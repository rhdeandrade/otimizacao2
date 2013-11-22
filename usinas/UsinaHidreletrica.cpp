/*
 * UsinaHidreletrica.cpp
 *
 *  Created on: 10/10/2013
 *      Author: raphael
 */

#ifndef USINAHIDRELETRICA_CPP_
#define USINAHIDRELETRICA_CPP_


#include "UsinaHidreletrica.h"

UsinaHidreletrica::UsinaHidreletrica() {
	// TODO Auto-generated constructor stub

}

void UsinaHidreletrica::atualizarBalancoHidrico(int periodo) {
	if (find(OtimizacaoDespachoHidrotermicoGlobals::obterInstancia()->cascata74.begin(), OtimizacaoDespachoHidrotermicoGlobals::obterInstancia()->cascata74.end(), this->id_usina) != OtimizacaoDespachoHidrotermicoGlobals::obterInstancia()->cascata74.end()) {
		return;
	}
	HistoricoOperacaoReservatorio* historicoOperacao = this->reservatorio.obterHistoricoOperacao(periodo, 0);
	HistoricoOperacaoReservatorio* historicoOperacaoAnterior = this->reservatorio.obterHistoricoOperacao(periodo - 1, this->reservatorio.volume_maximo);

	double volume = OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(historicoOperacao->volume, periodo);
	double volumeAnterior = OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(historicoOperacaoAnterior->volume, periodo);

	double vazaoTotal = carregar_vazao_montante(periodo); // Equivalente a calcularVazaoMontante
	double afluenciaNatural = carregar_afluencia_montante(periodo); // Equivalente a calcularVazaoMontante

	double volumeAtualizado = volumeAnterior + vazaoTotal;
	volumeAtualizado += historicoOperacao->vazao_turbinada;
	volumeAtualizado += historicoOperacao->vazao_vertida;
	volumeAtualizado += historicoOperacao->afluencia_natural;
	volumeAtualizado += afluenciaNatural;

	double result = volume - volumeAtualizado;

	if (abs((int)result) > OtimizacaoDespachoHidrotermicoGlobals::LIMIAR_ERRO_BALANCO_HIDRICO) {
		volumeAtualizado = OtimizacaoDespachoHidrotermicoGlobals::converterMetroCubicoParaHectometroCubico(volumeAtualizado, periodo);

		if (volumeAtualizado > this->reservatorio.volume_maximo) {
			historicoOperacao->volume = this->reservatorio.volume_maximo;
			volumeAtualizado += this->reservatorio.volume_maximo;
			historicoOperacao->vazao_vertida += OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(volumeAtualizado, periodo);

		} else if (this->reservatorio.volume_minimo > volumeAtualizado) {
			historicoOperacao->volume = volumeAtualizado;

			historicoOperacao->volume += OtimizacaoDespachoHidrotermicoGlobals::converterMetroCubicoParaHectometroCubico(historicoOperacao->vazao_vertida, periodo);

			historicoOperacao->vazao_vertida = 0;

			if (this->reservatorio.volume_minimo > historicoOperacao->volume) {
				double volumeMinimoFaltante = this->reservatorio.volume_minimo - historicoOperacao->volume;
				historicoOperacao->vazao_turbinada -= OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(volumeMinimoFaltante, periodo);
				historicoOperacao->volume += volumeMinimoFaltante;

				GeracaoEnergia* geracao = this->obterGeracaoEnergia(periodo);
				geracao->quantidade = this->calcularGeracaoEnergiaComProdutividadeMedia(periodo, 0, 0, 0, 0);
			}
		} else {
			historicoOperacao->volume = volumeAtualizado;
		}
	}

}


double UsinaHidreletrica::carregar_vazao_montante(int periodo) {
	double total = 0.0;
	for (int i = 0; i < this->montantes.size(); ++i) {
		UsinaHidreletrica montante = OtimizacaoDespachoHidrotermicoGlobals::obterUsina(this->montantes.at(i));

		if (montante.id_usina != -200) { //-200 não encontrou
			HistoricoOperacaoReservatorio* historico = montante.reservatorio.obterHistoricoOperacao(periodo, 0);
			total += historico->vazao_turbinada + historico->vazao_vertida;
		}
	}
	return total;
}

double UsinaHidreletrica::carregar_afluencia_montante(int periodo) {
  double total = 0.0;
  for (int i = 0; i < this->montantes.size(); ++i) {
      UsinaHidreletrica montante = OtimizacaoDespachoHidrotermicoGlobals::obterUsina(montantes.at(i));

      if (montante.id_usina != -200) {//-200 não encontrou
          HistoricoOperacaoReservatorio* historico = montante.reservatorio.obterHistoricoOperacao(periodo, 0);
          total += historico->afluencia_natural;
      }
    }
  return total;
}


double UsinaHidreletrica::calcularGeracaoEnergiaComProdutividadeMedia(int periodo, double volume, double volumeAnterior, double vazaoTurbinada, double vazaoVertida) {
	double resultado;
	if (periodo > 0) {
	    HistoricoOperacaoReservatorio* historico = this->reservatorio.obterHistoricoOperacao(periodo, this->reservatorio.volume_maximo);
	    HistoricoOperacaoReservatorio* historicoAnterior = this->reservatorio.obterHistoricoOperacao(periodo - 1, this->reservatorio.volume_maximo);

	    volume = historico->volume;
	    volumeAnterior = historicoAnterior->volume;
	    vazaoTurbinada = historico->vazao_turbinada;
	    vazaoVertida = historico->vazao_vertida;
	}

	double phi = this->calcularPolinomioMontante((volume + volumeAnterior)/2);
	double theta = this->calcularPolinomioJusante(vazaoVertida + vazaoTurbinada);

	double alturaQuedaBruta = phi - theta;
	double alturaQuedaLiquida;

	if (this->tipo_perda_hidraulica == 1) {
		alturaQuedaLiquida = alturaQuedaBruta - (((this->valor_perda_hidraulica / 100) * alturaQuedaBruta));
	} else if (this->tipo_perda_hidraulica == 2) {
		alturaQuedaLiquida = alturaQuedaBruta - this->valor_perda_hidraulica;
	} else if (this->tipo_perda_hidraulica == 3) {
		alturaQuedaLiquida = alturaQuedaBruta - ((this->valor_perda_hidraulica * pow(vazaoTurbinada, 2)));
	}

	resultado = this->produtividade_media * alturaQuedaLiquida;
	resultado *= vazaoTurbinada;

	return resultado;
}

double UsinaHidreletrica::calcularPolinomioMontante(double vazaoTotal) {

	  double A4 = this->coeficiente_cota_montante_a4 * pow(vazaoTotal, 4);
	  double A3 = this->coeficiente_cota_montante_a3 * pow(vazaoTotal, 3);
	  double A2 = this->coeficiente_cota_montante_a2 * pow(vazaoTotal, 2);
	  double A1 = this->coeficiente_cota_montante_a1 * vazaoTotal;

	  double resultado = this->coeficiente_cota_montante_a0 + A1 + A2 + A3 + A4;

	  return resultado;
}

double UsinaHidreletrica::calcularPolinomioJusante(double vazaoTotal) {
	double A4 = this->coeficiente_cota_jusante_a4 * pow(vazaoTotal, 4);
	  double A3 = this->coeficiente_cota_jusante_a3 * pow(vazaoTotal, 3);
	  double A2 = this->coeficiente_cota_jusante_a2 * pow(vazaoTotal, 2);
	  double A1 = this->coeficiente_cota_jusante_a1 * vazaoTotal;

	  double resultado = this->coeficiente_cota_jusante_a0 + A1 + A2 + A3 + A4;

	  return resultado;
}

#endif

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
	HistoricoOperacaoReservatorio* historicoOperacaoAnterior = this->reservatorio.obterHistoricoOperacao(periodo - 1, this->reservatorio.volumeMaximo);

	long double volume = OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(historicoOperacao->volume, periodo);
	long double volumeAnterior = OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(historicoOperacaoAnterior->volume, periodo);

	long double vazaoTotal = carregar_vazao_montante(periodo); // Equivalente a calcularVazaoMontante
	long double afluenciaNatural = carregar_afluencia_montante(periodo); // Equivalente a calcularVazaoMontante

	long double volumeAtualizado = volumeAnterior + vazaoTotal;
	volumeAtualizado += historicoOperacao->vazaoTurbinada;
	volumeAtualizado += historicoOperacao->vazaoVertida;
	volumeAtualizado += historicoOperacao->afluencia_natural;
	volumeAtualizado += afluenciaNatural;

	long double result = volume - volumeAtualizado;

	if (abs((int)result) > OtimizacaoDespachoHidrotermicoGlobals::LIMIAR_ERRO_BALANCO_HIDRICO) {
		volumeAtualizado = OtimizacaoDespachoHidrotermicoGlobals::converterMetroCubicoParaHectometroCubico(volumeAtualizado, periodo);

		if (volumeAtualizado > this->reservatorio.volumeMaximo) {
			historicoOperacao->volume = this->reservatorio.volumeMaximo;
			volumeAtualizado += this->reservatorio.volumeMaximo;
			historicoOperacao->vazaoVertida += OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(volumeAtualizado, periodo);

		} else if (this->reservatorio.volumeMinimo > volumeAtualizado) {
			historicoOperacao->volume = volumeAtualizado;

			historicoOperacao->volume += OtimizacaoDespachoHidrotermicoGlobals::converterMetroCubicoParaHectometroCubico(historicoOperacao->vazaoVertida, periodo);

			historicoOperacao->vazaoVertida = 0;

			if (this->reservatorio.volumeMinimo > historicoOperacao->volume) {
				long double volumeMinimoFaltante = this->reservatorio.volumeMinimo - historicoOperacao->volume;
				historicoOperacao->vazaoTurbinada -= OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(volumeMinimoFaltante, periodo);
				historicoOperacao->volume += volumeMinimoFaltante;

				GeracaoEnergia* geracao = this->obterGeracaoEnergia(periodo);
				geracao->quantidade = this->calcularGeracaoEnergiaComProdutividadeMedia(periodo, 0, 0, 0, 0);
			}
		} else {
			historicoOperacao->volume = volumeAtualizado;
		}
	}

}


long double UsinaHidreletrica::carregar_vazao_montante(int periodo) {
	long double total = 0.0;
	for (int i = 0; i < this->montantes.size(); ++i) {
		UsinaHidreletrica montante = OtimizacaoDespachoHidrotermicoGlobals::obterUsina(this->montantes.at(i));

		if (montante.id_usina != -200) { //-200 não encontrou
			HistoricoOperacaoReservatorio* historico = montante.reservatorio.obterHistoricoOperacao(periodo, 0);
			total += historico->vazaoTurbinada + historico->vazaoVertida;
		}
	}
	return total;
}

long double UsinaHidreletrica::carregar_afluencia_montante(int periodo) {
	long double total = 0.0;
	for (int i = 0; i < this->montantes.size(); ++i) {
      UsinaHidreletrica montante = OtimizacaoDespachoHidrotermicoGlobals::obterUsina(montantes.at(i));

      if (montante.id_usina != -200) {//-200 não encontrou
          HistoricoOperacaoReservatorio* historico = montante.reservatorio.obterHistoricoOperacao(periodo, 0);
          total += historico->afluencia_natural;
      }
    }
  return total;
}


long double UsinaHidreletrica::calcularGeracaoEnergiaComProdutividadeMedia(int periodo, long double volume, long double volumeAnterior, long double vazaoTurbinada, long double vazaoVertida) {
	long double resultado;
	if (periodo > 0) {
	    HistoricoOperacaoReservatorio* historico = this->reservatorio.obterHistoricoOperacao(periodo, this->reservatorio.volumeMaximo);
	    HistoricoOperacaoReservatorio* historicoAnterior = this->reservatorio.obterHistoricoOperacao(periodo - 1, this->reservatorio.volumeMaximo);

	    volume = historico->volume;
	    volumeAnterior = historicoAnterior->volume;
	    vazaoTurbinada = historico->vazaoTurbinada;
	    vazaoVertida = historico->vazaoVertida;
	}

	long double phi = this->calcularPolinomioMontante((volume + volumeAnterior)/2);
	long double theta = this->calcularPolinomioJusante(vazaoVertida + vazaoTurbinada);

	long double alturaQuedaBruta = phi - theta;
	long double alturaQuedaLiquida;

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

long double UsinaHidreletrica::calcularPolinomioMontante(long double vazaoTotal) {

	long double A4 = this->coeficiente_cota_montante_a4 * pow(vazaoTotal, 4);
	long double A3 = this->coeficiente_cota_montante_a3 * pow(vazaoTotal, 3);
	long double A2 = this->coeficiente_cota_montante_a2 * pow(vazaoTotal, 2);
	long double A1 = this->coeficiente_cota_montante_a1 * vazaoTotal;

	long double resultado = this->coeficiente_cota_montante_a0 + A1 + A2 + A3 + A4;

	 return resultado;
}

long double UsinaHidreletrica::calcularPolinomioJusante(long double vazaoTotal) {
	long double A4 = this->coeficiente_cota_jusante_a4 * pow(vazaoTotal, 4);
	long double A3 = this->coeficiente_cota_jusante_a3 * pow(vazaoTotal, 3);
	long double A2 = this->coeficiente_cota_jusante_a2 * pow(vazaoTotal, 2);
	long double A1 = this->coeficiente_cota_jusante_a1 * vazaoTotal;

	long double resultado = this->coeficiente_cota_jusante_a0 + A1 + A2 + A3 + A4;

	  return resultado;
}

long double UsinaHidreletrica::maximizarProducaoEnergia(int periodo, char tipoMaximizacao, bool previsao) {
	HistoricoOperacaoReservatorio* historico = this->reservatorio.obterHistoricoOperacao(periodo, this->reservatorio.volumeMaximo);
	HistoricoOperacaoReservatorio operacao_maximizada;

	if (tipoMaximizacao == UsinaHidreletrica::TIPO_MAXIMIZACAO_AFLUENCIA_NATURAL) {
		operacao_maximizada = this->maximizarVazaoTurbinadaMinimizarVazaoVertida(*historico);
	}
	else if (tipoMaximizacao == UsinaHidreletrica::TIPO_MAXIMIZACAO_RESERVATORIO) {
		operacao_maximizada = this->maximizarProducaoReservatorio(*historico);
	}

	if (previsao) {
		HistoricoOperacaoReservatorio* historico_anterior = this->reservatorio.obterHistoricoOperacao(periodo - 1, this->reservatorio.volumeMaximo);

		return this->calcularGeracaoEnergiaComProdutividadeMedia(0, operacao_maximizada.volume, historico_anterior->volume, operacao_maximizada.vazaoTurbinada, operacao_maximizada.vazaoVertida);

	}
	else {
		historico->volume = operacao_maximizada.volume;
		historico->vazaoTurbinada = operacao_maximizada.vazaoTurbinada;
		historico->vazaoVertida = operacao_maximizada.vazaoVertida;

		GeracaoEnergia* geracao = this->obterGeracaoEnergia(periodo);
		geracao->quantidade = this->calcularGeracaoEnergiaComProdutividadeMedia(periodo, 0, 0, 0, 0);
		return geracao->quantidade;

	}
}

HistoricoOperacaoReservatorio UsinaHidreletrica::maximizarVazaoTurbinadaMinimizarVazaoVertida(HistoricoOperacaoReservatorio historico) {
	double maxVazaoTurbinadaPeriodo = historico.vazaoTurbinada + historico.vazaoVertida;

	HistoricoOperacaoReservatorio h;

	if (maxVazaoTurbinadaPeriodo > this->reservatorio.maximo_vazao_turbinada) {
		h.vazaoTurbinada = this->reservatorio.maximo_vazao_turbinada;
		h.vazaoVertida = maxVazaoTurbinadaPeriodo - h.vazaoTurbinada;
	}
	else {
		h.vazaoTurbinada = maxVazaoTurbinadaPeriodo;
		h.vazaoVertida = 0;
	}

	h.volume = historico.volume;

	return h;
}

HistoricoOperacaoReservatorio UsinaHidreletrica::maximizarProducaoReservatorio(HistoricoOperacaoReservatorio historico) {
	HistoricoOperacaoReservatorio obj;

	long double vazaoTotal = this->carregar_vazao_montante(historico.periodo);
	long double afluenciaNatural = this->carregar_afluencia_montante(historico.periodo);

	HistoricoOperacaoReservatorio* historicoAnterior = this->reservatorio.obterHistoricoOperacao(historico.periodo - 1, this->reservatorio.volumeMaximo);

	long double volumeMensal = OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(historicoAnterior->volume, historico.periodo) + vazaoTotal;
	volumeMensal += historico.afluencia_natural;
	volumeMensal += afluenciaNatural;

	obj.volume = this->reservatorio.volumeMinimo;

	volumeMensal -= OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(this->reservatorio.volumeMinimo, historico.periodo);

	if (volumeMensal > this->reservatorio.volumeMinimo) {
		obj.vazaoTurbinada = this->reservatorio.maximo_vazao_turbinada;
		volumeMensal -= this->reservatorio.maximo_vazao_turbinada;

		if (volumeMensal > OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(this->reservatorio.volumeMaximo - this->reservatorio.volumeMinimo, historico.periodo)) {
			obj.volume  =  obj.volume + (this->reservatorio.volumeMaximo - this->reservatorio.volumeMinimo);

			volumeMensal -= OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(this->reservatorio.volumeMaximo - this->reservatorio.volumeMinimo, historico.periodo);

		}
		else {
			obj.volume += OtimizacaoDespachoHidrotermicoGlobals::converterMetroCubicoParaHectometroCubico(volumeMensal, historico.periodo);
			volumeMensal = 0;
		}

		obj.vazaoVertida = volumeMensal;
	}
	else {
		obj.vazaoTurbinada = volumeMensal;
		obj.vazaoVertida = 0;
	}

	return obj;
}

#endif

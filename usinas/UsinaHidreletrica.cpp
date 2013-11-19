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
	}


}
#endif

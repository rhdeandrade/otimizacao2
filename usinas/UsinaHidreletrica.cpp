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
	HistoricoOperacaoReservatorio* historico = this->reservatorio.obterHistoricoOperacao(periodo, 0);
	HistoricoOperacaoReservatorio* historico_anterior = this->reservatorio.obterHistoricoOperacao(periodo - 1, this->reservatorio.volume_maximo);

	double volume = OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(historico->volume, periodo);
	double volume_anterior = OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(historico_anterior->volume, periodo);
}
#endif

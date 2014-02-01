/*
 * RestricaoBalancoHidrico.cpp
 *
 *  Created on: 04/11/2013
 *      Author: raphael
 */

#ifndef RESTRICAOBALANCOHIDRICO_CPP_
#define RESTRICAOBALANCOHIDRICO_CPP_

#include "RestricaoBalancoHidrico.h"

RestricaoBalancoHidrico::RestricaoBalancoHidrico(vector<UsinaHidreletrica> hidreletricas) {
	this->hidreletricas = hidreletricas;
}

void RestricaoBalancoHidrico::checkConstraint() {
	bool isConstraintOK = true;
	double result = 0;
	for(int i = 1; i <= OtimizacaoDespachoHidrotermicoGlobals::NUM_PERIODO; i++) {
		for(int j = 0; j < this->hidreletricas.size(); j++) {
			UsinaHidreletrica hidreletrica = this->hidreletricas.at(j);

			HistoricoOperacaoReservatorio* historico = hidreletrica.reservatorio.obterHistoricoOperacao(i, 0);
			HistoricoOperacaoReservatorio* historicoOperacaoAnterior = hidreletrica.reservatorio.obterHistoricoOperacao(i-1, hidreletrica.reservatorio.volume_maximo);

			double volume = OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(historico->volume, i);
			double volumeAnterior = OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(historicoOperacaoAnterior->volume, i);

			double vazaoTotal = hidreletrica.carregar_vazao_montante(i); // Equivalente a calcularVazaoMontante
			double afluenciaNatural = hidreletrica.carregar_afluencia_montante(i); // Equivalente a calcularVazaoMontante

			if (hidreletrica.id_usina == 73)
				afluenciaNatural = 0;

			result = volume - (((((volumeAnterior + vazaoTotal) - historico->vazao_turbinada) - historico->vazao_vertida) + historico->afluencia_natural) - afluenciaNatural);

			if (abs(result > this->errorThreshold())) {
				isConstraintOK = false;
			}
		}

	}

	if (isConstraintOK) {
		cout << "Não consta violações de balanço hidrico.\n";
	}
	else {
		cout << "Restrição de balanço hídrico foi quebrada.\n";
	}
}

int RestricaoBalancoHidrico::errorThreshold() {
	return OtimizacaoDespachoHidrotermicoGlobals::LIMIAR_ERRO_BALANCO_HIDRICO;
}

#endif

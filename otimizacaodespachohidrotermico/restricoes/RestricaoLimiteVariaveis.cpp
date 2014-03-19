/*
 * RestricaoLimiteVariaveis.cpp
 *
 *  Created on: 04/11/2013
 *      Author: raphael
 */

#ifndef RESTRICAOLIMITEVARIAVEIS_CPP_
#define RESTRICAOLIMITEVARIAVEIS_CPP_

#include "RestricaoLimiteVariaveis.h"

RestricaoLimiteVariaveis::RestricaoLimiteVariaveis(vector<UsinaHidreletrica> hidreletricas, vector<UsinaTermica> termicas) {
	this->termicas = termicas;
	this->hidreletricas = hidreletricas;

}

void RestricaoLimiteVariaveis::checkConstraint() {
	bool isConstraintOK = true;

	for(int i = 1; i <= OtimizacaoDespachoHidrotermicoGlobals::NUM_PERIODO; i++) {
		for(int j = 0; j < this->hidreletricas.size(); j++) {
			UsinaHidreletrica hidreletrica = this->hidreletricas.at(j);

			if (this->capacidadeArmazenamentoReservatorio(hidreletrica, i)) {
				isConstraintOK = false;
			}
			if (this->capacidadeVazaoTurbinadaReservatorio(hidreletrica, i)) {
				isConstraintOK = false;
			}
			if (this->capacidadeVazaoVertidaReservatorio(hidreletrica, i)) {
				isConstraintOK = false;
			}
		}

		for (int j = 0; j < this->termicas.size(); j++) {
			UsinaTermica termica = this->termicas.at(j);

			if (this->capacidadeGeracaoEnergiaTermica(termica, i)) {
				isConstraintOK = false;
			}

		}
	}

	if (isConstraintOK) {
		cout << "Não consta violações de Limites de Variáveis\n";
	}
	else {
		cout << "Restrição de Limites de Variáveis foi quebrada\n";
	}
}

bool RestricaoLimiteVariaveis::capacidadeArmazenamentoReservatorio(UsinaHidreletrica hidreletrica, int periodo) {
	HistoricoOperacaoReservatorio* historico = hidreletrica.reservatorio.obterHistoricoOperacao(periodo, 0);

	if (hidreletrica.reservatorio.volumeMaximo < historico->volume) {
		return true;
	}
	if (hidreletrica.reservatorio.volumeMinimo > historico->volume) {
		return true;
	}

	return false;

}

bool RestricaoLimiteVariaveis::capacidadeVazaoTurbinadaReservatorio(UsinaHidreletrica hidreletrica, int periodo) {
	HistoricoOperacaoReservatorio* historico = hidreletrica.reservatorio.obterHistoricoOperacao(periodo, 0);

	if (hidreletrica.reservatorio.maximo_vazao_turbinada < historico->vazaoTurbinada) {
		return true;
	}
	if (hidreletrica.reservatorio.minimo_vazao_turbinada > historico->vazaoTurbinada) {
		return true;
	}

	return false;
}

bool RestricaoLimiteVariaveis::capacidadeVazaoVertidaReservatorio(UsinaHidreletrica hidreletrica, int periodo) {
	HistoricoOperacaoReservatorio* historico = hidreletrica.reservatorio.obterHistoricoOperacao(periodo, 0);

	//cout << hidreletrica.reservatorio.maximo_vazao_vertida << " " << historico->vazao_vertida << "\n";
	if (hidreletrica.reservatorio.maximo_vazao_vertida < historico->vazaoVertida) {
		return true;
	}
	if (historico->vazaoTurbinada < 0) {
		return true;
	}

	return false;
}

bool RestricaoLimiteVariaveis::capacidadeGeracaoEnergiaTermica(UsinaTermica termica, int periodo) {
	GeracaoEnergia* geracao = termica.obterGeracaoEnergia(periodo);

	if (termica.quantidade_geracao_max < geracao->quantidade) {
		return true;
	}
	if (termica.quantidadeGeracaoMin > geracao->quantidade) {
		return true;
	}

	return false;
}
#endif

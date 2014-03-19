/*
 * RestricaoDefluenciaMinima.cpp
 *
 *  Created on: 04/11/2013
 *      Author: raphael
 */

#ifndef RESTRICAODEFLUENCIAMINIMA_CPP_
#define RESTRICAODEFLUENCIAMINIMA_CPP_

#include "RestricaoDefluenciaMinima.h"

RestricaoDefluenciaMinima::RestricaoDefluenciaMinima(vector<UsinaHidreletrica> hidreletricas) {
	this->hidreletricas = hidreletricas;

}

void RestricaoDefluenciaMinima::checkConstraint() {
	bool isConstraintOK = true;
	long double result = 0;

	for(int i = 1; i <= OtimizacaoDespachoHidrotermicoGlobals::NUM_PERIODO; i++) {
		for(int j = 0; j < this->hidreletricas.size(); j++) {
			UsinaHidreletrica hidreletrica = this->hidreletricas.at(j);

			HistoricoOperacaoReservatorio* historico = hidreletrica.reservatorio.obterHistoricoOperacao(i, 0);

			result = (hidreletrica.reservatorio.defluencia_minima - (historico->vazaoVertida + historico->vazaoTurbinada));

			if (result > this->errorThreshold()) {
				isConstraintOK = false;
			}
		}
	}

	if (isConstraintOK) {
		cout << "Não consta violação de Defluencia Mínina\n";
	}
	else {
		cout << "Restrição de Defluencia Mínima foi quebrada\n";
	}
}

int RestricaoDefluenciaMinima::errorThreshold() {
	return 1;
}
#endif

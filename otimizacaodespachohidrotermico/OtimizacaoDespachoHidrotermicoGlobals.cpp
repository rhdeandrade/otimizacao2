/*
 * OtimizacaoDespachoHidrotermicoGlobals.cpp
 *
 *  Created on: 24/10/2013
 *      Author: raphael
 */

#ifndef OTIMIZACAODESPACHOHIDROTERMICOGLOBALS_CPP_
#define OTIMIZACAODESPACHOHIDROTERMICOGLOBALS_CPP_

#include "OtimizacaoDespachoHidrotermicoGlobals.h"

OtimizacaoDespachoHidrotermicoGlobals* OtimizacaoDespachoHidrotermicoGlobals::instancia;

OtimizacaoDespachoHidrotermicoGlobals::OtimizacaoDespachoHidrotermicoGlobals() {
	cascata74.push_back(74);
	cascata74.push_back(76);
	cascata74.push_back(77);
	cascata74.push_back(71);
	cascata74.push_back(72);
	cascata74.push_back(73);
	cascata74.push_back(77);
	cascata74.push_back(78);
	cascata74.push_back(82);

}

OtimizacaoDespachoHidrotermicoGlobals* OtimizacaoDespachoHidrotermicoGlobals::obterInstancia() {
	if (instancia == NULL) {
		instancia = new OtimizacaoDespachoHidrotermicoGlobals();
	}
	return instancia;
}

void OtimizacaoDespachoHidrotermicoGlobals::atualizarPlanoProducao(PlanoProducao planoProducao) {
	int i;
	for (i = 1; i <= OtimizacaoDespachoHidrotermicoGlobals::NUM_PERIODO; i++) {
		for (int j = 0; j < planoProducao.subsistemas.size(); j++) {
			double totalGeracaoHidreletricas = 0;
			double totalGeracaoTermicas = 0;
			double totalIntercambio = 0;


			vector<UsinaTermica> termicas = OtimizacaoDespachoHidrotermicoGlobals::obterUsinasDoSubsistema(planoProducao.termicas, planoProducao.subsistemas.at(j).id_subsistema);


		}
	}
}


vector<Usina> OtimizacaoDespachoHidrotermicoGlobals::obterUsinasDoSubsistema(vector<Usina> usinas, int idUsina) {
	vector<Usina> result;

	return result;
}

#endif

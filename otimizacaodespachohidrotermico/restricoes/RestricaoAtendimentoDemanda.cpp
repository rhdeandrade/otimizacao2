/*
 * RestricaoAtendimentoDemanda.cpp

 *
 *  Created on: 04/11/2013
 *      Author: raphael
 */

#ifndef RESTRICAOATENDIMENTODEMANDA_CPP_
#define RESTRICAOATENDIMENTODEMANDA_CPP_

#include "RestricaoAtendimentoDemanda.h"

RestricaoAtendimentoDemanda::RestricaoAtendimentoDemanda(vector<Subsistema> subsistemas, vector<UsinaHidreletrica> hidreletricas, vector<UsinaTermica> termicas) {
	this->hidreletricas = hidreletricas;
	this->subsistemas = subsistemas;
	this->termicas = termicas;

}

void RestricaoAtendimentoDemanda::checkConstraint() {
	bool isContraintOk = true;
	long double result = 0;

	for(int i = 1; i <= OtimizacaoDespachoHidrotermicoGlobals::NUM_PERIODO; i++) {
		for(int j = 0; j < this->subsistemas.size(); j++) {
			Subsistema subsistema = this->subsistemas.at(j);

			long double totalGeracaoHidreletricas = 0;
			long double totalGeracaoTermicas = 0;
			long double totalIntercambio = 0;

			vector<UsinaTermica> termicas = OtimizacaoDespachoHidrotermicoGlobals::obterUsinasTermicasDoSubsistema(this->termicas, subsistema.id_subsistema);

			for(int k = 0; k < termicas.size(); k++) {
				UsinaTermica termica = termicas.at(k);

				GeracaoEnergia* geracao = termica.obterGeracaoEnergia(i);
				totalGeracaoTermicas += geracao->quantidade;
			}

			vector<UsinaHidreletrica> hidreletricas = OtimizacaoDespachoHidrotermicoGlobals::obterUsinasHidreletricasDoSubsistema(this->hidreletricas, subsistema.id_subsistema);

			for(int k = 0; k < hidreletricas.size(); k++) {
				UsinaHidreletrica hidreletrica = hidreletricas.at(k);

				GeracaoEnergia* geracao = hidreletrica.obterGeracaoEnergia(i);
				totalGeracaoHidreletricas += geracao->quantidade;
			}

			Intercambio* intercambio = subsistema.obterIntercambioEnergia(i);
			long double totalEnviado = intercambio->totalEnergiaEnviada();
			long double totalRecebido = 0;

			for(int k = 0; k < this->subsistemas.size(); k++) {
				Subsistema ss = this->subsistemas.at(k);

				intercambio = ss.obterIntercambioEnergia(i);
				totalRecebido += intercambio->totalEnergiaRecebida(i);
			}



			totalIntercambio = totalRecebido - totalEnviado;

			DemandaEnergia* demanda = subsistema.obterDemandaEnergia(i);
			Deficit* deficit = subsistema.obterDeficitSubsistema(i);

			result = totalGeracaoHidreletricas + totalGeracaoTermicas + totalIntercambio;

			result -= demanda->quantidade;
			result += deficit->deficit;

			if ( (abs(result) > this->errorThreshold()) && result < 0) {
				isContraintOk = false;
			}

		}
	}

	if (isContraintOk) {
		cout << "Não há violações de atendimendo a demanda" << "\n";
	}
	else {
		cout << "Restrição de atendimento de demanda foi quebrada." << "\n";
	}
}

int RestricaoAtendimentoDemanda::errorThreshold() {
	return 1;
}

#endif

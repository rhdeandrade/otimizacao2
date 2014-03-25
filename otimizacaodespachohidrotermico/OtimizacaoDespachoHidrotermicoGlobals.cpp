/*
 * OtimizacaoDespachoHidrotermicoGlobals.cpp
 *
 *  Created on: 24/10/2013
 *      Author: raphael
 */

#ifndef OTIMIZACAODESPACHOHIDROTERMICOGLOBALS_CPP_
#define OTIMIZACAODESPACHOHIDROTERMICOGLOBALS_CPP_

#include "OtimizacaoDespachoHidrotermicoGlobals.h"

#include "PlanoProducao.cpp"
#include "../util/Report.cpp"


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


void OtimizacaoDespachoHidrotermicoGlobals::atualizarPlanoProducao(PlanoProducao* planoProducao) {
	int i;
	for (i = 1; i <= OtimizacaoDespachoHidrotermicoGlobals::NUM_PERIODO; i++) {
		for (int j = 0; j < planoProducao->subsistemas.size(); j++) {
			Subsistema* subsistema = &planoProducao->subsistemas.at(j);

			long double totalGeracaoHidreletricas = 0;
			long double totalGeracaoTermicas = 0;
			long double totalIntercambio = 0;

			vector<UsinaTermica> termicas = OtimizacaoDespachoHidrotermicoGlobals::obterUsinasTermicasDoSubsistema(planoProducao->termicas, subsistema->id_subsistema);

			for (int k = 0; k < termicas.size(); k++) {
				GeracaoEnergia* geracao = termicas.at(k).obterGeracaoEnergia(i);
				totalGeracaoTermicas += geracao->quantidade;
			}


			vector<UsinaHidreletrica> hidreletricas = OtimizacaoDespachoHidrotermicoGlobals::obterUsinasHidreletricasDoSubsistema(planoProducao->hidreletricas, subsistema->id_subsistema);

			for (int k = 0; k < hidreletricas.size(); k++) {
				hidreletricas.at(k).atualizarBalancoHidrico(i);
				GeracaoEnergia* geracao = hidreletricas.at(k).obterGeracaoEnergia(i);
				totalGeracaoHidreletricas += geracao->quantidade;
			}

			Intercambio* intercambio = subsistema->obterIntercambioEnergia(i);
			long double totalEnviado = intercambio->totalEnergiaEnviada();

			long double totalRecebido = 0;
			for (int k = 0; k < planoProducao->subsistemas.size(); k++) {
				intercambio = planoProducao->subsistemas.at(k).obterIntercambioEnergia(i);
				totalRecebido += intercambio->totalEnergiaRecebida(subsistema->id_subsistema);
			}
			totalIntercambio = totalRecebido - totalEnviado;

			DemandaEnergia* demanda = subsistema->obterDemandaEnergia(i);
			Deficit* deficit = subsistema->obterDeficitSubsistema(i);

			long double result = totalGeracaoTermicas + totalGeracaoHidreletricas;
			result += totalIntercambio;
			result = demanda->quantidade - result;

			//cout << totalGeracaoTermicas << " " << totalGeracaoHidreletricas << " " << totalIntercambio << " " << demanda->quantidade << " " << "Resultado incrivel esse brother: " << result << "\n";

			if (result > 0) {
				deficit->deficit = result;
				//cout << "Atualizando Deficit: " << deficit->deficit << " " << deficit->periodo << "\n";
			}
			else {
				deficit->deficit = 0;
			}
		}
	}
}


vector<UsinaTermica> OtimizacaoDespachoHidrotermicoGlobals::obterUsinasTermicasDoSubsistema(vector<UsinaTermica> usinas, int idUsina) {
	vector<UsinaTermica> termicas;

	for (int i = 0; i < usinas.size(); i++) {
		if (usinas.at(i).id_subsistema == idUsina) {
			termicas.push_back(usinas.at(i));
		}
	}

	return termicas;
}

vector<UsinaHidreletrica> OtimizacaoDespachoHidrotermicoGlobals::obterUsinasHidreletricasDoSubsistema(vector<UsinaHidreletrica> usinas, int idUsina) {
	vector<UsinaHidreletrica> hidreletricas;

	for (int i = 0; i < usinas.size(); i++) {
		if (usinas.at(i).id_subsistema == idUsina) {
			hidreletricas.push_back(usinas.at(i));
		}
	}

	return hidreletricas;
}

long double OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(long double valor, int periodo) {
	return valor * (pow(10.0, 6.0) / quantidadeSegundosMes(periodo));
}

long double OtimizacaoDespachoHidrotermicoGlobals::converterMetroCubicoParaHectometroCubico(long double valor, int periodo) {
	return valor / (pow(10.0, 6.0) / quantidadeSegundosMes(periodo));
}

long double OtimizacaoDespachoHidrotermicoGlobals::quantidadeSegundosMes(int periodo) {
	return 3600 * quantidadeHorasMes(periodo);
}

long double OtimizacaoDespachoHidrotermicoGlobals::quantidadeHorasMes(int periodo) {
	return 24 * quantidadeDiasMes(periodo);
}

long double OtimizacaoDespachoHidrotermicoGlobals::quantidadeDiasMes(int periodo) {
	int mes_atual = mesCorrente(periodo);

	if (mes_atual == 1)
		return 31.0;
	else if (mes_atual == 2){
		time_t t = time(0);   // get time now
		struct tm * now = localtime( & t );
		if (((now->tm_year + 1900) % 4) == 0)
			return 29.0;
		return 28.0;
	}
	else if (mes_atual == 3)
		return 31.0;
	else if (mes_atual == 4)
		return 30.0;
	else if (mes_atual == 5)
		return 31.0;
	else if (mes_atual == 6)
		return 30.0;
	else if (mes_atual == 7)
		return 31.0;
	else if (mes_atual == 8)
		return 31.0;
	else if (mes_atual == 9)
		return 30.0;
	else if (mes_atual == 10)
		return 31.0;
	else if (mes_atual == 11)
		return 30.0;
	else
		return 31.0;
}

int OtimizacaoDespachoHidrotermicoGlobals::mesCorrente(int periodo) {
	int mod = periodo % 12;

	if(mod == 0) {
		return 12;
	}
	else {
		return mod;
	}
}

UsinaHidreletrica OtimizacaoDespachoHidrotermicoGlobals::obterUsina(int id_usina) {
	vector<UsinaHidreletrica> hidreletricas = OtimizacaoDespachoHidrotermicoGlobals::instancia->hidreletricas;
	for (int i = 0; i < hidreletricas.size(); ++i) {
		if (hidreletricas.at(i).id_usina == id_usina) {
			return hidreletricas.at(i);
		}
	}

	UsinaHidreletrica usina;
	usina.id_usina = -200;
	return usina;

}

vector<UsinaHidreletrica>* OtimizacaoDespachoHidrotermicoGlobals::ordenarHidreletricasPorTamanhoReservatorio(vector<UsinaHidreletrica>* hidreletricas, bool comJusantes) {


	for (int i = 1; i < hidreletricas->size(); i++) {
		int j = i;
		while((hidreletricas->at(j).reservatorio.obterTamanho() > hidreletricas->at(j - 1).reservatorio.obterTamanho())) {

			UsinaHidreletrica* aux = &hidreletricas->at(j);
			UsinaHidreletrica* usina_j = &hidreletricas->at(j);
			UsinaHidreletrica* usina_j_1 = &hidreletricas->at(j-1);

			*usina_j = *usina_j_1;
			*usina_j_1 = *aux;
			j--;

			if (j == 0) {
				break;
			}

		}
	}
	/**
	if (!comJusantes)
		return hidreletricas;
	else {
		vector<UsinaHidreletrica> result;

		for(int i = 0; i <= hidreletricas->size(); i++) {
			UsinaHidreletrica hidreletrica = hidreletricas->at(i);

			if (!find(hidreletricas->begin(), hidreletricas->end(), hidreletrica) != hidreletricas->end()) {
				result.push_back(hidreletrica);
				this->obterUsinaJusante(hidreletrica, result);
			}

		}

		return hidreletricas;
	}
	*/

	return hidreletricas;

}

void OtimizacaoDespachoHidrotermicoGlobals::obterUsinaJusante(UsinaHidreletrica h, vector<UsinaHidreletrica> result) {

	if (h.jusante == 0) {
		return;
	}

	UsinaHidreletrica jusante = obterUsina(h.jusante);
	result.push_back(jusante);
	obterUsinaJusante(jusante, result);
}

vector<UsinaTermica>* OtimizacaoDespachoHidrotermicoGlobals::obterTermicasComPrioridadeDesativacao(vector<UsinaTermica>* termicas, int periodo) {

	vector<UsinaTermica> urgente;
	vector<UsinaTermica> normal;

	termicas = ordenarTermicasPorCusto(termicas, periodo);

	for(int i = 0; i < termicas->size(); i++) {
		UsinaTermica termica = termicas->at(i);

		if (find(termica.periodosDesativacaoObrigatorio.begin(), termica.periodosDesativacaoObrigatorio.end(), periodo) != termica.periodosDesativacaoObrigatorio.end()) {
			urgente.push_back(termica);
		}
		else {
			normal.push_back(termica);
		}

	}

	urgente.insert(urgente.end(), normal.begin(), normal.end());
	termicas->swap(urgente);

	return termicas;
}

vector<UsinaTermica>* OtimizacaoDespachoHidrotermicoGlobals::ordenarTermicasPorCusto(vector<UsinaTermica>* termicas, int periodo) {

	int totalTermicas = termicas->size();

	for (int i = 1; i < totalTermicas; i++) {
		int j = i;
		while(termicas->at(j).custoTermicaMegaWattMedio(periodo) < termicas->at(j - 1).custoTermicaMegaWattMedio(periodo)) {
			UsinaTermica* aux = &termicas->at(j);
			UsinaTermica* usina_j = &termicas->at(j);
			UsinaTermica* usina_j_1 = &termicas->at(j-1);
			*usina_j = *usina_j_1;
			*usina_j_1 = *aux;
			j--;

			if(j == 0) {
				break;
			}
		}
	}

	return termicas;
}

#endif

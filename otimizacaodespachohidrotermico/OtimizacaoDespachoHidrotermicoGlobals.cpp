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

			vector<UsinaTermica> termicas = OtimizacaoDespachoHidrotermicoGlobals::obterUsinasTermicasDoSubsistema(planoProducao.termicas, planoProducao.subsistemas.at(j).id_subsistema);

			for (int k = 0; k < termicas.size(); k++) {
				GeracaoEnergia* geracao = termicas.at(k).obterGeracaoEnergia(i);
				totalGeracaoTermicas += geracao->quantidade;
			}

			vector<UsinaHidreletrica> hidreletricas = OtimizacaoDespachoHidrotermicoGlobals::obterUsinasHidreletricasDoSubsistema(planoProducao.hidreletricas, planoProducao.subsistemas.at(j).id_subsistema);

			for (int k = 0; k < hidreletricas.size(); k++) {
				hidreletricas.at(k).atualizarBalancoHidrico(i);
				GeracaoEnergia* geracao = hidreletricas.at(k).obterGeracaoEnergia(i);
				totalGeracaoHidreletricas += geracao->quantidade;
			}

			Intercambio* intercambio = planoProducao.subsistemas.at(j).obterIntercambioEnergia(i);
			double totalEnviado = intercambio->totalEnergiaEnviada();

			double totalRecebido = 0;
			for (int k = 0; k < planoProducao.subsistemas.size(); k++) {
				intercambio = planoProducao.subsistemas.at(k).obterIntercambioEnergia(i);
				totalRecebido += intercambio->totalEnergiaRecebida(planoProducao.subsistemas.at(j).id_subsistema);
			}

			totalIntercambio = totalRecebido - totalEnviado;
			DemandaEnergia* demanda = planoProducao.subsistemas.at(j).obterDemandaEnergia(i);
			Deficit* deficit = planoProducao.subsistemas.at(j).obterDeficitSubsistema(i);

			double result = totalGeracaoTermicas + totalGeracaoHidreletricas;
			result += totalIntercambio;
			result = result - demanda->quantidade;

			if (deficit)
				if (result > 0) {
					deficit->deficit = result;
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

double OtimizacaoDespachoHidrotermicoGlobals::converterHectometroCubicoParaMetroCubico(double valor, int periodo) {
	return valor * (pow(10.0, 6.0) / quantidadeSegundosMes(periodo));
}

double OtimizacaoDespachoHidrotermicoGlobals::converterMetroCubicoParaHectometroCubico(double valor, int periodo) {
	return valor / (pow(10.0, 6.0) / quantidadeSegundosMes(periodo));
}

double OtimizacaoDespachoHidrotermicoGlobals::quantidadeSegundosMes(int periodo) {
	return 3600 * quantidadeHorasMes(periodo);
}

double OtimizacaoDespachoHidrotermicoGlobals::quantidadeHorasMes(int periodo) {
	return 24 * quantidadeDiasMes(periodo);
}

double OtimizacaoDespachoHidrotermicoGlobals::quantidadeDiasMes(int periodo) {
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

#endif

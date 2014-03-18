/*
 * OperacaoAtomicaQuatro.cpp
 *
 *  Created on: 13/03/2014
 *      Author: raphael
 */

#ifndef OPERACAOATOMICAQUATRO_CPP_
#define OPERACAOATOMICAQUATRO_CPP_


#include "OperacaoAtomicaQuatro.h"


using namespace std;

OperacaoAtomicaQuatro::OperacaoAtomicaQuatro() {
	// TODO Auto-generated constructor stub

}


PlanoProducao OperacaoAtomicaQuatro::execute(PlanoProducao* planoProducao, int periodo) {

	for(int i = 0; i < planoProducao->subsistemas.size(); i++) {
		Subsistema subsistema = planoProducao->subsistemas.at(i);

		vector<UsinaHidreletrica> hidreletricas = OtimizacaoDespachoHidrotermicoGlobals::obterUsinasHidreletricasDoSubsistema(planoProducao->hidreletricas, subsistema.id_subsistema);
		vector<UsinaTermica> termicas = OtimizacaoDespachoHidrotermicoGlobals::obterUsinasTermicasDoSubsistema(planoProducao->termicas, subsistema.id_subsistema);

		long double totalEnergiaHidraulicaSobrando = this->planejarMaximizacaoEnergiaHidraulica(hidreletricas, periodo);

		long double totalEnergiaTermicaDesligada = this->minimizarEnergiaTermica(termicas, periodo, &totalEnergiaHidraulicaSobrando);

		long double totalEnergiaHidraulicaProduzida = this->produzirEnergiaHidraulica(hidreletricas, periodo, totalEnergiaTermicaDesligada);
	}

	planoProducao = OtimizacaoDespachoHidrotermicoGlobals::atualizarPlanoProducao(planoProducao);

	return planoProducao;

}

long double OperacaoAtomicaQuatro::planejarMaximizacaoEnergiaHidraulica(vector<UsinaHidreletrica> hidreletricas, int periodo) {

	long double result = 0;

	vector<int> cascata74 = OtimizacaoDespachoHidrotermicoGlobals::obterInstancia()->cascata74;

	hidreletricas = OtimizacaoDespachoHidrotermicoGlobals::ordenarHidreletricasPorTamanhoReservatorio(hidreletricas, false);

	for (int i = 0; i < hidreletricas.size(); ++i) {
		if (find(cascata74.begin(), cascata74.end(), hidreletricas.at(i).id_usina) != cascata74.end()) {
			continue;
		}
		else {
			if (hidreletricas.at(i).reservatorio.obterTamanho() > 0) {
				result += hidreletricas.at(i).maximizar_producao_energia(periodo, UsinaHidreletrica::TIPO_MAXIMIZACAO_RESERVATORIO, true);
			}
			else {
				result += hidreletricas.at(i).maximizar_producao_energia(periodo, UsinaHidreletrica::TIPO_MAXIMIZACAO_AFLUENCIA_NATURAL, true);
			}

			GeracaoEnergia* geracao = hidreletricas.at(i).obterGeracaoEnergia(periodo);

			result -= geracao->quantidade;
		}
	}

	return result;
}


long double OperacaoAtomicaQuatro::minimizarEnergiaTermica(vector<UsinaTermica> termicas, int periodo, long double* totalEnergiaHidraulicaSobrando) {
	long double result = 0;

	termicas = OtimizacaoDespachoHidrotermicoGlobals::obter_termicas_com_prioridade_desativacao(termicas, periodo);

	for (int i = 0; i < termicas.size(); i++) {
		GeracaoEnergia* geracao = termicas.at(i).obterGeracaoEnergia(periodo);
		long double saldo = *totalEnergiaHidraulicaSobrando- geracao->quantidade;

		if (saldo > 0) {
			long double quantidade = termicas.at(i).iniciar_processo_desativacao(periodo);
			*totalEnergiaHidraulicaSobrando -= quantidade;

			result += quantidade;
		}
	}

	return result;

}

long double OperacaoAtomicaQuatro::produzirEnergiaHidraulica(vector<UsinaHidreletrica> hidreletricas, int periodo, double totalEnergiaTermicaDesligada) {
	long double totalEnergiaProduzida = 0;

	hidreletricas = OtimizacaoDespachoHidrotermicoGlobals::ordenarHidreletricasPorTamanhoReservatorio(hidreletricas, false);

	vector<int> cascata74 = OtimizacaoDespachoHidrotermicoGlobals::obterInstancia()->cascata74;

	for (int i = 0; i < hidreletricas.size(); i++) {
		if (find(cascata74.begin(), cascata74.end(), hidreletricas.at(i).id_usina) != cascata74.end()) {
			continue;
		}

		if (totalEnergiaTermicaDesligada > totalEnergiaProduzida) {
			if (hidreletricas.at(i).reservatorio.obterTamanho() > 0) {
				totalEnergiaProduzida += hidreletricas.at(i).maximizar_producao_energia(periodo, UsinaHidreletrica::TIPO_MAXIMIZACAO_RESERVATORIO, false);
			}
			else {
				totalEnergiaProduzida += hidreletricas.at(i).maximizar_producao_energia(periodo, UsinaHidreletrica::TIPO_MAXIMIZACAO_AFLUENCIA_NATURAL, false);
			}
		}
	}

	return totalEnergiaProduzida;

}


#endif

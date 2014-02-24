#ifndef PLANOPRODUCAO_CPP_
#define PLANOPRODUCAO_CPP_

/*
 * PlanoProducao.cpp
 *
 *  Created on: 30/09/2013
 *      Author: raphael
 */

#include "PlanoProducao.h"
#include "../usinas/Subsistema.cpp"
#include "../usinas/UsinaHidreletrica.cpp"
#include "../usinas/UsinaTermica.cpp"
#include "restricoes/Restricao.cpp"
#include "restricoes/RestricaoAtendimentoDemanda.cpp"
#include "restricoes/RestricaoDefluenciaMinima.cpp"
#include "restricoes/RestricaoBalancoHidrico.cpp"
#include "restricoes/RestricaoLimiteVariaveis.cpp"

PlanoProducao::PlanoProducao() {
	// TODO Auto-generated constructor stub

}

PlanoProducao::PlanoProducao(PlanoProducao obj) {
	this->termicas(obj.termicas);
	this->hidreletricas(obj.hidreletricas);
	this->subsistemas(obj.subsistemas);
}

std::vector<string> FileHandler::open_file(string file_name) {

	fstream myfile;
	std::vector<string> dados;
	string line;

	//cout << "Open File: " << file_name << "\n";

	myfile.open(file_name.c_str(), fstream::in);

	if (myfile.is_open()) {

		while (!myfile.eof()) {

			getline(myfile, line);

			if (!line.empty()) {
				dados.push_back(line);
			}
		}

		myfile.close();
	} else {
		cout << "Arquivo não encontrado\n";
	}

	return dados;

}

void PlanoProducao::ativarRestricoes(bool balancoHidrico, bool atendimentoDemanda, bool defluenciaMinima, bool limiteVariaveis) {
	if (balancoHidrico) {
		RestricaoBalancoHidrico* restricaoBalandoHidrico = new RestricaoBalancoHidrico(this->hidreletricas);
		this->restricoes.balanco_hidrico = restricaoBalandoHidrico;
	}
	if (atendimentoDemanda) {
		RestricaoAtendimentoDemanda* restricaoAtendimentoDemanda = new RestricaoAtendimentoDemanda(this->subsistemas, this->hidreletricas, this->termicas);
		this->restricoes.atendimento_demanda = restricaoAtendimentoDemanda;
	}
	if (defluenciaMinima) {
		RestricaoDefluenciaMinima* restricaoDefluenciaMinima = new RestricaoDefluenciaMinima(this->hidreletricas);
		this->restricoes.defluencia_minima = restricaoDefluenciaMinima;
	}
	if (limiteVariaveis) {
		RestricaoLimiteVariaveis* restricaoLimiteVariaveis =new RestricaoLimiteVariaveis(this->hidreletricas, this->termicas);
		this->restricoes.limite_variaveis = restricaoLimiteVariaveis;
	}

}

long double PlanoProducao::objectiveFunctionValue() {
	long double custo = 0;

	for (int i = 0; i < OtimizacaoDespachoHidrotermicoGlobals::NUM_PERIODO;
			i++) {
		long double custoTermica = 0;
		long double custoDeficit = 0;
		for (int j = 0; j < this->termicas.size(); j++) {
			custoTermica += this->termicas.at(j).custo_termica_mega_watt_medio(
					i);
		}

		for (int j = 0; j < this->subsistemas.size(); j++) {
			if (this->subsistemas.at(j).id_subsistema != 5)
				custoDeficit += this->subsistemas.at(j).custoDeficit(i);
		}

		long double result = custoTermica + custoDeficit;
		result *= this->calcularValorPresente(i);

		custo += result;
	}

	return custo;
}

void PlanoProducao::perturbation(int atomicOperationId, int counter) {
	switch (atomicOperationId) {
	case 1:
		//Operacao 1
	case 2:
		//Operacao 2
	case 3:
		//Operacao 3
	case 4:
		//Operacao 4
	}
}

long double PlanoProducao::calcularValorPresente(int periodo) {
	long double result = 1 + OtimizacaoDespachoHidrotermicoGlobals::TAXA_DESCONTO;
	result = pow(result, periodo);
	result = 1 / result;
	return result;

}

long double PlanoProducao::objectiveFunctionValue() {
	long double custo = 0;

	for (int i = 0; i < OtimizacaoDespachoHidrotermicoGlobals::NUM_PERIODO; i++) {
		long double custoTermica = 0;
		long double custoDeficit = 0;
		for (int j = 0; j < this->termicas.size(); j++) {
			custoTermica += this->termicas.at(j).custo_termica_mega_watt_medio(i);
		}

		for (int j = 0; j < this->subsistemas.size(); j++) {
			if (this->subsistemas.at(j).id_subsistema != 5)
				custoDeficit += this->subsistemas.at(j).custoDeficit(i);
		}

		long double result = custoTermica + custoDeficit;
		result *= this->calcularValorPresente(i);

		custo += result;
	}

	return custo;
}

#endif

/*
 * UsinaTermica.cpp
 *
 *  Created on: 10/10/2013
 *      Author: raphael
 */

#ifndef USINATERMICA_CPP_
#define USINATERMICA_CPP_

#include "UsinaTermica.h"

#include <cmath>

#include "GeracaoEnergia.h"
#include "Usina.cpp"

UsinaTermica::UsinaTermica() {
	this->coeficiente_custo_termica_a2 = 0;
	this->coeficiente_custo_termica_a0 = 0;
	this->coeficiente_custo_termica_a1 = 0;
	this->tempo_minimo_ativada = 3;
	this->tempo_minimo_desativada = 3;

}

long double UsinaTermica::custoTermicaMegaWattMedio(int periodo) {
	GeracaoEnergia* g = this->obterGeracaoEnergia(periodo);

	long double resultado = pow(g->quantidade, 2);

	resultado *= this->coeficiente_custo_termica_a2;
	resultado += this->coeficiente_custo_termica_a1 * g->quantidade;
	resultado += this->coeficiente_custo_termica_a0;

//	cout << "Resultado: " << periodo << "\n";
	return resultado;
}

long double UsinaTermica::iniciarProcessoDesativacao(int periodo) {
	long double resultado = 0.0;
	if (find(this->periodos_desativacao_obrigatorio.begin(), this->periodos_desativacao_obrigatorio.end(), periodo) != this->periodos_desativacao_obrigatorio.end()) {
		double status = this->statusUsina(periodo);
		double result = this->desativarUsina(periodo);
		double novoStatus = this->statusUsina(periodo);

		if (status != novoStatus) {
			this->adicionarPeriodosDesativacaoObrigatorio(periodo);
		}

		return result;
	}
	bool previsao;
	if (this->verificarTempoMinimoAtivacao(periodo)) {
		previsao = false;
		this->adicionarPeriodosDesativacaoObrigatorio(periodo);
	}
	else {
		previsao = true;
	}

	return this->desativarUsina(periodo, previsao);
}

#endif

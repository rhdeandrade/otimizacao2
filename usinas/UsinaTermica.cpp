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
	this->tempoMinimoAtivada = 3;
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
	if (find(this->periodosDesativacaoObrigatorio.begin(), this->periodosDesativacaoObrigatorio.end(), periodo) != this->periodosDesativacaoObrigatorio.end()) {
		long double status = this->statusUsina(periodo);
		long double result = this->desativarUsina(periodo);
		long double novoStatus = this->statusUsina(periodo);

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

long double UsinaTermica::statusUsina(int periodo) {
	GeracaoEnergia* geracao = this->obterGeracaoEnergia(periodo);

	if (geracao->quantidade == 0) {
		return 0;
	}
	if (geracao->quantidade == this->quantidadeGeracaoMin) {
		return 0;
	}
	else {
		long double resultado = geracao->quantidade * 100;
		resultado /= this->quantidade_geracao_max;
		return resultado;
	}
}

void UsinaTermica::adicionarPeriodosDesativacaoObrigatorio(int periodoBase) {
	for (int i = 0; i < this->periodosDesativacaoObrigatorio.size(); i++)
	{
		if (this->periodosDesativacaoObrigatorio.at(i) == periodoBase) {
			this->periodosDesativacaoObrigatorio.erase(this->periodosDesativacaoObrigatorio.begin() + i);
		}
	}

	for (int i = 1; i < (int) this->tempo_minimo_desativada; ++i)
	{
		periodoBase++;
		if (periodoBase == 60)
			return;

		this->periodosDesativacaoObrigatorio.push_back(periodoBase);
	}
}

bool UsinaTermica::verificarTempoMinimoAtivacao(int periodo) {
	for (int i = 0; i < (int) this->tempoMinimoAtivada; ++i)
	{
		periodo--;
		if (periodo == 0) {
			return false;
		}

		if (this->statusUsina(periodo) == 0) {
			return false;
		}
	}

	return true;
}

long double UsinaTermica::desativarUsina(int periodo, bool previsao) {
  long double result = 0;
  GeracaoEnergia* geracao = this->obterGeracaoEnergia(periodo);

  if (!previsao) {
    result = geracao->quantidade - this->quantidadeGeracaoMin;
    geracao->quantidade = this->quantidadeGeracaoMin;
  }

  return result;
}

#endif

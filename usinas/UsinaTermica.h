/*
 * UsinaTermica.h
 *
 *  Created on: 10/10/2013
 *      Author: raphael
 */

#ifndef USINATERMICA_H_
#define USINATERMICA_H_

#include <iostream>
#include "Usina.h"

using namespace std;


class UsinaTermica : public Usina {
public:
	long double quantidade_geracao_max;
	long double quantidadeGeracaoMin;
	long double coeficiente_custo_termica_a2;
	long double coeficiente_custo_termica_a1;
	long double coeficiente_custo_termica_a0;
	long double tempoMinimoAtivada;
	long double tempo_minimo_desativada;
	vector<int> periodosDesativacaoObrigatorio;

	UsinaTermica();
	long double custoTermicaMegaWattMedio(int periodo);
	long double iniciarProcessoDesativacao(int periodo);
	long double statusUsina(int periodo);
	void adicionarPeriodosDesativacaoObrigatorio(int periodoBase);
	bool verificarTempoMinimoAtivacao(int periodo);
	long double desativarUsina(int periodo, bool previsao = false);


};

#endif /* USINATERMICA_H_ */

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
	long double quantidade_geracao_min;
	long double coeficiente_custo_termica_a2;
	long double coeficiente_custo_termica_a1;
	long double coeficiente_custo_termica_a0;
	long double tempo_minimo_ativada;
	long double tempo_minimo_desativada;
	vector<int> periodos_desativacao_obrigatorio;

	UsinaTermica();
	long double custoTermicaMegaWattMedio(int periodo);
	long double iniciarProcessoDesativacao(int periodo);


};

#endif /* USINATERMICA_H_ */

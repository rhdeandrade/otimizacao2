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
	double quantidade_geracao_max;
	double quantidade_geracao_min;
	double coeficiente_custo_termica_a2;
	double coeficiente_custo_termica_a1;
	double coeficiente_custo_termica_a0;
	double tempo_minimo_ativada;
	double tempo_minimo_desativada;
	vector<int> periodos_desativacao_obrigatorio;

	UsinaTermica();


};

#endif /* USINATERMICA_H_ */

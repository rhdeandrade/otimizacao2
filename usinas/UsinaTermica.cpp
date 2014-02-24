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
//#include "Usina.cpp"

UsinaTermica::UsinaTermica() {
	this->coeficiente_custo_termica_a2 = 0;
	this->coeficiente_custo_termica_a0 = 0;
	this->coeficiente_custo_termica_a1 = 0;
	this->tempo_minimo_ativada = 3;
	this->tempo_minimo_desativada = 3;

}

long double UsinaTermica::custo_termica_mega_watt_medio(int periodo) {
	GeracaoEnergia* g = this->obterGeracaoEnergia(periodo);

	long double resultado = pow(g->quantidade, 2);

	resultado *= this->coeficiente_custo_termica_a2;
	resultado += this->coeficiente_custo_termica_a1 * g->quantidade;
	resultado += this->coeficiente_custo_termica_a0;
	return resultado;
}

#endif

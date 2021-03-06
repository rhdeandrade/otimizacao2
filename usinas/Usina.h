/*
 * Usina.h
 *
 *  Created on: 14/10/2013
 *      Author: raphael
 */

#ifndef USINA_H_
#define USINA_H_

#include "GeracaoEnergia.h"

using namespace std;


class Usina {
public:
	int id_usina;
	int id_subsistema;
	vector<GeracaoEnergia> geracoes;

	GeracaoEnergia* obterGeracaoEnergia(int periodo);
	long double totalEnergiaGerada();
	Usina();
};

#endif /* USINA_H_ */

/*
 * Subsistema.cpp
 *
 *  Created on: 22/10/2013
 *      Author: raphael
 */

#ifndef SUBSISTEMA_CPP_
#define SUBSISTEMA_CPP_

#include "Subsistema.h"

#include <new>
#include <vector>

#include "Deficit.h"
#include "DemandaEnergia.h"
#include "Intercambio.h"

Subsistema::Subsistema() {

}

Intercambio* Subsistema::obterIntercambioEnergia(int periodo) {
	for (int i = 0; i < this->intercambios.size(); i++) {
		if (this->intercambios.at(i).periodo == periodo) {
			return &this->intercambios.at(i);
		}
	}

	Intercambio* inter = new Intercambio();
	inter->periodo = 0;
	inter->quantidade_subsistema_1 = 0;
	inter->quantidade_subsistema_2 = 0;
	inter->quantidade_subsistema_3 = 0;
	inter->quantidade_subsistema_5 = 0;
	inter->quantidade_subsistema_4 = 0;
	return inter;
}

DemandaEnergia* Subsistema::obterDemandaEnergia(int periodo) {
	for (int i = 0; i < this->demandas.size(); i++) {
		if (this->demandas.at(i).periodo == periodo) {
			return &this->demandas.at(i);
		}
	}

	DemandaEnergia* d = new DemandaEnergia();
	d->periodo = 0;
	d->quantidade = 0;

	return d;
}

Deficit* Subsistema::obterDeficitSubsistema(int periodo) {
	for (int i = 0; i < this->deficits.size(); i++) {
		//cout << periodo << " --- " << this->deficits.at(i).periodo << " ---- " << this->deficits.at(i).deficit << "\n";
		if (this->deficits.at(i).periodo == periodo) {
			return &this->deficits.at(i);
		}
	}

	Deficit* d = new Deficit();
	d->deficit = 0;
	d->periodo = 0;

	return d;
}

long double Subsistema::custoDeficit(int periodo) {
	Deficit* deficit = obterDeficitSubsistema(periodo);

	double result = 0;
	if (deficit != NULL) {
		result = pow(deficit->deficit, 2);
		result *= this->coeficiente_custo_deficit_a2;
		result += this->coeficiente_custo_deficit_a1 * deficit->deficit;
		result += this->coeficiente_custo_deficit_a0;
	}
	return result;
}
#endif

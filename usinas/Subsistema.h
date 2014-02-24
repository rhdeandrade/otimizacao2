/*
 * Subsistema.h
 *
 *  Created on: 22/10/2013
 *      Author: raphael
 */

#ifndef SUBSISTEMA_H_
#define SUBSISTEMA_H_

#include "DemandaEnergia.h"
#include "Deficit.h"
#include "Intercambio.h"

using namespace std;


class Subsistema {
public:
    int id_subsistema;
    long double coeficiente_custo_deficit_a2;
    long double coeficiente_custo_deficit_a1;
    long double coeficiente_custo_deficit_a0;

    long double intercambio_minimo;
    long double intercambio_maximo;
    long double demanda;

    vector<DemandaEnergia> demandas;
    vector<Deficit> deficits;
    vector<Intercambio> intercambios;


    Intercambio* obterIntercambioEnergia(int periodo);
    DemandaEnergia* obterDemandaEnergia(int periodo);
    Deficit* obterDeficitSubsistema(int periodo);
    long double custoDeficit(int periodo);
	Subsistema();
};

#endif /* SUBSISTEMA_H_ */

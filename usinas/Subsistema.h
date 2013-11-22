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
    double coeficiente_custo_deficit_a2;
    double coeficiente_custo_deficit_a1;
    double coeficiente_custo_deficit_a0;

    double intercambio_minimo;
    double intercambio_maximo;
    double demanda;

    vector<DemandaEnergia> demandas;
    vector<Deficit> deficits;
    vector<Intercambio> intercambios;


    Intercambio* obterIntercambioEnergia(int periodo);
    DemandaEnergia* obterDemandaEnergia(int periodo);
    Deficit* obterDeficitSubsistema(int periodo);

	Subsistema();
};

#endif /* SUBSISTEMA_H_ */

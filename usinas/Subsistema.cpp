/*
 * Subsistema.cpp
 *
 *  Created on: 22/10/2013
 *      Author: raphael
 */

#ifndef SUBSISTEMA_CPP_
#define SUBSISTEMA_CPP_

#include "Subsistema.h"

Subsistema::Subsistema() {
	// TODO Auto-generated constructor stub

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

  return NULL;
}

Deficit* Subsistema::obterDeficitSubsistema(int periodo) {
  for (int i = 0; i < this->deficits.size(); i++) {
    if (this->deficits.at(i).periodo == periodo) {
      return &this->deficits.at(i);
    }
  }

  return NULL;
}
#endif

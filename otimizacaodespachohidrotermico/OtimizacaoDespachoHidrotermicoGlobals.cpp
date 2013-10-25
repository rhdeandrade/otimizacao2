/*
 * OtimizacaoDespachoHidrotermicoGlobals.cpp
 *
 *  Created on: 24/10/2013
 *      Author: raphael
 */

#ifndef OTIMIZACAODESPACHOHIDROTERMICOGLOBALS_CPP_
#define OTIMIZACAODESPACHOHIDROTERMICOGLOBALS_CPP_

#include "OtimizacaoDespachoHidrotermicoGlobals.h"

OtimizacaoDespachoHidrotermicoGlobals* OtimizacaoDespachoHidrotermicoGlobals::instancia;

OtimizacaoDespachoHidrotermicoGlobals::OtimizacaoDespachoHidrotermicoGlobals() {
	cascata74.push_back(74);
	cascata74.push_back(76);
	cascata74.push_back(77);
	cascata74.push_back(71);
	cascata74.push_back(72);
	cascata74.push_back(73);
	cascata74.push_back(77);
	cascata74.push_back(78);
	cascata74.push_back(82);

}

OtimizacaoDespachoHidrotermicoGlobals* OtimizacaoDespachoHidrotermicoGlobals::obterInstancia() {
	if (instancia == NULL) {
		instancia = new OtimizacaoDespachoHidrotermicoGlobals();
	}
	return instancia;
}

#endif

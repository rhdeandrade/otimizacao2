/*
 * Usina.cpp
 *
 *  Created on: 14/10/2013
 *      Author: raphael
 */
#ifndef USINA_CPP_
#define USINA_CPP_

#include "Usina.h"

Usina::Usina() {

}

GeracaoEnergia* Usina::obterGeracaoEnergia(int periodo) {


	for (int i = 0; i < this->geracoes.size(); i++) {
		GeracaoEnergia* g = &this->geracoes.at(i);
		if (g->periodo == periodo)
			return g;
	}

	GeracaoEnergia* geracao = new GeracaoEnergia();
	geracao->periodo = periodo;

	return geracao;
}

#endif

/*
 * Reservatorio.cpp
 *
 *  Created on: 14/10/2013
 *      Author: raphael
 */

#ifndef RESERVATORIO_CPP_
#define RESERVATORIO_CPP_

#include "Reservatorio.h"

#include <new>
#include <vector>

#include "HistoricoOperacaoReservatorio.h"

Reservatorio::Reservatorio() {

}

HistoricoOperacaoReservatorio* Reservatorio::obterHistoricoOperacao(int periodo, double volumeInicial) {
	for (int i = 0; i < this->historicoOperacao.size(); i++) {
		if(this->historicoOperacao.at(i).periodo == periodo) {
			return &this->historicoOperacao.at(i);
		}
	}

	HistoricoOperacaoReservatorio* historico = new HistoricoOperacaoReservatorio();

	historico->periodo = periodo;
	historico->volume = volumeInicial;

	return historico;
}

#endif

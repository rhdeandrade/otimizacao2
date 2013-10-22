/*
 * Reservatorio.h
 *
 *  Created on: 14/10/2013
 *      Author: raphael
 */

#ifndef RESERVATORIO_H_
#define RESERVATORIO_H_

#include <iostream>
#include "HistoricoOperacaoReservatorio.h"
using namespace std;


class Reservatorio {
public:

	double volume_maximo;
	double volume_minimo;
	double minimo_vazao_turbinada;
	double maximo_vazao_turbinada;
	double maximo_vazao_vertida;
	double defluencia_minima;
	/**
	 * @var Array of HistoricoOperacaoReservatorio
	 */
	vector<HistoricoOperacaoReservatorio> historicoOperacao;

	Reservatorio();
};

#endif /* RESERVATORIO_H_ */

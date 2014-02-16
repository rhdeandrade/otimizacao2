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

	long double volume_maximo;
	long double volume_minimo;
	long double minimo_vazao_turbinada;
	long double maximo_vazao_turbinada;
	long double maximo_vazao_vertida;
	long double defluencia_minima;
	/**
	 * @var Array of HistoricoOperacaoReservatorio
	 */
	vector<HistoricoOperacaoReservatorio> historicoOperacao;

	HistoricoOperacaoReservatorio* obterHistoricoOperacao(int periodo, long double volumeInicial);

	Reservatorio();
};

#endif /* RESERVATORIO_H_ */

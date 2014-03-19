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

	long double volumeMaximo;
	long double volumeMinimo;
	long double minimo_vazao_turbinada;
	long double maximo_vazao_turbinada;
	long double maximo_vazao_vertida;
	long double defluencia_minima;
	/**
	 * @var Array of HistoricoOperacaoReservatorio
	 */
	vector<HistoricoOperacaoReservatorio> historicoOperacao;

	HistoricoOperacaoReservatorio* obterHistoricoOperacao(int periodo, long double volumeInicial);
	long double obterTamanho();

	Reservatorio();
};

#endif /* RESERVATORIO_H_ */

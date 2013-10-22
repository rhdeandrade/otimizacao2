/*
 * Reservatorio.h
 *
 *  Created on: 14/10/2013
 *      Author: raphael
 */

#ifndef RESERVATORIO_H_
#define RESERVATORIO_H_

class Reservatorio {
public:

	float volumeMaximo;
	/**
	 * @var float
	 */
	float volumeMinimo;
	/**
	 * Valor padrão = 0
	 * @var float
	 */
	float minimoVazaoTurbinada = 0;
	/**
	 * @var float
	 */
	float maximoVazaoTurbinada;
	/**
	 * Valor = Infinito
	 * @var float
	 */
	float maximoVazaoVertida = 999999999;
	/**
	 * @var float
	 */
	float defluenciaMinima;
	/**
	 * @var Array of HistoricoOperacaoReservatorio
	 */
	vector<HistoricoOperacaoReservatorio>> historicoOperacao;

	Reservatorio();
};

#endif /* RESERVATORIO_H_ */

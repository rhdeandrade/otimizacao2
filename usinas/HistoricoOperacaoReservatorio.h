/*
 * HistoricoOperacaoReservatorio.h
 *
 *  Created on: 22/10/2013
 *      Author: raphael
 */

#ifndef HISTORICOOPERACAORESERVATORIO_H_
#define HISTORICOOPERACAORESERVATORIO_H_

class HistoricoOperacaoReservatorio {
public:
    int periodo;
    long double volume;
    long double vazaoTurbinada;
    long double vazaoVertida;
    long double afluencia_natural;
	HistoricoOperacaoReservatorio();
};

#endif /* HISTORICOOPERACAORESERVATORIO_H_ */

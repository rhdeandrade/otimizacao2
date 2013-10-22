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
    double volume;
    double vazao_turbinada;
    double vazao_vertida;
    double afluencia_natural;
	HistoricoOperacaoReservatorio();
};

#endif /* HISTORICOOPERACAORESERVATORIO_H_ */

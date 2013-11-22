/*
 * Restricao.h
 *
 *  Created on: 21/11/2013
 *      Author: raphael
 */

#ifndef RESTRICAO_H_
#define RESTRICAO_H_

#include "RestricaoAtendimentoDemanda.h"
#include "RestricaoBalancoHidrico.h"
#include "RestricaoDefluenciaMinima.h"
#include "RestricaoLimiteVariaveis.h"


class Restricao {
public:
	// TODO Auto-generated constructor stub
	RestricaoAtendimentoDemanda *atendimento_demanda;
	RestricaoBalancoHidrico *balanco_hidrico;
	RestricaoDefluenciaMinima *defluencia_minima;
	RestricaoLimiteVariaveis *limite_variaveis;

	Restricao();
};

#endif /* RESTRICAO_H_ */

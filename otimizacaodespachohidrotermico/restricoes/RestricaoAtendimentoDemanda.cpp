/*
 * RestricaoAtendimentoDemanda.cpp

 *
 *  Created on: 04/11/2013
 *      Author: raphael
 */

#ifndef RESTRICAOATENDIMENTODEMANDA_CPP_
#define RESTRICAOATENDIMENTODEMANDA_CPP_

#include "RestricaoAtendimentoDemanda.h"

RestricaoAtendimentoDemanda::RestricaoAtendimentoDemanda(vector<Subsistema> subsistemas, vector<UsinaHidreletrica> hidreletricas, vector<UsinaTermica> termicas) {
	this->hidreletricas = hidreletricas;
	this->subsistemas = subsistemas;
	this->termicas = termicas;

}

#endif

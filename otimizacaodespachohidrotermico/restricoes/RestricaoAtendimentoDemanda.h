/*
 * RestricaoAtendimentoDemanda.h
 *
 *  Created on: 04/11/2013
 *      Author: raphael
 */

#ifndef RESTRICAOATENDIMENTODEMANDA_H_
#define RESTRICAOATENDIMENTODEMANDA_H_


using namespace std;

class RestricaoAtendimentoDemanda {
public:
	RestricaoAtendimentoDemanda(vector<Subsistema> subsistemas, vector<UsinaHidreletrica> hidreletricas, vector<UsinaTermica> termicas);
};

#endif /* RESTRICAOATENDIMENTODEMANDA_H_ */

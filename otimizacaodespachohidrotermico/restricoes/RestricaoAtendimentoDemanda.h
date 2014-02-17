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
	vector<Subsistema> subsistemas;
	vector<UsinaHidreletrica> hidreletricas;
	vector<UsinaTermica> termicas;
	RestricaoAtendimentoDemanda(vector<Subsistema> subsistemas, vector<UsinaHidreletrica> hidreletricas, vector<UsinaTermica> termicas);
	void checkConstraint(vector<Subsistema> subsistemas);
	int errorThreshold();
};

#endif /* RESTRICAOATENDIMENTODEMANDA_H_ */

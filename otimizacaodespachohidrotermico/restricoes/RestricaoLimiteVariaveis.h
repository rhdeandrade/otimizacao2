/*
 * RestricaoLimiteVariaveis.h
 *
 *  Created on: 04/11/2013
 *      Author: raphael
 */

#ifndef RESTRICAOLIMITEVARIAVEIS_H_
#define RESTRICAOLIMITEVARIAVEIS_H_

using namespace std;

class RestricaoLimiteVariaveis {
public:
	vector<UsinaHidreletrica> hidreletricas;
	RestricaoLimiteVariaveis(vector<UsinaHidreletrica> hidreletricas, vector<UsinaTermica> termicas);
};

#endif /* RESTRICAOLIMITEVARIAVEIS_H_ */

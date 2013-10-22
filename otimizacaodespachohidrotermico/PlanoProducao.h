/*
 * PlanoProducao.h
 *
 *  Created on: 30/09/2013
 *      Author: raphael
 */

#ifndef PLANOPRODUCAO_H_
#define PLANOPRODUCAO_H_



class PlanoProducao {

public:
	PlanoProducao();

	vector<UsinaTermica> termicas;
	vector<UsinaHidreletrica> hidreletricas;
	vector<Subsistema> subsistemas;

};

#endif /* PLANOPRODUCAO_H_ */

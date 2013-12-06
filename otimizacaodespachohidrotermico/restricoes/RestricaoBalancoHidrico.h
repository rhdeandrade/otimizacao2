/*
 * RestricaoBalancoHidrico.h
 *
 *  Created on: 04/11/2013
 *      Author: raphael
 */

#ifndef RESTRICAOBALANCOHIDRICO_H_
#define RESTRICAOBALANCOHIDRICO_H_


using namespace std;

class RestricaoBalancoHidrico {
public:
	vector<UsinaHidreletrica> hidreletricas;
	RestricaoBalancoHidrico(vector<UsinaHidreletrica> hidreletricas);
	void checkConstraint();
	int errorThreshold();
};

#endif /* RESTRICAOBALANCOHIDRICO_H_ */

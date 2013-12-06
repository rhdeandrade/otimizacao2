/*
 * RestricaoDefluenciaMinima.h
 *
 *  Created on: 04/11/2013
 *      Author: raphael
 */

#ifndef RESTRICAODEFLUENCIAMINIMA_H_
#define RESTRICAODEFLUENCIAMINIMA_H_

using namespace std;

class RestricaoDefluenciaMinima {
public:
	vector<UsinaHidreletrica> hidreletricas;

	RestricaoDefluenciaMinima(vector<UsinaHidreletrica> hidreletricas);
	void checkConstraint();
	int errorThreshold();
};

#endif /* RESTRICAODEFLUENCIAMINIMA_H_ */

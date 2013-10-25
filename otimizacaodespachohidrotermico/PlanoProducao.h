/*
 * PlanoProducao.h
 *
 *  Created on: 30/09/2013
 *      Author: raphael
 */

#ifndef PLANOPRODUCAO_H_
#define PLANOPRODUCAO_H_

#include "../usinas/Subsistema.h"
#include "../usinas/UsinaHidreletrica.h"
#include "../usinas/UsinaTermica.h"

class PlanoProducao {

public:
	PlanoProducao();

	vector<UsinaTermica> termicas;
	vector<UsinaHidreletrica> hidreletricas;
	vector<Subsistema> subsistemas;
	void ativarRestricoes(bool balancoHidrico, bool atendimentoDemanda, bool defluenciaMinima, bool limiteVariaveis);

};

#endif /* PLANOPRODUCAO_H_ */

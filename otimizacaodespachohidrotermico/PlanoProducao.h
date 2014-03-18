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

#include "restricoes/Restricao.h"
#include "OperacaoAtomicaQuatro.h"

class PlanoProducao {

public:
	PlanoProducao();
	PlanoProducao(PlanoProducao *obj);
	vector<UsinaTermica> termicas;
	vector<UsinaHidreletrica> hidreletricas;
	vector<Subsistema> subsistemas;
	Restricao restricoes;
	void ativarRestricoes(bool balancoHidrico, bool atendimentoDemanda, bool defluenciaMinima, bool limiteVariaveis);
	long double objectiveFunctionValue();
	void perturbation(int atomicOperationId, int counter);
	long double calcularValorPresente(int periodo);


};

#endif /* PLANOPRODUCAO_H_ */

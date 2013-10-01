/*
 * OtimizacaoDespachoHidrotermico.h
 *
 *  Created on: 30/09/2013
 *      Author: raphael
 */

#ifndef OTIMIZACAODESPACHOHIDROTERMICO_H_
#define OTIMIZACAODESPACHOHIDROTERMICO_H_

#include <iostream>
#include "sstream"

#include "PlanoProducao.h"

using namespace std;

class OtimizacaoDespachoHidrotermico {
public:
	PlanoProducao planoProducao;

	OtimizacaoDespachoHidrotermico();
	void carregarDados(string lote, int serie);
};

#endif /* OTIMIZACAODESPACHOHIDROTERMICO_H_ */

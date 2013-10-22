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
#include <vector>
#include "../usinas/UsinaTermica.h"
#include "../usinas/UsinaHidreletrica.h"
#include "PlanoProducao.h"
#include "CarregadorDados.h"



using namespace std;

class OtimizacaoDespachoHidrotermico {
public:
	PlanoProducao planoProducao;
	CarregadorDados carregadorDados;

	OtimizacaoDespachoHidrotermico();
	void carregarDados(string lote, int serie);
};

#endif /* OTIMIZACAODESPACHOHIDROTERMICO_H_ */

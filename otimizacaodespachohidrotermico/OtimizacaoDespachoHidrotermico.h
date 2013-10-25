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
#include "OtimizacaoDespachoHidrotermicoGlobals.h"



using namespace std;

class OtimizacaoDespachoHidrotermico {
public:
	PlanoProducao planoProducao;
	CarregadorDados carregadorDados;

	OtimizacaoDespachoHidrotermico();
	void carregarDados(string lote, int serie);
	void ativarRestricoes(bool balancoHidrico, bool atendimentoDemanda, bool defluenciaMinima, bool limiteVariaveis);
};

#endif /* OTIMIZACAODESPACHOHIDROTERMICO_H_ */

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
#include "../heuristicsearch/HillClimbing.h"

using namespace std;

class OtimizacaoDespachoHidrotermico {
public:
	PlanoProducao planoProducao;
	CarregadorDados carregadorDados;
	vector<string> errors;
	OtimizacaoDespachoHidrotermico();
	void carregarDados(string lote, int serie);
	void ativarRestricoes(bool balancoHidrico, bool atendimentoDemanda, bool defluenciaMinima, bool limiteVariaveis);
	void validarPlanoProducao();
	void executarOtimizacaoHillClimbing(int operacaoAtomica, int numeroMaximoIteracoes, int numeroMaximoIteracoesPerturbacao);
};

#endif /* OTIMIZACAODESPACHOHIDROTERMICO_H_ */

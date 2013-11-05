/*
 * OtimizacaoDespachoHidrotermicoGlobals.h
 *
 *  Created on: 24/10/2013
 *      Author: raphael
 */

#ifndef OTIMIZACAODESPACHOHIDROTERMICOGLOBALS_H_
#define OTIMIZACAODESPACHOHIDROTERMICOGLOBALS_H_

#include <iostream>

using namespace std;


class OtimizacaoDespachoHidrotermicoGlobals {
public:
	vector<int> cascata74;
	vector<UsinaHidreletrica> hidreletricas;
	const static double TAXA_DESCONTO = 0.00948879;
	const static int LIMIAR_ERRO_BALANCO_HIDRICO = 16;
	const static int NUM_PERIODO = 60;

	static void atualizarPlanoProducao(PlanoProducao planoProducao);
	static OtimizacaoDespachoHidrotermicoGlobals* obterInstancia();
	static vector<Usina> obterUsinasDoSubsistema(vector<Usina> usinas, int idUsina);

private:
	OtimizacaoDespachoHidrotermicoGlobals();
	static OtimizacaoDespachoHidrotermicoGlobals* instancia;
};

#endif /* OTIMIZACAODESPACHOHIDROTERMICOGLOBALS_H_ */

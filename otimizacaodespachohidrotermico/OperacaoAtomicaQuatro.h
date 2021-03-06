/*
 * OperacaoAtomicaQuatro.h
 *
 *  Created on: 13/03/2014
 *      Author: raphael
 */

#ifndef OPERACAOATOMICAQUATRO_H_
#define OPERACAOATOMICAQUATRO_H_


#include "PlanoProducao.h"

using namespace std;

class PlanoProducao;

class OperacaoAtomicaQuatro {
public:
	OperacaoAtomicaQuatro();
	PlanoProducao* execute(PlanoProducao* planoProducao, int periodo);

	long double planejarMaximizacaoEnergiaHidraulica(vector<UsinaHidreletrica>* hidreletricas, int periodo);
	long double minimizarEnergiaTermica(vector<UsinaTermica>* termicas, int periodo, long double* totalEnergiaHidraulicaSobrando);
	long double produzirEnergiaHidraulica(vector<UsinaHidreletrica>* hidreletricas, int periodo, double totalEnergiaTermicaDesligada);
};

#endif /* OPERACAOATOMICAQUATRO_H_ */

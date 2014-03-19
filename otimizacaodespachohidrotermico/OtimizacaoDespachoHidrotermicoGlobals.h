/*
 * OtimizacaoDespachoHidrotermicoGlobals.h
 *
 *  Created on: 24/10/2013
 *      Author: raphael
 */

#ifndef OTIMIZACAODESPACHOHIDROTERMICOGLOBALS_H_
#define OTIMIZACAODESPACHOHIDROTERMICOGLOBALS_H_

#include "PlanoProducao.h"
#include "../util/Report.h"

#include <iostream>

using namespace std;

class OtimizacaoDespachoHidrotermicoGlobals {
public:
	vector<int> cascata74;
	vector<UsinaHidreletrica> hidreletricas;
	const static long double TAXA_DESCONTO = 0.00948879;
	const static int LIMIAR_ERRO_BALANCO_HIDRICO = 16;
	const static int NUM_PERIODO = 60;

	static void atualizarPlanoProducao(PlanoProducao* planoProducao);
	static OtimizacaoDespachoHidrotermicoGlobals* obterInstancia();
	static vector<UsinaTermica> obterUsinasTermicasDoSubsistema(vector<UsinaTermica> usinas, int idUsina);
	static vector<UsinaHidreletrica> obterUsinasHidreletricasDoSubsistema(vector<UsinaHidreletrica> usinas, int idUsina);
	static long double converterHectometroCubicoParaMetroCubico(long double valor, int periodo);
	static long double converterMetroCubicoParaHectometroCubico(long double valor, int periodo);
	static long double quantidadeSegundosMes(int periodo);
	static long double quantidadeHorasMes(int periodo);
	static long double quantidadeDiasMes(int periodo);
	static int mesCorrente(int periodo);
	static UsinaHidreletrica obterUsina(int id_usina);
	static vector<UsinaHidreletrica> ordenarHidreletricasPorTamanhoReservatorio(vector<UsinaHidreletrica> hidreletricas, bool comJusantes);
	static void obterUsinaJusante(UsinaHidreletrica h, vector<UsinaHidreletrica> result);
	static vector<UsinaTermica> obterTermicasComPrioridadeDesativacao(vector<UsinaTermica> termicas, int periodo);
	static vector<UsinaTermica> ordenarTermicasPorCusto(vector<UsinaTermica> termicas, int periodo);



private:
	OtimizacaoDespachoHidrotermicoGlobals();
	static OtimizacaoDespachoHidrotermicoGlobals* instancia;
};

#endif /* OTIMIZACAODESPACHOHIDROTERMICOGLOBALS_H_ */

/*
 * OtimizacaoDespachoHidrotermico.cpp
 *
 *  Created on: 30/09/2013
 *      Author: raphael
 */


#ifndef OTIMIZACAODESPACHOHIDROTERMICO_CPP_
#define OTIMIZACAODESPACHOHIDROTERMICO_CPP_

#include "OtimizacaoDespachoHidrotermico.h"
#include "../usinas/UsinaTermica.cpp"
#include "../usinas/UsinaHidreletrica.cpp"
#include "../usinas/Subsistema.cpp"
#include "../usinas/DemandaEnergia.cpp"
#include "../usinas/Deficit.cpp"
#include "../usinas/Intercambio.cpp"
#include "../usinas/Reservatorio.cpp"
#include "../usinas/HistoricoOperacaoReservatorio.cpp"
#include "../usinas/GeracaoEnergia.cpp"
#include "PlanoProducao.cpp"
#include "CarregadorDados.cpp"
#include "OtimizacaoDespachoHidrotermicoGlobals.cpp"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>

OtimizacaoDespachoHidrotermico::OtimizacaoDespachoHidrotermico() {

}


void OtimizacaoDespachoHidrotermico::carregarDados(string lote, int serie) {
	cout << "Tipo: " << lote << " Numero: " << serie << "\n";

	stringstream ss;

	ss << serie;

	string termicas =  "otimizacaodespachohidrotermico/dados/" + lote + "/Termicas.txt";
	string geracaoTermicas =  "otimizacaodespachohidrotermico/dados/" + lote + "/planoproducao/termoSaida_" + ss.str() + ".txt";
	string hidreletricas =  "otimizacaodespachohidrotermico/dados/" + lote + "/Hidreletricas.txt";
	string geracaoHidreletricas =  "otimizacaodespachohidrotermico/dados/" + lote + "/planoproducao/hidroSaida_" + ss.str() + ".txt";
	string subsistemas =  "otimizacaodespachohidrotermico/dados/" + lote + "/Subsistemas.txt";
	string deficits =  "otimizacaodespachohidrotermico/dados/" + lote + "/planoproducao/DeficitsSaida_" + ss.str() + ".txt";
	string demanda =  "otimizacaodespachohidrotermico/dados/" + lote + "/planoproducao/Demanda.txt";
	string intercambios =  "otimizacaodespachohidrotermico/dados/" + lote + "/planoproducao/IntercambiosSaida_" + ss.str() + ".txt";

	CarregadorDados c(termicas, geracaoTermicas,
					hidreletricas, geracaoHidreletricas,
					subsistemas, deficits,
					demanda, intercambios);

	this->carregadorDados = c;

	this->planoProducao.termicas = this->carregadorDados.carregar_usinas_termicas();
	this->planoProducao.hidreletricas = this->carregadorDados.carregarUsinasHidreletricas();
	this->planoProducao.subsistemas = this->carregadorDados.carregarSubsistema();

	OtimizacaoDespachoHidrotermicoGlobals::obterInstancia()->hidreletricas = this->planoProducao.hidreletricas;

}

void OtimizacaoDespachoHidrotermico::ativarRestricoes(bool balancoHidrico, bool atendimentoDemanda, bool defluenciaMinima, bool limiteVariaveis) {
	planoProducao.ativarRestricoes(balancoHidrico, atendimentoDemanda, defluenciaMinima, limiteVariaveis);
}

#endif

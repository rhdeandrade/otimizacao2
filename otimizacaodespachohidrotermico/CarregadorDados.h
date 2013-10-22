/*
 * CarregadorDados.h
 *
 *  Created on: 07/10/2013
 *      Author: raphael
 */

#ifndef CARREGADORDADOS_H_
#define CARREGADORDADOS_H_

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include "../util/FileHandler.h"

using namespace std;
using namespace boost;


class CarregadorDados {
public:
	string arquivoDadosTermicas;
	string arquivoGeracoesTermicas;
	string arquivoDadosHidreletricas;
	string arquivoGeracoesHidreletricas;
	string arquivoDadosSubsistemas;
	string arquivoDeficitsSubsistemas;
	string arquivoDemandasSubsistemas;
	string arquivoIntercambiosSubsistemas;

	CarregadorDados();
	CarregadorDados(string arquivoDadosTermicas, string arquivoGeracoesTermicas, string arquivoDadosHidreletricas, string arquivoGeracoesHidreletricas,
			string arquivoDadosSubsistemas, string arquivoDeficitsSubsistemas, string arquivoDemandasSubsistemas, string arquivoIntercambiosSubsistemas);

    vector<UsinaTermica> carregar_usinas_termicas();
    vector<GeracaoEnergia> carregar_geracoes_usinas_termicas(int id_usina, string arquivo);
    vector<UsinaHidreletrica> carregarUsinasHidreletricas();

    //vector<GeracaoEnergia> carregar_geracoes_usinas_termicas(int id_usina, string arquivo);

    //vector<UsinaHidreletrica> carregar_usinas_hidreletricas();

};

#endif /* CARREGADORDADOS_H_ */

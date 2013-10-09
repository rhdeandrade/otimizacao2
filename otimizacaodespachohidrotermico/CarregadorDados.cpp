/*
 * CarregadorDados.cpp
 *
 *  Created on: 07/10/2013
 *      Author: raphael
 */

#include "CarregadorDados.h"

CarregadorDados::CarregadorDados(string arquivoDadosTermicas, string arquivoGeracoesTermicas, string arquivoDadosHidreletricas, string arquivoGeracoesHidreletricas,
								string arquivoDadosSubsistemas, string arquivoDeficitsSubsistemas, string arquivoDemandasSubsistemas, string arquivoIntercambiosSubsistemas) {

	this->arquivoDadosTermicas = arquivoDadosTermicas;
	this->arquivoDadosHidreletricas = arquivoDadosHidreletricas;
	this->arquivoGeracoesTermicas = arquivoDadosTermicas;
	this->arquivoGeracoesHidreletricas = arquivoGeracoesHidreletricas;
	this->arquivoDadosSubsistemas = arquivoDadosSubsistemas;
	this->arquivoDeficitsSubsistemas = arquivoDeficitsSubsistemas;
	this->arquivoDemandasSubsistemas = arquivoDemandasSubsistemas;
	this->arquivoIntercambiosSubsistemas = arquivoIntercambiosSubsistemas;

}

CarregadorDados::CarregadorDados() {

}


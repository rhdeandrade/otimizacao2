/*
 * CarregadorDados.h
 *
 *  Created on: 07/10/2013
 *      Author: raphael
 */

#ifndef CARREGADORDADOS_H_
#define CARREGADORDADOS_H_

using namespace std;

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
};

#endif /* CARREGADORDADOS_H_ */

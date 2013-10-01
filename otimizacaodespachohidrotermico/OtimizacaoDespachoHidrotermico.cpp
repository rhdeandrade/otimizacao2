/*
 * OtimizacaoDespachoHidrotermico.cpp
 *
 *  Created on: 30/09/2013
 *      Author: raphael
 */

#include "OtimizacaoDespachoHidrotermico.h"
#include "PlanoProducao.cpp"


OtimizacaoDespachoHidrotermico::OtimizacaoDespachoHidrotermico() {

}


void OtimizacaoDespachoHidrotermico::carregarDados(string lote, int serie) {
	cout << "Tipo: " << lote << " Numero: " << serie << "\n";

	stringstream ss;

	ss << serie;

	string termicas =  "despachohidrotermico/dados/" + lote + "/Termicas.txt";
	string geracaoTermicas =  "despachohidrotermico/dados/" + lote + "/planoproducao/termoSaida_" + ss.str() + ".txt";
	string hidreletricas =  "despachohidrotermico/dados/" + lote + "/Hidreletricas.txt";
	string geracaoHidreletricas =  "despachohidrotermico/dados/" + lote + "/planoproducao/hidroSaida_" + ss.str() + ".txt";
	string subsistemas =  "despachohidrotermico/dados/" + lote + "/Subsistemas.txt";
	string deficits =  "despachohidrotermico/dados/" + lote + "/planoproducao/DeficitsSaida_" + ss.str() + ".txt";
	string demanda =  "despachohidrotermico/dados/" + lote + "/planoproducao/Demanda.txt";
	string intercambios =  "despachohidrotermico/dados/" + lote + "/planoproducao/IntercambiosSaida_" + ss.str() + ".txt";

}


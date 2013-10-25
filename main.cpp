/*
 * main.cpp
 *
 *  Created on: 26/09/2013
 *      Author: raphael
 */



#include "otimizacaodespachohidrotermico/OtimizacaoDespachoHidrotermico.cpp"

using namespace std;


int main() {
	OtimizacaoDespachoHidrotermico odh;
	odh.carregarDados("lote5", 10);
	odh.ativarRestricoes(true, true, true, true);

}


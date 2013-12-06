/*
 * main.cpp
 *
 *  Created on: 26/09/2013
 *      Author: raphael
 */



#include "otimizacaodespachohidrotermico/OtimizacaoDespachoHidrotermico.cpp"
#include <ctime>
using namespace std;


int main() {
	OtimizacaoDespachoHidrotermico odh;
	odh.carregarDados("lote5", 10);
	odh.ativarRestricoes(true, true, true, true);

	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	cout << "Start: " << buf << "\n";

	OtimizacaoDespachoHidrotermicoGlobals::atualizarPlanoProducao(odh.planoProducao);
	odh.validarPlanoProducao();

}

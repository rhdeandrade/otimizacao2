/*
 * main.cpp
 *
 *  Created on: 26/09/2013
 *      Author: raphael
 */



#include "otimizacaodespachohidrotermico/OtimizacaoDespachoHidrotermico.cpp"
#include "util/Report.h"
#include "util/Report.cpp"
#include <ctime>
using namespace std;


int main() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	cout.setf(ios::fixed);
	cout.precision(20);

	OtimizacaoDespachoHidrotermico odh;
	odh.carregarDados("lote5", 10);
	//Report::imprimir_resultados(odh.planoProducao);

	odh.ativarRestricoes(true, true, true, true);

	cout << "Start: " << buf << "\n";

	Report::imprimir_resultados(odh.planoProducao);
	OtimizacaoDespachoHidrotermicoGlobals::atualizarPlanoProducao(&odh.planoProducao);
	Report::imprimir_resultados(odh.planoProducao);
	odh.validarPlanoProducao();

	int operacaoAtomica = 4;

	cout << "Executando operação atômica: " << operacaoAtomica << "\n";

	odh.executarOtimizacaoHillClimbing(operacaoAtomica, 60, 3);
	odh.validarPlanoProducao();

	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	Report::imprimir_resultados(odh.planoProducao);
	cout << "End: " << buf << "\n";

}

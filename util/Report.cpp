/*
 * Report.cpp
 *
 *  Created on: 13/12/2013
 *      Author: raphael
 */

#ifndef REPORT_CPP_
#define REPORT_CPP_


#include "Report.h"
#include <iostream>

Report::Report() {

}

void Report::imprimir_resultados(PlanoProducao plano_producao) {
  cout << "Funcao Objetivo: ";
  cout << plano_producao.objectiveFunctionValue() << "\n";

  double total_energia_hidraulica = 0;

  for (int i = 0; i < plano_producao.hidreletricas.size(); i++) {
    total_energia_hidraulica += plano_producao.hidreletricas.at(i).totalEnergiaGerada();
  }

  cout << "Total Energia Hidraulica: " << total_energia_hidraulica << "\n";

  double total_energia_termica = 0;
  for (int i = 0; i < plano_producao.termicas.size(); i++) {
    total_energia_termica += plano_producao.termicas.at(i).totalEnergiaGerada();
  }

  cout << "Total Energia Termica: " << total_energia_termica << "\n";

  double total_deficit = 0;

  for (int i = 0; i < plano_producao.subsistemas.size(); i++) {
    for (int j = 0; j < plano_producao.subsistemas.at(i).deficits.size(); j++) {
      total_deficit += plano_producao.subsistemas.at(i).deficits.at(j).deficit;
    }
  }

  cout << "Total Deficit: " << total_deficit << "\n";

}

#endif

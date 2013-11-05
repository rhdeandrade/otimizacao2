#ifndef PLANOPRODUCAO_CPP_
#define PLANOPRODUCAO_CPP_


/*
 * PlanoProducao.cpp
 *
 *  Created on: 30/09/2013
 *      Author: raphael
 */

#include "PlanoProducao.h"
#include "../usinas/Subsistema.cpp"
#include "../usinas/UsinaHidreletrica.cpp"
#include "../usinas/UsinaTermica.cpp"
#include "restricoes/RestricaoAtendimentoDemanda.cpp"
#include "restricoes/RestricaoDefluenciaMinima.cpp"
#include "restricoes/RestricaoBalancoHidrico.cpp"
#include "restricoes/RestricaoLimiteVariaveis.cpp"

PlanoProducao::PlanoProducao() {
	// TODO Auto-generated constructor stub

}

std::vector<string> FileHandler::open_file(string file_name) {

  fstream myfile;
  std::vector<string> dados;
  string line;

  //cout << "Open File: " << file_name << "\n";

  myfile.open(file_name.c_str(), fstream::in);

  if (myfile.is_open()) {

    while (!myfile.eof()) {

      getline(myfile, line);

      if (!line.empty()) {
        dados.push_back(line);
      }
    }

    myfile.close();
  }
  else {
    cout << "Arquivo não encontrado\n";
  }

  return dados;

}


void PlanoProducao::ativarRestricoes(bool balancoHidrico, bool atendimentoDemanda, bool defluenciaMinima, bool limiteVariaveis) {
	if (balancoHidrico) {
		RestricaoBalancoHidrico restricaoBalandoHidrico(this->hidreletricas);
		this->restricoes.push_back((void)restricaoBalandoHidrico);
	}
	if (atendimentoDemanda) {
		RestricaoAtendimentoDemanda restricaoAtendimentoDemanda(this->subsistemas, this->hidreletricas, this->termicas);
		this->restricoes.push_back((void)restricaoAtendimentoDemanda);
	}
	if (defluenciaMinima) {
		RestricaoDefluenciaMinima restricaoDefluenciaMinima(this->hidreletricas);
		this->restricoes.push_back((void)restricaoDefluenciaMinima);
	}
	if (limiteVariaveis) {
		RestricaoLimiteVariaveis restricaoLimiteVariaveis(this->hidreletricas, this->termicas);
		this->restricoes.push_back((void)restricaoLimiteVariaveis);
	}

}

#endif

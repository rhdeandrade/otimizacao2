/*
 * PlanoProducao.cpp
 *
 *  Created on: 30/09/2013
 *      Author: raphael
 */

#include "PlanoProducao.h"

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



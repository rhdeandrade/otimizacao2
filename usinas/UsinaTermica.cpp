/*
 * UsinaTermica.cpp
 *
 *  Created on: 10/10/2013
 *      Author: raphael
 */

#include "UsinaTermica.h"
#include "Usina.cpp"

UsinaTermica::UsinaTermica() {
  this->coeficiente_custo_termica_a2 = 0;
  this->coeficiente_custo_termica_a0 = 0;
  this->coeficiente_custo_termica_a1 = 0;
  this->tempo_minimo_ativada = 3;
  this->tempo_minimo_desativada = 3;

}


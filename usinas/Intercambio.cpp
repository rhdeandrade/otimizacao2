/*
 * Intercambio.cpp
 *
 *  Created on: 22/10/2013
 *      Author: raphael
 */

#include "Intercambio.h"

Intercambio::Intercambio() {
	// TODO Auto-generated constructor stub

}

long double Intercambio::totalEnergiaEnviada() {
	long double resultado = this->quantidade_subsistema_1 + this->quantidade_subsistema_2 + this->quantidade_subsistema_3 + this->quantidade_subsistema_4 + this->quantidade_subsistema_5;
	return resultado;
}

long double Intercambio::totalEnergiaRecebida(int id_subsistema) {

	//cout << this->quantidade_subsistema_1 << " " << this->quantidade_subsistema_2 << " " << this->quantidade_subsistema_3 << " " << this->quantidade_subsistema_4 << " " << this->quantidade_subsistema_5 << "\n";

	if (id_subsistema == 1)
		return  this->quantidade_subsistema_1;
	else if (id_subsistema == 2)
		return this->quantidade_subsistema_2;
	else if (id_subsistema == 3)
		return this->quantidade_subsistema_3;
	else if (id_subsistema == 4)
		return this->quantidade_subsistema_4;
	else if (id_subsistema == 5)
		return this->quantidade_subsistema_5;

  return 0.0;
}


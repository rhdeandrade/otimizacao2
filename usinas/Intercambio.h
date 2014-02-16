/*
 * Intercambio.h
 *
 *  Created on: 22/10/2013
 *      Author: raphael
 */

#ifndef INTERCAMBIO_H_
#define INTERCAMBIO_H_

class Intercambio {
public:
	int periodo;
	long double quantidade_subsistema_1;
	long double quantidade_subsistema_2;
	long double quantidade_subsistema_3;
	long double quantidade_subsistema_4;
	long double quantidade_subsistema_5;

	Intercambio();
	long double totalEnergiaEnviada();
	long double totalEnergiaRecebida(int id_subsistema);
};

#endif /* INTERCAMBIO_H_ */

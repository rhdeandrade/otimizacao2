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
	double quantidade_subsistema_1;
	double quantidade_subsistema_2;
	double quantidade_subsistema_3;
	double quantidade_subsistema_4;
	double quantidade_subsistema_5;

	Intercambio();
	double totalEnergiaEnviada();
	double totalEnergiaRecebida(int id_subsistema);
};

#endif /* INTERCAMBIO_H_ */

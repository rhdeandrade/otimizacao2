/*
 * UsinaHidreletrica.h
 *
 *  Created on: 10/10/2013
 *      Author: raphael
 */

#ifndef USINAHIDRELETRICA_H_
#define USINAHIDRELETRICA_H_

#include "iostream"
#include "Reservatorio.h"

using namespace std;

class UsinaHidreletrica : public Usina {
public:
	static const char TIPO_MAXIMIZACAO_RESERVATORIO = 'r';
	static const char TIPO_MAXIMIZACAO_AFLUENCIA_NATURAL = 'a';
//	Reservatorio reservatorio;
	int jusante;
	vector<int> montantes; //Classe montante Apenas pra poder fazer atributo de UsinaHidreletrica dentro da class UsinaHidreletrica

	double coeficiente_cota_montante_a0;
	double coeficiente_cota_montante_a1;
	double coeficiente_cota_montante_a2;
	double coeficiente_cota_montante_a3;
	double coeficiente_cota_montante_a4;

	double coeficiente_cota_jusante_a0;
	double coeficiente_cota_jusante_a1;
	double coeficiente_cota_jusante_a2;
	double coeficiente_cota_jusante_a3;
	double coeficiente_cota_jusante_a4;

	double tipo_perda_hidraulica;
	double valor_perda_hidraulica;

	double potencia_efetiva;
	double produtividade_media;
	Reservatorio reservatorio;

	UsinaHidreletrica();

	void atualizarBalancoHidrico(int periodo);
	double carregar_vazao_montante(int periodo);
	double carregar_afluencia_montante(int periodo);
	double calcularGeracaoEnergiaComProdutividadeMedia(int periodo, double volume, double volumeAnterior, double vazaoTurbinada, double vazaoVertida);
	double calcularPolinomioMontante(double vazaoTotal);
	double calcularPolinomioJusante(double vazaoTotal);
};

#endif /* USINAHIDRELETRICA_H_ */

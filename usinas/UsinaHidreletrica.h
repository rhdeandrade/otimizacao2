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

	long double coeficiente_cota_montante_a0;
	long double coeficiente_cota_montante_a1;
	long double coeficiente_cota_montante_a2;
	long double coeficiente_cota_montante_a3;
	long double coeficiente_cota_montante_a4;

	long double coeficiente_cota_jusante_a0;
	long double coeficiente_cota_jusante_a1;
	long double coeficiente_cota_jusante_a2;
	long double coeficiente_cota_jusante_a3;
	long double coeficiente_cota_jusante_a4;

	long double tipo_perda_hidraulica;
	long double valor_perda_hidraulica;

	long double potencia_efetiva;
	long double produtividade_media;
	Reservatorio reservatorio;

	UsinaHidreletrica();

	void atualizarBalancoHidrico(int periodo);
	long double carregar_vazao_montante(int periodo);
	long double carregar_afluencia_montante(int periodo);
	long double calcularGeracaoEnergiaComProdutividadeMedia(int periodo,long double volume, long double volumeAnterior, long double vazaoTurbinada, long double vazaoVertida);
	long double calcularPolinomioMontante(long double vazaoTotal);
	long double calcularPolinomioJusante(long double vazaoTotal);
	long double maximizarProducaoEnergia(int periodo, char tipoMaximizacao, bool previsao);
	HistoricoOperacaoReservatorio maximizarVazaoTurbinadaMinimizarVazaoVertida(HistoricoOperacaoReservatorio historico);
	HistoricoOperacaoReservatorio maximizarProducaoReservatorio(HistoricoOperacaoReservatorio historico);
};

#endif /* USINAHIDRELETRICA_H_ */

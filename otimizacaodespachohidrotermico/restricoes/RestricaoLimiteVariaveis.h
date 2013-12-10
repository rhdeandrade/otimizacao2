/*
 * RestricaoLimiteVariaveis.h
 *
 *  Created on: 04/11/2013
 *      Author: raphael
 */

#ifndef RESTRICAOLIMITEVARIAVEIS_H_
#define RESTRICAOLIMITEVARIAVEIS_H_

using namespace std;

class RestricaoLimiteVariaveis {
public:
	vector<UsinaHidreletrica> hidreletricas;
	vector<UsinaTermica> termicas;
	RestricaoLimiteVariaveis(vector<UsinaHidreletrica> hidreletricas, vector<UsinaTermica> termicas);
	void checkConstraint();

	bool capacidadeArmazenamentoReservatorio(UsinaHidreletrica hidreletrica, int periodo);
	bool capacidadeVazaoTurbinadaReservatorio(UsinaHidreletrica hidreletrica, int periodo);
	bool capacidadeVazaoVertidaReservatorio(UsinaHidreletrica hidreletrica, int periodo);
	bool capacidadeGeracaoEnergiaTermica(UsinaTermica termica, int periodo);
};

#endif /* RESTRICAOLIMITEVARIAVEIS_H_ */

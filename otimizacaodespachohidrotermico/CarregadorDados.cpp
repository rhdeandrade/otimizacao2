/*
 * CarregadorDados.cpp
 *
 *  Created on: 07/10/2013
 *      Author: raphael
 */

#include "CarregadorDados.h"
#include "../util/FileHandler.cpp"

CarregadorDados::CarregadorDados(string arquivoDadosTermicas, string arquivoGeracoesTermicas, string arquivoDadosHidreletricas, string arquivoGeracoesHidreletricas,
		string arquivoDadosSubsistemas, string arquivoDeficitsSubsistemas, string arquivoDemandasSubsistemas, string arquivoIntercambiosSubsistemas) {

	this->arquivoDadosTermicas = arquivoDadosTermicas;
	this->arquivoDadosHidreletricas = arquivoDadosHidreletricas;
	this->arquivoGeracoesTermicas = arquivoDadosTermicas;
	this->arquivoGeracoesHidreletricas = arquivoGeracoesHidreletricas;
	this->arquivoDadosSubsistemas = arquivoDadosSubsistemas;
	this->arquivoDeficitsSubsistemas = arquivoDeficitsSubsistemas;
	this->arquivoDemandasSubsistemas = arquivoDemandasSubsistemas;
	this->arquivoIntercambiosSubsistemas = arquivoIntercambiosSubsistemas;

}

CarregadorDados::CarregadorDados() {

}

vector<UsinaTermica> CarregadorDados::carregar_usinas_termicas() {
	FileHandler file_handler;
	string delimitador(" ");
	vector<UsinaTermica> termicas;

	vector<string> usinas_termicas = file_handler.open_file(this->arquivoDadosTermicas);
	int i;


	for(i = 0; i < usinas_termicas.size(); i++) {
		vector<string> tokens;
		UsinaTermica usina_termica;

		string value(usinas_termicas.at(i).data());

		split(tokens, value, is_any_of(delimitador));

		usina_termica.id_usina = (int) lexical_cast<double>(tokens.at(0).data());

		usina_termica.quantidade_geracao_max = lexical_cast<double>(tokens.at(1).data());

		usina_termica.quantidade_geracao_min = lexical_cast<double>(tokens.at(2).data());

		usina_termica.coeficiente_custo_termica_a0 = lexical_cast<double>(tokens.at(3).data());

		usina_termica.coeficiente_custo_termica_a1 = lexical_cast<double>(tokens.at(4).data());

		usina_termica.coeficiente_custo_termica_a2 = lexical_cast<double>(tokens.at(5).data());

		usina_termica.id_subsistema = (int) lexical_cast<double>(tokens.at(6).data());


		usina_termica.geracoes = this->carregar_geracoes_usinas_termicas(usina_termica.id_usina, this->arquivoGeracoesTermicas);

		termicas.push_back(usina_termica);

	}

	return termicas;
}

vector<GeracaoEnergia> CarregadorDados::carregar_geracoes_usinas_termicas(int id_usina, string arquivo) {
	FileHandler file_handler;
	vector<GeracaoEnergia> geracoes;
	vector<string> dados_arquivo = file_handler.open_file(arquivo);
	string delimitador(" ");

	int i = 0;
	while(i <= dados_arquivo.size()) {
		vector<string> tokens;
		string value(dados_arquivo.at(i).data());
		split(tokens, value, is_any_of(delimitador));

		if(((int) lexical_cast<double>(tokens.at(0).data())) == id_usina) {
			int periodo = 1;
			while (periodo <= 60) { //Esse é o número de períodos definidos na classe OtimizacaoDespachoHidrotermicoGlobals do pj PHP
				i++;
				string value(dados_arquivo.at(i).data());

				split(tokens, value, is_any_of(delimitador));
				GeracaoEnergia geracao;
				geracao.periodo = periodo;
				periodo++;
				geracao.quantidade = lexical_cast<double>(tokens.at(0).data());

				geracoes.push_back(geracao);
			}

			return geracoes;
		}
		else {
			i += 60;
		}

		i++; //Pra mim essa linha não faz sentido, pq não fazer i += 61 na linha de cima então? Apenas copiei do cogido php

	}
	return geracoes;
}


vector<UsinaHidreletrica> CarregadorDados::carregarUsinasHidreletricas() {
	FileHandler file_handler;
	vector<UsinaHidreletrica> usinas;
	vector<string> dados_arquivo = file_handler.open_file(this->arquivoDadosHidreletricas);

	vector<string> tokens;
	string delemitador(" ");

	for (int i = 0; i < dados_arquivo.size(); i++) {
		string linha = dados_arquivo.at(i).data();
		split(tokens, linha, is_any_of(delemitador));

		UsinaHidreletrica usina;
		usina.id_usina = (int) lexical_cast<double>(tokens.at(0).data());
		usina.jusante = (int) lexical_cast<double>(tokens.at(1).data());
		usina.reservatorio.volume_maximo = lexical_cast<double>(tokens.at(2).data());
		usina.reservatorio.volume_minimo = lexical_cast<double>(tokens.at(3).data());

		usina.coeficiente_cota_montante_a0 = lexical_cast<double>(tokens.at(4).data());
		usina.coeficiente_cota_montante_a1 = lexical_cast<double>(tokens.at(5).data());
		usina.coeficiente_cota_montante_a2 = lexical_cast<double>(tokens.at(6).data());
		usina.coeficiente_cota_montante_a3 = lexical_cast<double>(tokens.at(7).data());
		usina.coeficiente_cota_montante_a4 = lexical_cast<double>(tokens.at(8).data());

		usina.coeficiente_cota_jusante_a0 = lexical_cast<double>(tokens.at(9).data());
		usina.coeficiente_cota_jusante_a1 = lexical_cast<double>(tokens.at(10).data());
		usina.coeficiente_cota_jusante_a2 = lexical_cast<double>(tokens.at(11).data());
		usina.coeficiente_cota_jusante_a3 = lexical_cast<double>(tokens.at(12).data());
		usina.coeficiente_cota_jusante_a4 = lexical_cast<double>(tokens.at(13).data());

		usina.tipo_perda_hidraulica = lexical_cast<double>(tokens.at(14).data());
		usina.valor_perda_hidraulica = lexical_cast<double>(tokens.at(15).data());
		usina.potencia_efetiva = lexical_cast<double>(tokens.at(16).data());
		usina.produtividade_media = lexical_cast<double>(tokens.at(17).data());
		usina.id_subsistema = (int) lexical_cast<double>(tokens.at(18).data());

		usina.reservatorio.defluencia_minima = lexical_cast<double>(tokens.at(19).data());
		usina.reservatorio.maximo_vazao_turbinada = lexical_cast<double>(tokens.at(20).data());

		usina = carregar_historico_operacao_reservatorio(usina);

		usinas.push_back(usina);

	}

	carregar_montantes(&usinas);



	return usinas;
}

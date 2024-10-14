/**
 * @file Menu.h
 */

#ifndef MENU_H
#define MENU_H

#include "DataSet.h"

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;


/**
 * @class Menu
 * @brief Representa o menu do programa.
 */
class Menu
{
private:
    /*!<  Instância de um objeto da classe Dataset, o qual contém todas as informações do sistema */
    /// Complexidade O(1)
    DataSet dataset;
    /// @brief Da display do menu inicial, a landing page do programa
    /// Complexidade O(1)
    void menu();
    /// @brief pega o input do usuário, e executa uma das 8 opções disponíveis na landing page do programa
    /// Complexidade O(1)
    void principal();
    /// @brief função que pega no DataSet as informações sobre um país, aeroporto, companhia ou cidade
    /// @param txt string que pode representar um país, aeroporto, companhia aérea ou uma cidade
    /// Complexidade O(1)
    string submenu(string txt);
    /// @brief da o display do submenu relacionado as "estatísticas" do programa
    /// @param opt opção de um input
    /// Complexidade O(1)
    void submenu3_text(int opt);
    /// @brief pega o input do usuário para escolher uma das opções relacionadas as estatísticas do programa
    /// @param (opt, info) opção de input
    /// Complexidade O(1)
    char submenu3(int opt,string* info);
    /// @brief da o display das opções relacionadas aos aeroportos do programa
    /// Complexidade O(1)
    void submenu2_text();
    /// @brief pega o input do usuário para escolher uma das opções sobre os aeroportos
    /// Complexidade O(1)
    void submenu2();
    /// @brief da o display das opções relacionadas ao trajeto entre dois locais
    /// Complexidade O(1)
    void submenu4_text();
    /// @brief pega o input do usuário, e executa uma das duas opções de trajeto entre dois locais(source, tarjet)
    /// Complexidade O(1)
    char submenu4();

public:
    /// @brief contrutor da classe Menu, gera uma instância da classe menu com um objeto Dataset pelo parâmetro
    /// @param dataset Objeto da classe DataSet com os dados do programa
    /// Complexidade O(1)
    Menu(DataSet dataset);
};

#endif


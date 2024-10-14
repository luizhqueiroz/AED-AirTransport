/**
 * @file Airport.h
 */

#ifndef AIRPORT_H
#define AIRPORT_H

#include "City.h"
#include "Country.h"
#include "Airline.h"

#include <string>
#include <list>

using std::string;
using std::list;
using std::stod;

/**
 * @class Airport
 * @brief Representa um aeroporto.
 */
class Airport
{
private:
    string code; /*!< código referente ao aeroporto */
    string name; /*!< nome referente ao aeroporto */
    double latitude; /*!< latitude referente ao aeroporto */
    double longitude; /*!< longitude referente ao aeroporto */
    City* city; /*!<  cidade a qual o aeroporto pertence */
    list <Airline *> airlines; /*!<  lista das campanhias que operam em um determinado aeroporto */
    list <Country *> countries; /*!< lista dos paises conectados a um determinado aeroporto */
    list <Flight *> flights; /*!< lista dos voos de um determinado aeroporto */

public:
    /// @brief Define o código do aeroporto
    /// @param code código do aeroporto
    /// Complexidade O(1)
    void setCode(string code);
    /// @brief Define o nome do aeroporto
    /// @param name nome do aeroporto
    /// Complexidade O(1)
    void setName(string name);
    /// @brief Define a latitude do aeroporto
    /// @param latitude latitude do aeroporto
    /// Complexidade O(1)
    void setLatitude(string latitude);
    /// @brief Define a longitude do aeroporto
    /// @param longitude longitude do aeroporto
    /// Complexidade O(1)
    void setLongitude(string longitude);
    /// @brief Obtém o código do aeroporto
    /// Complexidade O(1)
    string getCode();
    /// @brief Obtém o nome do aeroporto
    /// Complexidade O(1)
    string getName();
    /// @brief Obtém a latitude do aeroporto
    /// Complexidade O(1)
    double getLatitude();
    /// @brief Obtém o longitude do aeroporto
    /// Complexidade O(1)
    double getLongitude();
    /// @brief Define a cidade do aeroporto
    /// Complexidade O(1)
    void setCity(City *city);
    /// @brief Obtém a cidade do aeroporto
    /// Complexidade O(1)
    City* getCity();
    /// @brief Percorre o arquivo de aeroportos até encontrar as companhias que operam em tal
    /// @param airline companhia que pode operar em tal aeroporto
    /// Complexidade O(n)
    void insertAirline(Airline* airline);
    /// @brief Percorre o arquivo de aeroportos até encontrar os país que operam em tal
    /// @param country país que pode conter tal aeroporto
    /// Complexidade O(n)
    void insertCountry(Country* country);
    /// @brief Retorna uma lista de companhias aéreas que operam em determinado aeroporto
    /// Complexidade O(1)
    list <Airline *>& getAirlines();
    /// @brief Retorna uma lista de países para qual determinado aeroporto faz conexão
    /// Complexidade O(1)
    list <Country *>& getCountries();
    /// @brief Retorna uma lista de voos que ocorrem em determinado aeroporto
    /// Complexidade O(1)
    list <Flight *>& getFlights();
};

#endif

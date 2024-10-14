/**
 * @file Country.h
 */

#ifndef COUNTRY_H
#define COUNTRY_H

class Airline;
class Flight;
class City;

#include "City.h"
#include "Airline.h"
#include "Flight.h"

#include <string>
#include <list>
#include <iostream>

using std::string;
using std::list;
using std::cout;
using std::endl;

/**
 * @class Country
 * @brief Representa um país.
 */
class Country
{
private:
    string name; /*!< nome do país */
    list<City *> cities; /*!< lista das cidades do pais */
    list<Airline *> airlines; /*!< lista das companhias aéreas do pais */
    list<Flight *> flights; /*!< lista dos voos do pais */

public:
    /// @brief Define o nome do país
    /// @param name nome do pais
    /// Complexidade O(1)
    void setName(string name);

    /// @brief Obtém o nome do país
    /// Complexidade O(1)
    string getName();

    /// @brief Adiciona a uma lista as cidades do país em questão
    /// @param city cidade presente em tal país
    /// Complexidade O(1)
    void insertCity(City *city);

    /// @brief Obtém as cidades do país em questão
    /// Complexidade O(1)
    list<City *>& getCities();

    /// @brief Adiciona a uma lista as companhias aéreas do país em questão
    /// @param airline companhia aérea presente em tal país
    /// Complexidade O(1)
    void insertAirline(Airline *airline);

    /// @brief Obtém da lista as companhias aéreas do país em questão
    /// Complexidade O(1)
    list<Airline *>& getAirlines();

    /// @brief Obtém da lista dos voos do país em questão
    /// Complexidade O(1)
    list<Flight *>& getFlights();
};
#endif

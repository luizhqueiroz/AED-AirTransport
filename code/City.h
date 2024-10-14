/**
 * @file City.h
 */

#ifndef CITY_H
#define CITY_H

class Airport;
class Country;

#include "Country.h"
#include "Airport.h"

#include <string>
#include <list>

using std::string;
using std::list;

/**
 * @class City
 * @brief Representa uma cidade.
 */
class City
{
private:
    string name; /*!< nome da cidade */
    Country* country; /*!< pais no qual pertence a cidade */
    list<Airport *> airports; /*!< @brief lista dos aeroportos da cidade */

public:
    /// @brief Define o nome da cidade
    /// @param name nome da cidade
    /// Complexidade O(1)
    void setName(string name);
    /// @brief Obtém o nome da cidade
    /// Complexidade O(1)
    string getName();
    /// @brief Define o pais da cidade em questão
    /// @param country país da cidade
    /// Complexidade O(1)
    void setCountry(Country *country);
    /// @brief Obtém o pais da cidade em questão
    /// Complexidade O(1)
    Country* getCountry();
    /// @brief Adiciona a uma lista os aeroportos da cidade em questão
    /// @param airport aeroporto presente em tal cidade
    /// Complexidade O(1)
    void insertAirport(Airport* airport);
    /// @brief Obtém da lista os aeroportos da cidade em questão
    /// Complexidade O(1)
    list<Airport *>& getAirports();
};

#endif

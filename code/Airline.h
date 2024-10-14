/**
 * @file Airline.h
 */

#ifndef AIRLINE_H
#define AIRLINE_H

#include <string>
#include <list>

#include "Country.h"
#include "Airport.h"

using std::string;
using std::list;

/**
 * @class Airline
 * @brief Representa uma companhia aérea.
 */
class Airline
{
private:
    string code; /*!< código referente a companhia aérea */
    string name; /*!< nome referente a companhia aérea */
    string callsign; /*!< alcunha da referida companhia aérea */
    Country* country; /*!< pais ao qual a companhia pertence */
    list <Airport*> airports; /*!< aeroportos deservidos pela companhia */
    list <Flight*> flights; /*!< lista dos voos da companhia */
public:
    /// @brief Define o código da companhia aérea
    /// @param code código da companhia aérea
    /// Complexidade O(1)
    void setCode(string code);
    /// @brief Define o nome da companhia aérea
    /// @param name nome da companhia aérea
    /// Complexidade O(1)
    void setName(string name);
    /// @brief Define a alcunha da companhia aérea
    /// @param callsign alcunha da companhia aérea
    /// Complexidade O(1)
    void setCallsign(string callsign);
    /// @brief Define o país da companhia aérea
    /// @param country país da companhia aérea
    /// Complexidade O(1)
    void setCountry(Country *country);
    /// @brief Obtém o código da companhia aérea
    /// Complexidade O(1)
    string getCode();
    /// @brief Obtém o nome da companhia aérea
    /// Complexidade O(1)
    string getName();
    /// @brief Obtém a alcunha da companhia aérea
    /// Complexidade O(1)
    string getCallsign();
    /// @brief Obtém o país da companhia aérea
    /// Complexidade O(1)
    Country* getCountry();
    /// @brief Obtém a lista de aeroportos
    /// Complexidade O(1)
    list <Airport*>& getAirports();
    /// @brief insere os aeroportos que estão em determinada companhia aérea
    /// @param airport aeroporto de uma companhia aérea
    /// Complexidade O(n)
    void insertAirport(Airport* airport);
    /// @brief Obtém os voos que estão em determinada companhia aérea
    /// Complexidade O(1)
    list <Flight*>& getFlights();
};

#endif

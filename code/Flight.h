/**
 * @file Flight.h
 */

#ifndef FLIGHT_H
#define FLIGHT_H

#include "Airport.h"
#include "Airline.h"

#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

/**
 * @class Flight
 * @brief Representa os voos.
 */
class Flight
{
private:
    Airport* source; /*!<  aeroporto de saída */
    Airport* target; /*!<  aeroporto de destino */
    list<Airline *> airlines; /*!<  lista das companhias aéreas para um certo voo */
    int distance; /*!<  distancia entre os aeroportos */

public:
    /// @brief Define o aeroporto de saída
    /// @param source pointeiro que representa o aeroporto de partida
    /// Complexidade O(1)
    void setSource(Airport* source);
    /// @brief Define o aeroporto de destino
    /// @param source ponteiro que representa o aeroporto de destino
    /// Complexidade O(1)
    void setTarget(Airport* source);
    /// @brief Insere numa lista as companhias aéreas para um determinado voo
    /// @param airline pointeiro para uma companhia aérea
    /// Complexidade O(1)
    void insertAirline(Airline* airline);
    /// @brief Define a longitude e a latitude dos aeroportos selecionados
    /// Complexidade O(1)
    void setDistance();
    /// @brief Define o aeroporto de saído do voo em questão
    /// Complexidade O(1)
    Airport* getSource();
    /// @brief Define o aeroporto de chegada do voo em questão
    /// Complexidade O(1)
    Airport* getTarget();
    /// @brief Obtém da lista as comanhias aéreas que realizam o voo em questão
    /// Complexidade O(1)
    list<Airline *>& getAirlines();
    /// @brief Obtém a longitude e a latitude dos aeroportos selecionados
    /// Complexidade O(1)
    int getDistance();
    /// @brief Calcula a distância entre os aeroportos definidos
    /// @param (lat1,long1,lat2,long2) latitude e longitude da origem e do destino de um trajeto
    /// Complexidade O(1)
    static int haversine(double lat1,double long1,double lat2,double long2);
};

#endif

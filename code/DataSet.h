/**
 * @file Dataset.h
 */

#ifndef DATASET_H
#define DATASET_H

#include "Airport.h"
#include "Country.h"
#include "Airline.h"
#include "Flight.h"
#include "Graph.h"

#include <string>
#include <list>
#include <unordered_map>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include <limits>
#include <queue>
#include <algorithm>
#include <map>

using std::string;
using std::list;
using std::unordered_map;
using std::vector;
using std::multimap;
using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::queue;
using std::reverse;
using std::stringstream;
using std::multimap;
using std::pair;

/**
 * @class DataSet
 * @brief Contém as manipulações dos dados utilizados.
 */
class DataSet
{
private:
/*!< contador de index */
int ind;
/*!< unordered_map < nome do pais, Country > CountriesMap; */
unordered_map < string , Country* > CountriesMap;
/*!< unordered_map < nome da cidade, City > CitiesMap; */
unordered_map < string , City* > CitiesMap;
/*!< unordered_map < codigo do aeroporto, Aeroporto > AirportsMap; */
unordered_map < string , Airport* > AirportsMap;
/*!< unordered_map < codigo da companhia, Airline > AirlinesMap; */
unordered_map < string , Airline* > AirlinesMap;
/*!< unordered_map < codigo do aeroporto, index na Matriz > AirportsIndex; */
unordered_map < string , int > AirportsIndex;
/*!< unordered_map < index na Matriz, codigo do aeroporto > IndexAirports; */
unordered_map < int , string > IndexAirports;
/*!< lista de todos os voos */
list <Flight* > flights;
/*!< grafo dos voos */
Graph* graph;
/*!< map contendo o nome do aeroporto e/ou companhias e o número de voos realizados pelas mesmas */
void printTopK(multimap<int,string> map,int k,string txt);

public:

/// @brief Dataset contendo os aeroportos e companhias que atuam nestes
/// @param (airports,arlines,fligthsFile) arquivos que contém os aeroportos, companhias aéreas e voos
/// Complexidade O(1)
DataSet(string airports, string airlines, string flightsFile);
/// @brief lê dados de aeroportos de um arquivo com o nome dado e armazena-os em um mapa de objetos Airport
/// @param filename nome do arquivo que contém as informações sobre os aeroportos
/// Complexidade O(n)
void readAirports(string filename);
/// @brief imprimem os dados armazenados em seus respectivos mapas
/// Complexidade O(n)
void printAirportsMap();
/// @brief imprimem os dados armazenados em seus respectivos mapas
/// Complexidade O(n*m) onde n é o numero de cidades e m é o número de aeroportos por cidade
void printCitiesMap();
/// @brief lê dados de companhias aéreas de um arquivo com o nome dado e armazena-os em um mapa de objetos companhias aéreas
/// @param filename nome do arquivo que contém as informções sobre as companhias aéreas
/// Complexidade O(n)
void readAirlines(string filename);
/// @brief imprimem os dados armazenados em seus respectivos mapas
/// Complexidade O(n)
void printAirlinesMap();
/// @brief imprimem os dados armazenados em seus respectivos mapas
/// Complexidade O(n*m)
void printCountriesMap();
/// @brief lê dados de voos de um arquivo com o nome dado e armazena-os na matriz de adjacência do objeto Graph
/// @param filename nome do arquivo que contém as informções sobre os voos
/// Complexidade O(n)
void readFlights(string filename);
/// @brief imprime os aeroportos no país especificado
/// @param country string que representa um país
/// Complexidade O(1)
void printAirports(string country);
/// @brief imprime as companhias aéreas no país especificado
/// @param country string que representa um país
/// Complexidade O(1)
void printAirlines(string country);
/// @brief imprime todos os países presentes na lista
/// Complexidade O(1)
void printCountries();
/// @brief retornam um ponteiro para o objeto país
/// @param country string que representa um país
/// Complexidade O(1)
Country *getCountry(string country);
/// @brief retornam um ponteiro para o objeto aeroporto
/// @param airport string que representa um aeroporto
/// Complexidade O(1)
Airport *getAirport(string airport);
/// @brief retornam um ponteiro para o objeto companhia aérea
/// @param airline string que representa uma companhia aérea
/// Complexidade O(1)
Airline *getAirline(string airline);
/// @brief retornam um ponteiro para o objeto cidade
/// @param city string que representa uma cidade
/// Complexidade O(1)
City *getCity(string city);
/// @brief retorna um ponteiro para o objeto Graph
/// Complexidade O(1)
Graph* getGraph();
/// @brief retornam o índice de um aeroporto com o código dado
/// @param airportCode código do aeroporto
/// Complexidade O(1)
int getAirportsIndex(string airportCode);
/// @brief retorna o código de aeroporto de um aeroporto no índice dado
/// @param index índice de um aeroporto na matriz adjacente
/// Complexidade O(1)
string getIndexAirports(int index);
/// @brief imprime a distância entre os aeroportos de origem e destino
/// @param (source, target) string que representa o local de partida e de destino respectivamente
/// Complexidade O(1)
void printDistance(string source,string target);
/// @brief retorna booleano indicando se há um voo direto entre os aeroportos de origem e destino
/// @param (source, target) string que representa o local de partida e de destino respectivamente
/// Complexidade O(1)
bool testAirports(string source,string target);
/// @brief retorna o número de aeroportos da rede global, de um país e os servidos por uma companhia aérea
/// @param (type, info) escolha de input do usuário
/// Complexidade O(1) para o primeiro caso e O(n) para o segundo e terceiro caso.
void numAirports(char type,string info);
/// @brief retorna a quantidade de voos da rede mundial, de um país ou de um companhia aérea
/// @param (type, info) escolha de input do usuário
/// Complexidade O(n) para todos os casos
void numFlights(char type,string info);
/// @brief retorna a quantidade de companhias aéreas de um país ou até mesmo da rede global
/// @param (type, info) escolha de input do usuário
/// Complexidade O(1) para todos os casos
void numAirlines(char type,string info);
/// @brief da o display dos K aeroportos com o maior número de voos
/// @param (type, info) escolha de input do usuário
/// Complexidade O(n * log(n))
void topKvoos(char type,string info);
/// @brief da o display dos K aeroportos com o maior número de companhias aéreas presentes em tais aeroportos
/// @param (type, info) escolha de input do usuário
/// Complexidade O(n * log(n))
void topKairlines(char type,string info);
};

#endif


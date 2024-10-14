/**
 * @file Graph.h
 */

#ifndef GRAPH_H
#define GRAPH_H

class DataSet;

#include "Flight.h"
#include "Graph.h"
#include "DataSet.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <limits>
#include <queue>
#include <algorithm>
#include <map>

using std::string;
using std::vector;
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
 * @class Graph
 * @brief Representa o grafo.
 */
class Graph
{
private:
/*!<  armazeno o número de vertices da matriz */
int numVertices;
/*!<  apontador para dataset */
DataSet* dataset;
/*!<  vetor  de vetores de inteiros */
vector<vector<int>> paths;
/*!<  vetor de inteiros */
vector<int> path;
/*!<  apontador para um vetor de inteiros */
vector<int> *parent;
/*!<  apontador para um array 2D de apontadores */
Flight *** adjMatrix;
/*!<  apontador para um array de vetores de inteiros */
vector<int>* adj;
/*!<  declaração da função bfs */
void bfs(int start);
/*!<  declaração da função find_paths */
void find_paths(int u);

public:
/// @brief uma estrutura de dados de grafo, com uma matriz de adjacência implementada como uma matriz 2D de objetos voos
/// @param (numVertices, dataset) número de vértices da matriz adjacente e uma objeto Dataset com os dados do programa
/// Complexidade O(n^2)
Graph(int numVertices, DataSet* dataset);
/// @brief adiciona uma aresta entre os vértices nas posições de origem e destino dadas
/// @param (source, target) vértice da origem e do destino de um trajeto, em relação à matriz adjacente
/// Complexidade O(1)
void add_edge(int source, int target);
/// @brief obtém o valor da matriz de adjacência em uma determinada posição de origem e destino
/// @param (source, target) vértice da origem e do destino de um trajeto, em relação à matriz adjacente
/// Complexidade O(1)
Flight* getAdjMatrix(int source, int target);
/// @brief define o valor da matriz de adjacência em uma determinada posição de origem e destino
/// @param (source, target, flight) vértices da origem e do destino de um determinado voo, em relação à matriz adjacente
/// Complexidade O(1)
void setAdjMatrix(int source, int target, Flight* flight);
/// @brief imprime a matriz de adjacência
/// Complexidade O(n^2)
void printAdjMatrix();
/// @brief imprime a matriz de adjacência
/// @param (source, target) string que represeta a origem e o destino de um voo, na forma de código do aeroporto
/// Complexidade O(|V|+|E|)
void print_paths_airports(string source,string target);
/// @brief imprimem caminhos entre aeroportos ou cidades, respectivamente, especificados
/// @param (source, target) string que representa a origem e o destino de um voo, na forma do nome da cidade
/// Complexidade O(n^2)
void print_paths_cities(string source,string target);
/// @brief imprime voos a partir de um aeroporto de origem especificado
/// @param source string que representa um aeroporto
/// Complexidade O(n^2)
void printFlights(string source);
};

#endif


#include "DataSet.h"

Graph::Graph(int numVertices, DataSet* dataset)  : numVertices{numVertices}, dataset{dataset}
{
    adjMatrix = new Flight **[numVertices];

    for (int i = 0; i < numVertices; i++)
    {
        adjMatrix[i] = new Flight *[numVertices];

        for (int j = 0; j < numVertices; j++)
            adjMatrix[i][j] = nullptr;
    }

    adj = new vector<int>[numVertices];
    parent = new vector<int>[numVertices];
}

void Graph::add_edge(int source, int target)
{
    adj[source].push_back(target);
}

Flight* Graph::getAdjMatrix(int source, int target)
{
    return adjMatrix[source][target];
}

void Graph::setAdjMatrix(int source, int target, Flight* flight)
{
    adjMatrix[source][target] = flight;
}

void Graph::printAdjMatrix()
{
    int i, j;
    bool first;
    Flight *flight;
    Airport *airport;

    for (i = 0; i < numVertices; i++)
    {
        first = true;

        for (j = 0; j < numVertices; j++)
        {
            flight = adjMatrix[i][j];

            if (flight != nullptr)
            {
                if (first)
                {
                    first = false;
                    airport = flight->getSource();

                    cout << "_____________________________________________________________\n";
                    cout << "| " << airport->getCode() << " " << airport->getCity()->getName() << endl;
                    cout << "|____________________________________________________________\n";
                }

                airport = flight->getTarget();

                cout << "  " << airport->getCode() << " " << airport->getCity()->getName();
                cout << " " << flight->getDistance() << " km" << endl;

                list<Airline *> airlines = flight->getAirlines();
                list<Airline *>::iterator it;

                cout << "    ";
                for (it = airlines.begin(); it != airlines.end(); it++)
                    cout << (*it)->getCode() << "  ";
                cout << endl
                     << endl
                     << std::flush;
            }
        }
    }
}

void Graph::bfs(int start)
{
    bool **visited = new bool *[numVertices];

    for (int i = 0; i < numVertices; i++)
    {
        visited[i] = new bool[numVertices];

        for (int j = 0; j < numVertices; j++)
            visited[i][j] = false;
    }

    vector<int> dist(numVertices, INT_MAX);
    queue<int> q;

    q.push(start);
    parent[start] = {-1};
    dist[start] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : adj[u])
            if (dist[v] > dist[u] + 1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
                parent[v].clear();

                if (!visited[v][u])
                    parent[v].push_back(u);

                visited[v][u] = true;
            }
            else if (dist[v] == dist[u] + 1)
            {

                if (!visited[v][u])
                    parent[v].push_back(u);

                visited[v][u] = true;
            }
    }
}

void Graph::find_paths(int u)
{
    if (u == -1)
    {
        paths.push_back(path);
        return;
    }

    for (int par : parent[u])
    {
        path.push_back(u);

        find_paths(par);
        path.pop_back();
    }
}

void Graph::print_paths_airports(string source, string target)
{
    int start = dataset->getAirportsIndex(source);
    int end = dataset->getAirportsIndex(target);
    int min = 50000;
    int imin = 0;
    int i,j;
    vector<int>::iterator it;

    if ( adj[dataset->getAirportsIndex(source)].size() == 0 )
    {
        cout << "Não há voos saindo de " << source << " ";
        cout << dataset->getAirport(source)->getName() << endl;
        return;
    }

    j = dataset->getAirportsIndex(target);

    for ( i = 0; i < numVertices; i++ )
        if (adjMatrix[i][j] != nullptr)
            break;

    if (i == numVertices)
    {
        cout << "Não há voos chegando em " << target << " ";
        cout << dataset->getAirport(target)->getName() << endl;
        return;
    }

    for (auto i = paths.begin(); i != paths.end(); i++)
        (*i).clear();

    paths.clear();

    for (int i = 0; i < numVertices; i++)
        parent[i].clear();

    path.clear();

    cout << "Percursos com menos conexões de " << source << " para " << target << endl
         << endl;

    Flight *flight;
    Airport *airport;
    list<Airline *> airlines;

    bfs(start);

    find_paths(end);
    int num = 0;

    for (auto v = paths.begin(); v != paths.end(); v++)
    {
        reverse((*v).begin(), (*v).end());

        int dist = 0;

        for (it = (*v).begin(); it < (*v).end() - 1; ++it)
        {
            flight = adjMatrix[*it][*(it + 1)];

            if (flight == nullptr)
            {
                cout << "O Voo " << dataset->getIndexAirports(*it) << " -> ";
                cout << dataset->getIndexAirports(*(it + 1)) << " não existe\n";
                return;
            }

            airport = flight->getSource();
            cout << airport->getCode() << " " << airport->getCity()->getName() << " -> ";

            airport = flight->getTarget();
            cout << airport->getCode() << " " << airport->getCity()->getName() << " ";

            airlines = flight->getAirlines();
            list<Airline *>::iterator it2;
            cout << "( ";
            for (it2 = airlines.begin(); it2 != airlines.end(); it2++)
                cout << (*it2)->getCode() << " ";
            cout << " ) : ";

            cout << flight->getDistance() << " KM\n";
            dist += flight->getDistance();
        }

        cout << "Distância Total: " << dist << " KM\n\n";

        if (dist < min)
        {
            min = dist;
            imin = num;
        }

        num++;
    }

    if ( min == 50000 )
    {
        cout << "Não há conexão possível entre " << source << " e " << target << endl;
        return;
    }

    cout << "Percurso Recomendado com Distância Mínima: " << min << " KM\n";

    path = paths[imin];

    for (it = path.begin(); it < path.end() - 1; it++)
    {
        flight = adjMatrix[*it][*(it + 1)];

        airport = flight->getSource();
        cout << airport->getCode() << " " << airport->getCity()->getName() << " -> ";

        airport = flight->getTarget();
        cout << airport->getCode() << " " << airport->getCity()->getName() << " ";

        airlines = flight->getAirlines();

        list<Airline *>::iterator it2;
        cout << "( ";
        for (it2 = airlines.begin(); it2 != airlines.end(); it2++)
            cout << (*it2)->getCode() << " ";
        cout << " )\n";
    }

    if (path.size() > 2)
    {
        cout << "\nCompanhias Aéreas Recomendadas:\n";

        it = path.begin();
        flight = adjMatrix[*it][*(it + 1)];

        airlines = flight->getAirlines();
        list<Airline *>::iterator it3;

        for (it3 = airlines.begin(); it3 != airlines.end(); it3++)
        {
            unsigned count = 0;
            string code;

            for (it = path.begin() + 1; it < path.end() - 1; it++)
            {
                flight = adjMatrix[*it][*(it + 1)];
                list<Airline *> airlines2 = flight->getAirlines();
                list<Airline *>::iterator it4;

                for (it4 = airlines2.begin(); it4 != airlines2.end(); it4++)
                {
                    if ((*it3)->getCode() == (*it4)->getCode())
                    {
                        code = (*it3)->getCode();
                        count++;
                    }
                }
            }

            if (count == path.size() - 2)
            {
                Airline *airline = dataset->getAirline(code);
                cout << "  " << airline->getCode() << " " << airline->getName() << endl;
            }
        }
    }
}

void Graph::print_paths_cities(string source,string target)
{
    list <Airport*>::iterator it;
    list <Airport*>::iterator it2;
    list <Airport*> airports1;
    list <Airport*> airports2;
    string airportCode1, airportCode2;

    airports1 = dataset->getCity(source)->getAirports();
    airports2 = dataset->getCity(target)->getAirports();

    for ( it = airports1.begin(); it != airports1.end() ; it++ )
    {
        airportCode1 = (*it)->getCode();

        for ( it2 = airports2.begin(); it2 != airports2.end() ; it2++ )
        {
            airportCode2 = (*it2)->getCode();
            print_paths_airports(airportCode1,airportCode2);
            cout << endl;
        }
    }
}

void Graph::printFlights(string source)
{
    Airport *airport;
    string city = dataset->getAirport(source)->getCity()->getName();
    list<Airline *> airlines;
    list<Airline *>::iterator it;
    int voos = 0;
    int i = dataset->getAirportsIndex(source);

    for (int j = 0; j < numVertices; j++)
        if (adjMatrix[i][j] != nullptr)
            voos++;

    cout << voos << " Voos estão saindo do Aeroporto " << source << " " << city << endl;

    for (int j = 0; j < numVertices; j++)
    {
        Flight *flight = adjMatrix[i][j];

        if (flight != nullptr)
        {
            airport = flight->getTarget();
            cout << "  " << airport->getCode() << " " << airport->getCity()->getName();
            cout << " " << flight->getDistance() << " KM : "; // << endl;

            airlines = flight->getAirlines();

            for (it = airlines.begin(); it != airlines.end(); it++)
                cout << (*it)->getCode() << " ";
            cout << endl;
        }
    }

    airport = dataset->getAirport(source);
    cout << endl
         << airport->getAirlines().size() << " Companhias Aéreas estão operando ";
    cout << "no Aeroporto " << source << " " << city << endl;

    airlines = airport->getAirlines();

    for (it = airlines.begin(); it != airlines.end(); it++)
        cout << "  " << (*it)->getCode() << " " << (*it)->getName() << endl;
    cout << endl;

    list<Country *> countries = airport->getCountries();

    cout << countries.size() << " Países estão acessíveis por este Aeroporto\n";

    list<Country *>::iterator it2;

    for (it2 = countries.begin(); it2 != countries.end(); it2++)
        cout << "  " << (*it2)->getName() << endl;
    cout << endl;
}

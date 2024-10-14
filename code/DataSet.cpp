#include "DataSet.h"

DataSet::DataSet(string airportsFile, string airlinesFile, string flightsFile) : ind{0}
{
    int numVertices;
    readAirports(airportsFile);
    readAirlines(airlinesFile);

    numVertices = AirportsMap.size();

    graph = new Graph(numVertices, this);

    readFlights(flightsFile);

}

void DataSet::readAirports(string filename)
{
    string line, code, word, cidade, pais;
    Airport *airport;
    City *city;
    Country *country;
    ifstream ifs{filename};

    if (!ifs.is_open())
    {
        cerr << "File " << filename << " Not Found\n";
        exit(-1);
    }

    getline(ifs, line);

    while (!ifs.eof())
    {
        getline(ifs, line);

        if (line == "")
            break;

        stringstream s(line);
        getline(s, word, ',');

        airport = new Airport();
        airport->setCode(word);

        getline(s, word, ',');
        airport->setName(word);

        getline(s, cidade, ',');
        getline(s, pais, ',');


        if (cidade == "Hamilton")
        {
            if (pais == "Canada")
                cidade = "Hamilton CA";
            else if (pais == "New Zealand")
                cidade = "Hamilton NZ";
        }

        if (cidade == "Sydney")
        {
            if (pais == "Canada")
                cidade = "Sydney CA";
            else if (pais == "Australia")
                cidade = "Sydney AU";
        }

        city = CitiesMap[cidade];

        if (city == nullptr)
        {
            city = new City();
            city->setName(cidade);
            CitiesMap[cidade] = city;

            country = CountriesMap[pais];

            if (country == nullptr)
            {
                country = new Country();
                country->setName(pais);
                CountriesMap[pais] = country;
            }

            city->setCountry(country);
            country->insertCity(city);
        }

        city->insertAirport(airport);
        airport->setCity(city);

        getline(s, word, ',');
        airport->setLatitude(word);

        getline(s, word, ',');
        airport->setLongitude(word);

        AirportsMap[airport->getCode()] = airport;

        AirportsIndex[airport->getCode()] = ind;

        IndexAirports[ind] = airport->getCode();
        ind++;
    }

    ifs.close();
}

void DataSet::printAirportsMap()
{
    Airport* airport;

    cout << "Lista dos Aeroportos:\n\n";

    for (auto const &pair : AirportsMap)
    {
        airport = pair.second;
        cout << airport->getCode() << " ";
        cout << airport->getName() << " ";
        cout << airport->getCity()->getName() << " ";
        cout << airport->getCity()->getCountry()->getName() << " ";
        cout << airport->getLatitude() << " ";
        cout << airport->getLongitude() << endl;
    }

    cout << endl;
}

void DataSet::printCitiesMap()
{
    City* city;

    cout << "Lista das Cidades:\n\n";

    for (auto const &pair : CitiesMap)
    {
        city = pair.second;
        cout << city->getName() << " ";
        cout << city->getCountry()->getName() << endl;

        list<Airport *>::iterator it;
        list<Airport *> airports = city->getAirports();

        for (it = airports.begin(); it != airports.end(); it++)
            cout << "  " << (*it)->getCode() << " " << (*it)->getName() << endl;

        cout << endl;
    }

    cout << endl;
}

void DataSet::readAirlines(string filename)
{
    string line, word, code;
    Airline *airline;
    Country *country;

    ifstream ifs{filename};

    if (!ifs.is_open())
    {
        cerr << "File " << filename << " Not Found\n";
        exit(-1);
    }

    getline(ifs, line);

    while (!ifs.eof())
    {
        getline(ifs, line);

        if (line == "")
            break;

        stringstream s(line);
        getline(s, code, ',');

        airline = new Airline();
        airline->setCode(code);

        getline(s, word, ',');
        airline->setName(word);

        getline(s, word, ',');
        airline->setCallsign(word);

        getline(s, word, ',');

        if (word == "Democratic People's Republic of Korea")
            word = "Korea";
        else if (word == "Republic of Korea")
            word = "South Korea";
        else if (word == "Macao")
            word = "Macau";
        else if (word == "ALASKA")
            word = "United States";
        else if (word == "AVIANCA")
            word = "Colombia";
        else if (word == "Myanmar")
            word = "Burma";
        else if (word == "Republic of the Congo")
            word = "Congo (Brazzaville)";
        else if (word == "Hong Kong SAR of China")
            word = "Hong Kong";
        else if (word == "DRAGON")
            word = "Hong Kong";
        else if (word == "Lao Peoples Democratic Republic")
            word = "Laos";

        if (CountriesMap.find(word) != CountriesMap.end())
        {
            country = CountriesMap[word];
            airline->setCountry(country);

            country->insertAirline(airline);
        }

        AirlinesMap[code] = airline;
    }

    ifs.close();
}

void DataSet::printAirlinesMap()
{
    Airline* airline;

    cout << "Lista das Companhias Aéreas:\n\n";

    for (auto const &pair : AirlinesMap)
    {
        airline = pair.second;

        cout << airline->getCode() << " ";
        cout << airline->getName() << " ";
        cout << airline->getCallsign() << " ";
        cout << airline->getCountry()->getName() << endl;
    }
}

void DataSet::printCountriesMap()
{
    Country* country;

    cout << "Lista dos Países:\n\n";

    for (auto const &pair : CountriesMap)
    {
        country = pair.second;

        cout << country->getName() << endl;

        list<City *>::iterator it2;
        list<City *> cities = country->getCities();

        cout << "  Cidades:\n";

        for (it2 = cities.begin(); it2 != cities.end(); it2++)
            cout << "    " << (*it2)->getName() << endl;

        cout << "  Companhias Aéreas:\n    ";

        list<Airline *>::iterator it3;
        list<Airline *> airlines = country->getAirlines();

        for (it3 = airlines.begin(); it3 != airlines.end(); it3++)
            cout << (*it3)->getCode() << " ";

        cout << endl << endl;
    }
}

void DataSet::readFlights(string filename)
{
    string line, source, target, airline;
    Flight *flight;
    ifstream ifs{filename};

    if (!ifs.is_open())
    {
        cerr << "File " << filename << " Not Found\n";
        exit(-1);
    }

    getline(ifs, line);

    while (!ifs.eof())
    {
        getline(ifs, line);

        if (line == "")
            break;

        stringstream s(line);
        getline(s, source, ',');
        int i = AirportsIndex[source];

        getline(s, target, ',');
        int j = AirportsIndex[target];

        getline(s, airline, ',');

        AirlinesMap[airline]->insertAirport(AirportsMap[source]);
        AirlinesMap[airline]->insertAirport(AirportsMap[target]);


        if ( graph->getAdjMatrix(i,j) == nullptr)
        {
            flight = new Flight();
            flights.push_back(flight);

            flight->setSource(AirportsMap[source]);

            AirportsMap[source]->getCity()->getCountry()->getFlights().push_back(flight);

            AirportsMap[source]->getFlights().push_back(flight);

            flight->setTarget(AirportsMap[target]);

            AirportsMap[target]->getCity()->getCountry()->getFlights().push_back(flight);

            flight->setDistance();

            flight->insertAirline(AirlinesMap[airline]);

            AirlinesMap[airline]->getFlights().push_back(flight);

            graph->setAdjMatrix(i,j,flight);
            graph->add_edge(AirportsIndex[source], AirportsIndex[target]);
        }
        else
        {
            flight = graph->getAdjMatrix(i,j);

            flight->insertAirline(AirlinesMap[airline]);

            AirlinesMap[airline]->getFlights().push_back(flight);
        }

        Airport *airport = AirportsMap[source];
        airport->insertAirline(AirlinesMap[airline]);

        Airport *airport2 = AirportsMap[target];
        airport->insertCountry(airport2->getCity()->getCountry());
    }

    ifs.close();
}

Country *DataSet::getCountry(string country)
{
    auto i = CountriesMap.find(country);

    if ( i == CountriesMap.end() )
        return nullptr;

    return i->second;
}

Airport *DataSet::getAirport(string airport)
{
    auto i = AirportsMap.find(airport);

    if ( i == AirportsMap.end() )
        return nullptr;

    return i->second;
}

Airline *DataSet::getAirline(string airline)
{
    auto i = AirlinesMap.find(airline);

    if ( i == AirlinesMap.end() )
        return nullptr;

    return i->second;
}

City *DataSet::getCity(string city)
{
    auto i = CitiesMap.find(city);

    if ( i == CitiesMap.end() )
        return nullptr;

    return i->second;
}

void DataSet::numAirports(char type,string info)
{
    list <City *> cities;
    list <City *>::iterator it;
    int count = 0;

    switch ( type )
    {
        case '1':
            cout << "\nA Rede Global tem " << AirportsMap.size() << " Aeroportos\n";
            break;

        case '2':
            cities = CountriesMap[info]->getCities();

            for ( it = cities.begin() ; it != cities.end() ; it++ )
                count += (*it)->getAirports().size();

            cout << "O País " << info << " tem " << count << " Aeroportos\n";
            break;

        case '3':
            cout << "A Companhia Aérea " << info << " serve ";
            cout  << AirlinesMap[info]->getAirports().size() << " Aeroportos\n";
            break;
    }
}

void DataSet::numFlights(char type,string info)
{
    list <Flight*> voos;
    list <Flight*>::iterator it;
    int count = 0;

    switch ( type )
    {
        case '1':
            for ( it = flights.begin() ; it != flights.end() ; it++ )
                count += (*it)->getAirlines().size();
            cout << "\n\nA Rede Global tem " << count << " Voos\n";
            break;

        case '2':
            voos = CountriesMap[info]->getFlights();

            for ( it = voos.begin() ; it != voos.end() ; it++ )
                count += (*it)->getAirlines().size();
            cout << "O País " << info << " tem " << count << " Voos\n";;
            break;

        case '3':
            cout << "A Companhia Aérea " << info << " ";
            cout << AirlinesMap[info]->getName() << " tem ";
            cout  << AirlinesMap[info]->getFlights().size() << " Voos\n";
            break;
    }
}

void DataSet::numAirlines(char type,string info)
{
    switch ( type )
    {
        case '1':
            cout << "\nA Rede Global tem " << AirlinesMap.size() << " Companhias Aéreas\n";
            break;

        case '2':
            cout << "\nO País " << info << " tem ";
            cout << CountriesMap[info]->getAirlines().size() << " Companhias Aéreas\n";
            break;
    }
}

void DataSet::topKvoos(char type,string info)
{
    Airport* airport;
    Country* country;
    list<Flight*> flights;
    list<Flight*>::iterator it;
    multimap <int,string> map;
    multimap<int, string>::reverse_iterator it2;
    list<City*> cities;
    list<City*>::iterator it3;
    list<Airport*> airports;
    list<Airport*>::iterator it4;

    int count,k;
    string airportCode,str;

    do
    {
        cout << "Escolher o valor de K (1-10): ";
        getline(cin, str);
        try { k = stoi(str); }
        catch (std::invalid_argument e) { k = 0; }
    }
    while ( k < 1 || k > 10 );

    cout << endl;

    switch ( type )
    {
        case '1':
            for (auto const &par : AirportsMap)
            {
                airport = par.second;
                flights = airport->getFlights();
                count = 0;

                for ( it = flights.begin() ; it != flights.end() ; it++)
                    count += (*it)->getAirlines().size();

                map.insert(pair<int, string>(count,airport->getCode()));
            }

            break;

        case '2':
            country = CountriesMap[info];
            cities = country->getCities();

            for ( it3 = cities.begin() ; it3 != cities.end() ; it3++)
            {
                airports = (*it3)->getAirports();

                for ( it4 = airports.begin() ; it4 != airports.end() ; it4++)
                {
                    airport = (*it4);
                    flights = airport->getFlights();
                    count = 0;

                    for ( it = flights.begin() ; it != flights.end() ; it++)
                        count += (*it)->getAirlines().size();

                    map.insert(pair<int, string>(count,airport->getCode()));
                }
            }

            break;
    }
    printTopK(map,k,"voos");
}

void DataSet::topKairlines(char type,string info)
{
    Airport* airport;
    Country* country;
    multimap <int,string> map;
    multimap<int, string>::reverse_iterator it;
    list<City*> cities;
    list<City*>::iterator it3;
    list<Airport*> airports;
    list<Airport*>::iterator it4;
    string str,airportCode;
    int k;

    do
    {
        cout << "Escolher o valor de K (1-10): ";
        getline(cin, str);
        try { k = stoi(str); }
        catch (std::invalid_argument e) { k = 0; }
    }
    while ( k < 1 || k > 10 );

    cout << endl;

    switch ( type )
    {
        case '1':
            for (auto const &par : AirportsMap)
            {
                airport = par.second;
                map.insert(pair<int, string>(airport->getAirlines().size(),airport->getCode()));
            }

            break;

        case '2':
            country = CountriesMap[info];
            cities = country->getCities();

            for ( it3 = cities.begin() ; it3 != cities.end() ; it3++)
            {
                airports = (*it3)->getAirports();

                for ( it4 = airports.begin() ; it4 != airports.end() ; it4++)
                {
                    airport = (*it4);
                    map.insert(pair<int, string>(airport->getAirlines().size(),airport->getCode()));
                }
            }
            break;
    }

    printTopK(map,k,"airlines");
}

void DataSet::printTopK(multimap<int,string> map,int k,string txt)
{
    multimap<int, string>::reverse_iterator it;
    Airport* airport;
    string airportCode;
    int i = 0;

    for ( it = map.rbegin(); i < k && it != map.rend(); it++)
    {
        airportCode = it->second;
        airport = AirportsMap[airportCode];
        cout << it->first << " " << txt << "  ";
        cout << airportCode << "  " << airport->getName() << "  ";
        cout << airport->getCity()->getName() << "  ";
        cout << airport->getCity()->getCountry()->getName() << endl;
        i++;
    }
}

void DataSet::printCountries()
{
    cout << "\nLista dos Países:\n\n";

    for (auto const &pair : CountriesMap)
        std::cout << "[" << pair.second->getName() << "] ";

    cout << endl;
}

void DataSet::printAirports(string pais)
{
    Country *country = CountriesMap[pais];

    if (country == nullptr)
    {
        cout << "País " << pais << " Inexistente\n\n";
        return;
    }

    list<City *>::iterator it;
    list<City *> cities = country->getCities();

    cout << "\nLista dos Aeroportos de " << pais << " :\n\n";

    for (it = cities.begin(); it != cities.end(); it++)
    {
        cout << "  ";
        list<Airport *>::iterator it2;
        list<Airport *> airports = (*it)->getAirports();

        for (it2 = airports.begin(); it2 != airports.end(); it2++)
            cout << (*it2)->getCode() << " ";

        cout << " " << (*it)->getName() << endl;
    }
}

void DataSet::printAirlines(string pais)
{
    Country *country = CountriesMap[pais];

    if (country == nullptr)
    {
        cout << "País " << pais << " Inexistente\n\n";
        return;
    }

    cout << "\nCompanhias Aéreas de " << pais << "\n";

    list<Airline *>::iterator it;
    list<Airline *> airlines = country->getAirlines();

    for (it = airlines.begin(); it != airlines.end(); it++)
        cout << "  " << (*it)->getCode() << " " << (*it)->getName() << endl;

    cout << endl;
}

bool DataSet::testAirports(string source, string target)
{
    if (source == target)
    {
        cout << "Os Aeroportos devem ser Diferentes\n";
        return false;
    }

    if (AirportsMap[source]->getCity()->getName() == AirportsMap[target]->getCity()->getName())
    {
        cout << "Os Aeroportos devem ser de Cidades Diferentes\n";
        return false;
    }

    return true;
}

Graph* DataSet::getGraph()
{
    return graph;
}

int DataSet::getAirportsIndex(string airportCode)
{
    return AirportsIndex[airportCode];
}

string DataSet::getIndexAirports(int index)
{
    return IndexAirports[index];
}

void DataSet::printDistance(string src, string dest)
{
    Airport *source, *target;
    double lat1, long1, lat2, long2;
    int dist;

    source = AirportsMap[src];

    if (source == nullptr)
    {
        cout << "Aeroporto " << src << " Inexistente\n";
        return;
    }

    target = AirportsMap[dest];

    if (target == nullptr)
    {
        cout << "Aeroporto " << dest << " Inexistente\n";
        return;
    }

    lat1 = source->getLatitude();
    long1 = source->getLongitude();

    lat2 = target->getLatitude();
    long2 = target->getLongitude();
    dist = Flight::haversine(lat1, long1, lat2, long2);
    cout << "Distância entre " << src << " e " << dest << " : " << dist << " KM\n\n";
}
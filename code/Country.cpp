#include "Country.h"

void Country::setName(string name)
{
    this->name = name;
}

string Country::getName()
{
    return name;
}

void Country::insertCity(City *city)
{
    cities.push_back(city);
}

list<City *>& Country::getCities()
{
    return cities;
}

void Country::insertAirline(Airline *airline)
{
    airlines.push_back(airline);
}

list<Airline *>& Country::getAirlines()
{
    return airlines;
}

list<Flight *>& Country::getFlights()
{
    return flights;
}
#include "City.h"

void City::setName(string name)
{
    this->name = name;
}

string City::getName()
{
    return name;
}

void City::setCountry(Country *country)
{
    this->country = country;
}

Country* City::getCountry()
{
    return country;
}

void City::insertAirport(Airport* airport)
{
    airports.push_back(airport);
}

list<Airport *>& City::getAirports()
{
    return airports;
}
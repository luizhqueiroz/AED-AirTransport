#include "Airport.h"

void Airport::setCode(string code)
{
    this->code = code;
}

void Airport::setName(string name)
{
    this->name = name;
}

void Airport::setLatitude(string latitude)
{
    this->latitude = stod(latitude,0);
}

void Airport::setLongitude(string longitude)
{
    this->longitude = stod(longitude,0);
}

string Airport::getCode()
{
    return code;
}

string Airport::getName()
{
    return name;
}

double Airport::getLatitude()
{
    return latitude;
}

double Airport::getLongitude()
{
    return longitude;
}

void Airport::setCity(City *city)
{
    this->city = city;
}

City* Airport::getCity()
{
    return city;
}

void Airport::insertAirline(Airline*  airline)
{
    list <Airline *>::iterator it;

    for ( it = airlines.begin() ; it != airlines.end() ; it++)
        if ( (*it)->getCode() == airline->getCode() )
            break;

    if ( it == airlines.end() )
        airlines.push_back(airline);
}

list <Airline *>& Airport::getAirlines()
{
    return airlines;
}

void Airport::insertCountry(Country* country)
{
    list <Country *>::iterator it;

    for ( it = countries.begin() ; it != countries.end() ; it++)
        if ( (*it)->getName() == country->getName() )
            break;

    if ( it == countries.end() )
        countries.push_back(country);
}

list <Country *>& Airport::getCountries()
{
    return countries;
}
list <Flight *>& Airport::getFlights()
{
    return flights;
}

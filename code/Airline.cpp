#include "Airline.h"

void Airline::setCode(string code)
{
    this->code = code;
}

void Airline::setName(string name)
{
    this->name = name;
}

void Airline::setCallsign(string callsign)
{
    this->callsign = callsign;
}

void Airline::setCountry(Country *country)
{
    this->country = country;
}

string Airline::getCode()
{
    return code;
}

string Airline::getName()
{
    return name;
}

string Airline::getCallsign()
{
    return callsign;
}

Country* Airline::getCountry()
{
    return country;
}

list <Airport*>& Airline::getAirports()
{
    return airports;
}

void Airline::insertAirport(Airport* airport)
{
    list <Airport *>::iterator it;

    for ( it = airports.begin() ; it != airports.end() ; it++)
        if ( (*it)->getCode() == airport->getCode() )
            break;

    if ( it == airports.end() )
        airports.push_back(airport);
}

list <Flight*>& Airline::getFlights()
{
    return flights;
}

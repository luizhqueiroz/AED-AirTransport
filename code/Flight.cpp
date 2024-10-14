#include "Flight.h"

void Flight::setSource(Airport* source)
{
    this->source = source;
}

void Flight::setTarget(Airport* target)
{
    this->target = target;
}

void Flight::insertAirline(Airline* airline)
{
    airlines.push_back(airline);
}

void Flight::setDistance()
{
    double lat1 = source->getLatitude();
    double long1 = source->getLongitude();
    double lat2 = target->getLatitude();
    double long2 = target->getLongitude();
    distance = haversine(lat1,long1,lat2,long2);
}

int Flight::getDistance()
{
    return distance;
}

int Flight::haversine(double lat1, double long1, double lat2, double long2)
{
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLong = (long2 - long1) * M_PI / 180.0;

    lat1 = (lat1)*M_PI / 180.0;
    lat2 = (lat2)*M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLong / 2), 2) * cos(lat1) * cos(lat2);

    double radius = 6371.0;
    double c = 2.0 * asin(sqrt(a));

    return (int) floor(radius * c);
}

Airport* Flight::getSource()
{
    return source;
}

Airport* Flight::getTarget()
{
    return target;
}

list<Airline *>& Flight::getAirlines()
{
    return airlines;
}
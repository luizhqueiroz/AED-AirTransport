#include "code/Menu.h"

int main()
{
    DataSet dataset("../data/airports.csv","../data/airlines.csv","../data/flights.csv");
    Menu menu(dataset);
    return 0;
}
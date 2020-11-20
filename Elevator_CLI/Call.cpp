#include "Call.h"

Call::Call(int floor)
{
    this->floor = floor;
    this->name = "Stefan";
    this->weight = 80;
}

Call::Call(int floor, double weight)
{
    this->floor = floor;
    this->name = "Stefan";
    this->weight = weight;
}

Call::Call(int floor, double weight, string name)
{
    this->floor = floor;
    this->name = name;
    this->weight = weight;
}

double Call::getWeight()
{
    return this->weight;
}

int Call::getFloor()
{
    return this->floor;
}

string Call::getName()
{
    return this->name;
}

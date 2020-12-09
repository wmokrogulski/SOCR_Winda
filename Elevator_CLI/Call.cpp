#include "Call.h"

Call::Call(int floor)
{
    this->callTime = clock();
    this->floor = floor;
    this->name = first_names[rand() % size(first_names)]+" "+last_names[rand()%size(last_names)];
    this->weight = 40+(rand()%100);
}

Call::Call(int floor, double weight)
{
    this->callTime = clock();
    this->floor = floor;
    this->name = first_names[rand() % size(first_names)] + " " + last_names[rand() % size(last_names)];
    this->weight = weight;
}

Call::Call(int floor, double weight, string name)
{
    this->callTime = clock();
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

int Call::getCallTime()
{
    return this->callTime;
}

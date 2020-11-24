#pragma once
#include <string>
#include <ctime>

using namespace std;

class Call
{
private:
	string name;
	double weight;
	int floor;
	int callTime;
public:
	Call(int floor);
	Call(int floor, double weight);
	Call(int floor, double weight, string name);
	double getWeight();
	int getFloor();
	string getName();
	int getCallTime();
};


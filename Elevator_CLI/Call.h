#pragma once
#include <string>

using namespace std;

class Call
{
private:
	string name;
	double weight;
	int floor;
public:
	Call(int floor);
	Call(int floor, double weight);
	Call(int floor, double weight, string name);
};


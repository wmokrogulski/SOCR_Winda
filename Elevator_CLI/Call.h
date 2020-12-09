#pragma once
#include <string>
#include <ctime>
#include <random>
#include<iostream>

using namespace std;

const string first_names[] = { "Adam","Andrew","Steve","Maggy","Elisa","Joe","Anna" };
const string last_names[] = { "Dohn","Thatcher","Pratchet","Smith","Collie" };

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

#pragma once
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

#include "Call.h"

class Elevator
{
private:
	double h, v, a, j;
	double vn, an, jn;
	double cabinWeight, counterWeight;
	double passengerWeight;
	vector<Call> elevatorCalls;
	int floor;
	int setFloor;
public:
	Elevator();
	Elevator(double vn, double an, double jn);
	Elevator(double vn, double an, double jn, double cabinWeight, double counterWeight);
	void moveWithConstJerk(chrono::milliseconds timeStep);
	void moveWithConstAcc(chrono::milliseconds timeStep);
	void moveWithConstVel(chrono::milliseconds timeStep);
	void testMove(int fps);
	double getHeight();
};


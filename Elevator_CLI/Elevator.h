#pragma once
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "Call.h"

const double V_NOM = 1;
const double A_NOM = 1;
const double J_NOM = 1;

const double CABIN_WEIGHT = 800;
const double COUNTERWEIGHT = 1200;

const double FLOOR_HEIGHT = 2.5;
const int NUM_OF_FLOORS = 5;

const int CYCLE_TIME = 10;

class Elevator
{
private:
	bool logEnabled;
	double h, v, a, j;
	double vn, an, jn;
	double cabinWeight, counterWeight;
	double passengerWeight;
	double timePassed;
	vector<Call> elevatorCalls;
	vector<double> floorHeights;
	FILE* logfile;
	chrono::milliseconds cycleTime;
	int floor;
	int setFloor;
public:
	Elevator();
	Elevator(int numFloors);
	Elevator(int numFloors, double floorHeight);
	Elevator(int numFloors, double floorHeight, double vn, double an, double jn);
	Elevator(int numFloors, double floorHeight, double vn, double an, double jn, double cabinWeight, double counterWeight);
	void moveWithConstJerk(chrono::milliseconds timeStep);
	void moveWithConstAcc(chrono::milliseconds timeStep);
	void moveWithConstVel(chrono::milliseconds timeStep);
	void moveUpA(double d);
	void moveDownA(double d);
	void moveUpB(double d);
	void moveDownB(double d);
	void moveUpC(double d);
	void moveDownC(double d);
	void testMove(double d);
	void moveToFloor(int floor);
	void openDoors();
	void log();
	void openLog();
	void closeLog();
	void enableLog();
	void disableLog();
	int checkFloor();
};


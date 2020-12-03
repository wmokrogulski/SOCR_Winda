#pragma once
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <algorithm>

#include "Call.h"

const double GRAVITY = 9.81; // m/s^2

const double INERTIA_NOM = 0.5; // kg*m^2

const double V_NOM = 1; // m/s
const double A_NOM = 1; // m/s^2
const double J_NOM = 1; // m/s^3

const double R_NOM = 1; // m

const double CABIN_WEIGHT = 800; // kg
const double COUNTERWEIGHT = 1200; // kg

const double FLOOR_HEIGHT = 2.5; // m
const int NUM_OF_FLOORS = 5;

const int CYCLE_TIME = 10; // ms

class Elevator
{
private:
	bool logEnabled;
	double inertia;
	double h, v, a, j;
	double vn, an, jn;
	double r;
	double totalEnergy;
	double cabinWeight, counterWeight;
	double passengerWeight;
	double timePassed;
	vector<Call> elevatorCalls;
	vector<double> floorHeights;
	FILE* logfile;
	chrono::milliseconds cycleTime;
	int floor;
	int setFloor;
	int startTime;
	double avgServiceTime;
	double maxServiceTime;
	double totalServiceTime;
	double sumOfServiceTime;
	int servedCalls;
public:
	Elevator();
	Elevator(int numFloors);
	Elevator(int numFloors, double floorHeight);
	Elevator(int numFloors, double floorHeight, double vn, double an, double jn);
	Elevator(int numFloors, double floorHeight, double vn, double an, double jn, double cabinWeight, double counterWeight);
	double calculateEnergy();
	double calculatePower();
	void moveWithConstJerk(chrono::milliseconds timeStep);
	void moveWithConstAcc(chrono::milliseconds timeStep);
	void moveWithConstVel(chrono::milliseconds timeStep);
	void addCall(Call call);
	void moveUpA(double d);
	void moveDownA(double d);
	void moveUpB(double d);
	void moveDownB(double d);
	void moveUpC(double d);
	void moveDownC(double d);
	void testMove(double d);
	void moveToFloor(int floor);
	void simpleMoveToFloor(int floor);
	void advMoveToFloor(int floor);
	void openDoors();
	void closeDoors();
	void log();
	void openLog();
	void closeLog();
	void enableLog();
	void disableLog();
	int checkFloor();
	double checkPrecision();
	vector<Call> getCalls();
	int getMaxFloor();
	void setRadius(double r);
	double getRadius();
	int getFloor();
	double getEnergy();
	double getAvgServiceTime();
	double getMaxServiceTime();
	double getTotalTime();
};


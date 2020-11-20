#pragma once
#include "Elevator.h"
#include <thread>
enum mode{closestCall, earliestCall, upDown};
class ElevatorController
{
private:
	Elevator elevator;
	mode selectedAlgorithm;
	bool active;
	thread operation;
public:
	ElevatorController(Elevator elevator);
	void addCall(Call call);
	void closestCallAlgorithm(vector<Call> calls);
	void earliestCallAlgorithm(vector<Call> calls);
	void upDownAlgorithm(vector<Call> calls);
	void operate();
	void setMode(mode algorithm);
	void enableLog();
	void activate();
	void deactivate();
};


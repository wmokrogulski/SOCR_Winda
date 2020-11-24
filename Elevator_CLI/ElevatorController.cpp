#include "ElevatorController.h"

ElevatorController::ElevatorController(Elevator elevator)
{
	this->elevator = elevator;
	this->selectedAlgorithm = earliestCall;
	this->active = false;
}

void ElevatorController::addCall(Call call)
{
	this->elevator.addCall(call);
}

void ElevatorController::closestCallAlgorithm(vector<Call> calls)
{
	// HERE GOES THE CLOSEST CALL ALGORITHM
	for (int i = 0; i <= this->elevator.getMaxFloor(); i++) {
	}
}

void ElevatorController::earliestCallAlgorithm(vector<Call> calls)
{
	// HERE GOES THE EARLIEST CALL ALGORITHM
	this->elevator.moveToFloor(calls.at(0).getFloor());
}

void ElevatorController::upDownAlgorithm(vector<Call> calls)
{
	// HERE GOES THE UP DOWN ALGORITHM
}

void ElevatorController::operate()
{
	vector<Call> calls;
	while (this->active) {
		calls = this->elevator.getCalls();
		if (!calls.empty()) {
			switch (this->selectedAlgorithm)
			{
			case closestCall:
				this->closestCallAlgorithm(calls);
				break;
			case earliestCall:
				this->earliestCallAlgorithm(calls);
				break;
			case upDown:
				this->upDownAlgorithm(calls);
				break;
			default:
				break;
			}
		}
	}
}

void ElevatorController::setMode(mode algorithm)
{
	this->selectedAlgorithm = algorithm;
}

void ElevatorController::enableLog()
{
	this->elevator.enableLog();
}

void ElevatorController::activate()
{
	this->active = true;
	this->operation = thread(&ElevatorController::operate, this);
}

void ElevatorController::deactivate()
{
	vector<Call> calls;
	do {
		calls = this->elevator.getCalls();
		this_thread::sleep_for(chrono::milliseconds(200));
	} while (!calls.empty());
	this->active = false;
	this->operation.join();
}

void ElevatorController::testCalls()
{
	this->activate();
	this->addCall(Call(4));
	this->addCall(Call(3));
	this_thread::sleep_for(chrono::seconds(1));
	this->addCall(Call(2));
	this->addCall(Call(3));
	this_thread::sleep_for(chrono::seconds(2));
	this->addCall(Call(1));
	this->addCall(Call(0));
	this->deactivate();
}

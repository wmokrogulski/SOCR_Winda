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
	cout << "Added call to " << call.getFloor() << " floor" << endl;
}

void ElevatorController::closestCallAlgorithm(vector<Call> calls)
{
	// HERE GOES THE CLOSEST CALL ALGORITHM
	int floor = this->elevator.getFloor();
	bool found=false;
	for (int i = 0; i <= this->elevator.getMaxFloor(); i++) {
		if (floor == 0) {
			for (Call call : calls) {
				if (call.getFloor() == floor + i) {
					this->elevator.moveToFloor(floor + i);
					found = true;
					break;
				}
			}
			if (found) {
				break;
			}
		}
		if (floor > 0 || floor < this->elevator.getMaxFloor()) {
			for (Call call : calls) {
				if (call.getFloor() == floor + i) {
					this->elevator.moveToFloor(floor + i);
					found = true;
					break;
				}
			}
			if (found) {
				break;
			}
			for (Call call : calls) {
				if (call.getFloor() == floor - i) {
					this->elevator.moveToFloor(floor - i);
					found = true;
					break;
				}
			}
			if (found) {
				break;
			}
		}
		if (floor == this->elevator.getMaxFloor()) {
			for (Call call : calls) {
				if (call.getFloor() == floor - i) {
					this->elevator.moveToFloor(floor - i);
					found = true;
					break;
				}
			}
			if (found) {
				break;
			}
		}
	}
}

void ElevatorController::earliestCallAlgorithm(vector<Call> calls)
{
	// HERE GOES THE EARLIEST CALL ALGORITHM
	this->elevator.moveToFloor(calls.at(0).getFloor());
}

void ElevatorController::upDownAlgorithm(vector<Call> calls)
{
	// HERE GOES THE UP DOWN 
	int floor = this->elevator.getFloor();
	bool found = false;
	if (this->dir == up) {
		for (int i = 0; i <= this->elevator.getMaxFloor() - floor; i++) {
			for (Call call : calls) {
				if (call.getFloor() == floor + i) {
					cout << "Going to floor " << floor + i << endl;
					this->elevator.moveToFloor(floor + i);
					found = true;
					return;
				}
			}
			if (found) {
				break;
			}
		}
		if (!found) {
			this->dir = down;
		}
	}
	if (this->dir == down) {
		for (int i = 0; i <= floor; i++) {
			for (Call call : calls) {
				if (call.getFloor() == floor - i) {
					cout << "Going to floor " << floor - i << endl;
					this->elevator.moveToFloor(floor - i);
					found = true;
					return;
				}
			}
		}
		if (!found) {
			this->dir = up;
		}
	}
	if (this->dir == up) {
		for (int i = 0; i <= this->elevator.getMaxFloor() - floor; i++) {
			for (Call call : calls) {
				if (call.getFloor() == floor + i) {
					cout << "Going to floor " << floor + i << endl;
					this->elevator.moveToFloor(floor + i);
					found = true;
					return;
				}
			}
			if (found) {
				break;
			}
		}
	}
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

double ElevatorController::getEnergy()
{
	return this->elevator.getEnergy();
}

double ElevatorController::getAvgServiceTime()
{
	return this->elevator.getAvgServiceTime();
}

double ElevatorController::getMaxServiceTime()
{
	return this->elevator.getMaxServiceTime();
}

double ElevatorController::getTotalTime()
{
	return this->elevator.getTotalTime();
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
	this->addCall(Call(2));
	this->addCall(Call(4));
	this->addCall(Call(3));
	this_thread::sleep_for(chrono::seconds(1));
	this->addCall(Call(1));
	this->addCall(Call(0));
	this->addCall(Call(2));
	this_thread::sleep_for(chrono::seconds(2));
	this->addCall(Call(3));
	this->deactivate();
}
void ElevatorController::testCalls2()
{
	this->activate();
	this->addCall(Call(1));
	this->addCall(Call(2));
	this_thread::sleep_for(chrono::seconds(5));
	this->addCall(Call(5));
	this_thread::sleep_for(chrono::seconds(5));
	this->addCall(Call(3));
	this_thread::sleep_for(chrono::seconds(5));
	this->addCall(Call(0));
	this_thread::sleep_for(chrono::seconds(5));
	this->addCall(Call(3));
	this_thread::sleep_for(chrono::seconds(5));
	this->addCall(Call(2));
	this->addCall(Call(1));
	this_thread::sleep_for(chrono::seconds(5));
	this->addCall(Call(4));
	this->deactivate();
}

void ElevatorController::testCalls3()
{
	this->activate();
	this->addCall(Call(3));
	this->addCall(Call(4));
	this->addCall(Call(2));
	this->deactivate();
}

void ElevatorController::printQualityIndexes()
{
	cout << "Total energy: " << this->getEnergy()/1000 << " kWh" << endl;
	cout << "Total service time: " << this->getTotalTime() << " s" << endl;
	cout << "Average service time: " << this->getAvgServiceTime() << " s" << endl;
	cout << "Max service time: " << this->getMaxServiceTime() << " s" << endl;
}

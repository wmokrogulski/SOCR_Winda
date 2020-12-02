#define _CRT_SECURE_NO_WARNINGS
#include "Elevator.h"

Elevator::Elevator()
{
	this->logEnabled = false;
	this->timePassed = 0;
	this->logfile = NULL;
	this->cycleTime = chrono::milliseconds(CYCLE_TIME);
	this->vn = V_NOM;
	this->an = A_NOM;
	this->jn = J_NOM;
	this->r = R_NOM;
	this->v = 0;
	this->a = 0;
	this->j = 0;
	this->h = 0;
	this->totalEnergy = 0;
	this->floor = 0;
	this->setFloor = NULL;
	this->startTime=clock();
	this->avgServiceTime=0;
	this->maxServiceTime = NULL;
	this->totalServiceTime=0;
	this->sumOfServiceTime=0;
	this->servedCalls=0;
	this->cabinWeight = CABIN_WEIGHT;
	this->counterWeight = COUNTERWEIGHT;
	this->passengerWeight = 0;
	for (int i = 0; i <= NUM_OF_FLOORS; i++) {
		this->floorHeights.push_back(FLOOR_HEIGHT * i);
	}
}

Elevator::Elevator(int numFloors)
{
	this->logEnabled = false;
	this->logfile = NULL;
	this->cycleTime = chrono::milliseconds(CYCLE_TIME);
	this->timePassed = 0;
	this->vn = V_NOM;
	this->an = A_NOM;
	this->jn = J_NOM;
	this->r = R_NOM;
	this->totalEnergy = 0;
	this->v = 0;
	this->a = 0;
	this->j = 0;
	this->h = 0;
	this->floor = 0;
	this->setFloor = NULL;
	this->startTime = clock();
	this->avgServiceTime = 0;
	this->maxServiceTime = NULL;
	this->totalServiceTime = 0;
	this->sumOfServiceTime = 0;
	this->servedCalls = 0;
	this->cabinWeight = CABIN_WEIGHT;
	this->counterWeight = COUNTERWEIGHT;
	this->passengerWeight = 0;
	for (int i = 0; i <= numFloors; i++) {
		this->floorHeights.push_back(FLOOR_HEIGHT * i);
	}
}

Elevator::Elevator(int numFloors, double floorHeight)
{
	this->logEnabled = false;
	this->logfile = NULL;
	this->cycleTime = chrono::milliseconds(CYCLE_TIME);
	this->timePassed = 0;
	this->vn = V_NOM;
	this->an = A_NOM;
	this->jn = J_NOM;
	this->r = R_NOM;
	this->totalEnergy = 0;
	this->v = 0;
	this->a = 0;
	this->j = 0;
	this->h = 0;
	this->floor = 0;
	this->setFloor = NULL;
	this->startTime = clock();
	this->avgServiceTime = 0;
	this->maxServiceTime = NULL;
	this->totalServiceTime = 0;
	this->sumOfServiceTime = 0;
	this->servedCalls = 0;
	this->cabinWeight = CABIN_WEIGHT;
	this->counterWeight = COUNTERWEIGHT;
	this->passengerWeight = 0;
	for (int i = 0; i <= numFloors; i++) {
		this->floorHeights.push_back(floorHeight * i);
	}
}

Elevator::Elevator(int numFloors, double floorHeight, double vn, double an, double jn)
{
	this->logEnabled = false;
	this->logfile = NULL;
	this->cycleTime = chrono::milliseconds(CYCLE_TIME);
	this->timePassed = 0;
	this->vn = vn;
	this->an = an;
	this->jn = jn;
	this->r = R_NOM;
	this->totalEnergy = 0;
	this->v = 0;
	this->a = 0;
	this->j = 0;
	this->h = 0;
	this->floor = 0;
	this->setFloor = NULL;
	this->startTime = clock();
	this->avgServiceTime = 0;
	this->maxServiceTime = NULL;
	this->totalServiceTime = 0;
	this->sumOfServiceTime = 0;
	this->servedCalls = 0;
	this->cabinWeight = CABIN_WEIGHT;
	this->counterWeight = COUNTERWEIGHT;
	this->passengerWeight = 0;
	for (int i = 0; i <= numFloors; i++) {
		this->floorHeights.push_back(floorHeight * i);
	}
}

Elevator::Elevator(int numFloors, double floorHeight, double vn, double an, double jn, double cabinWeight, double counterWeight)
{
	this->logEnabled = false;
	this->logfile = NULL;
	this->cycleTime = chrono::milliseconds(CYCLE_TIME);
	this->timePassed = 0;
	this->vn = vn;
	this->an = an;
	this->jn = jn;
	this->r = R_NOM;
	this->totalEnergy = 0;
	this->v = 0;
	this->a = 0;
	this->j = 0;
	this->h = 0;
	this->floor = 0;
	this->setFloor = NULL;
	this->startTime = clock();
	this->avgServiceTime = 0;
	this->maxServiceTime = NULL;
	this->totalServiceTime = 0;
	this->sumOfServiceTime = 0;
	this->servedCalls = 0;
	this->cabinWeight = cabinWeight;
	this->counterWeight = counterWeight;
	this->passengerWeight = 0;
	for (int i = 0; i <= numFloors; i++) {
		this->floorHeights.push_back(floorHeight * i);
	}
}

double Elevator::calculateEnergy()
{
	double energy = this->calculatePower() * this->cycleTime.count();
	this->totalEnergy += energy;
	return this->totalEnergy;
}

double Elevator::calculatePower()
{
	double power=0;
	// TODO: Power calculation
	return power;
}

void Elevator::moveWithConstJerk(chrono::milliseconds timeStep)
{
	double tS = timeStep.count() / 1000.;
	this->a += tS * this->j;
	this->v += tS * this->a;
	this->h += tS * this->v;
}

void Elevator::moveWithConstAcc(chrono::milliseconds timeStep)
{
	double tS = timeStep.count() / 1000.;
	this->v += tS * this->a;
	this->h += tS * this->v;
}

void Elevator::moveWithConstVel(chrono::milliseconds timeStep)
{
	double tS = timeStep.count() / 1000.;
	this->h += tS * this->v;
}

void Elevator::addCall(Call call)
{
	this->passengerWeight += call.getWeight();
	this->elevatorCalls.push_back(call);
}

void Elevator::moveUpA(double d)
{
	this->openLog();
	this->log();
	double t1 = this->timePassed + (this->an / this->jn);
	double t2 = this->timePassed + (this->vn / this->an);
	double t3 = this->timePassed + (this->an / this->jn) + (this->vn / this->an);
	double t4 = this->timePassed + (d / this->vn);
	double t5 = this->timePassed + (d / this->vn) + (this->an / this->jn);
	double t6 = this->timePassed + (d / this->vn) + (this->vn / this->an);
	double t7 = this->timePassed + (d / this->vn) + (this->vn / this->an) + (this->an / this->jn);
	this->j = this->jn;
	while (this->timePassed <= t1)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed <= t2)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed <= t3)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed <= t4)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstVel(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed <= t5)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed <= t6)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed <= t7)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	this->closeLog();
}

void Elevator::moveDownA(double d)
{
	this->openLog();
	this->log();
	double t1 = this->timePassed + (this->an / this->jn);
	double t2 = this->timePassed + (this->vn / this->an);
	double t3 = this->timePassed + (this->an / this->jn) + (this->vn / this->an);
	double t4 = this->timePassed + (d / this->vn);
	double t5 = this->timePassed + (d / this->vn) + (this->an / this->jn);
	double t6 = this->timePassed + (d / this->vn) + (this->vn / this->an);
	double t7 = this->timePassed + (d / this->vn) + (this->vn / this->an) + (this->an / this->jn);
	this->j = -this->jn;
	while (this->timePassed <= t1)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed <= t2)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed <= t3)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed <= t4)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstVel(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed <= t5)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed <= t6)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed <= t7)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	this->log();
	this->closeLog();
}

void Elevator::moveUpB(double d)
{
	this->openLog();

	double t1 = this->timePassed + (this->an / this->jn);
	double t2 = this->timePassed + ((-this->an) / (2 * this->jn)) + ((sqrt(pow((this->an), 3) + 4 * d * pow(this->jn, 2))) / (2 * this->jn * sqrt(this->an)));
	double t3 = this->timePassed + ((3 * this->an) / (2 * this->jn)) + ((sqrt(pow((this->an), 3) + 4 * d * pow(this->jn, 2))) / (2 * this->jn * sqrt(this->an)));
	double t4 = this->timePassed + ((sqrt(pow((this->an), 3) + 4 * d * pow(this->jn, 2))) / (sqrt(this->an * this->jn)));
	double t5 = this->timePassed + (this->an / this->jn) + ((sqrt(pow((this->an), 3) + 4 * d * pow(this->jn, 2))) / (sqrt(this->an * this->jn)));

	this->log();
	this->j = this->jn;
	while (this->timePassed <= t1)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed <= t2)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed <= t3)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed <= t4)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed <= t5)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	this->log();
	this->closeLog();
}

void Elevator::moveDownB(double d)
{
	this->openLog();

	double t1 = this->timePassed + (this->an / this->jn);
	double t2 = this->timePassed + ((-this->an) / (2 * this->jn)) + ((sqrt(pow((this->an), 3) + 4 * d * pow(this->jn, 2))) / (2 * this->jn * sqrt(this->an)));
	double t3 = this->timePassed + ((3 * this->an) / (2 * this->jn)) + ((sqrt(pow((this->an), 3) + 4 * d * pow(this->jn, 2))) / (2 * this->jn * sqrt(this->an)));
	double t4 = this->timePassed + ((sqrt(pow((this->an), 3) + 4 * d * pow(this->jn, 2))) / (sqrt(this->an * this->jn)));
	double t5 = this->timePassed + (this->an / this->jn) + ((sqrt(pow((this->an), 3) + 4 * d * pow(this->jn, 2))) / (sqrt(this->an * this->jn)));

	this->log();
	this->j = -this->jn;
	while (this->timePassed <= t1)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed <= t2)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed <= t3)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed <= t4)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed <= t5)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	this->log();
	this->closeLog();
}

void Elevator::moveUpC(double d)
{
	this->openLog();

	double t1 = this->timePassed + pow((d / (2 * this->jn)), (1 / 3.0));
	double t2 = this->timePassed + pow(((27 * d) / (2 * this->jn)), 1 / 3.0);
	double t3 = this->timePassed + pow(((32 * d) / (this->jn)), 1 / 3.0);

	this->log();
	this->j = this->jn;
	while (this->timePassed <= t1)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed <= t2)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed <= t3)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	this->log();
	this->closeLog();
}

void Elevator::moveDownC(double d)
{
	this->openLog();

	double t1 = this->timePassed + pow((d / (2 * this->jn)), (1 / 3.0));
	double t2 = this->timePassed + pow(((27 * d) / (2 * this->jn)), 1 / 3.0);
	double t3 = this->timePassed + pow(((32 * d) / (this->jn)), 1 / 3.0);

	this->log();
	this->j = -this->jn;
	while (this->timePassed <= t1)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed <= t2)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed <= t3)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	this->log();
	this->closeLog();
}

void Elevator::testMove(double d)
{
	this->openLog();

	double t1 = pow((d / (2 * this->jn)), (1 / 3.0));
	double t2 = pow(((27 * d) / (2 * this->jn)), 1 / 3.0);
	double t3 = pow(((32 * d) / (this->jn)), 1 / 3.0);
	cout << "Pietro: " << this->floor << endl;

	printf("j = %f\na = %f\nv = %f\nh = %f\n\n", this->j, this->a, this->v, this->h);
	this->log();
	this->j = this->jn;
	while (this->timePassed <= t1)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		printf("j = %f\na = %f\nv = %f\nh = %f\n\n", this->j, this->a, this->v, this->h);
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed <= t2)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		printf("j = %f\na = %f\nv = %f\nh = %f\n\n", this->j, this->a, this->v, this->h);
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed <= t3)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		printf("j = %f\na = %f\nv = %f\nh = %f\n\n", this->j, this->a, this->v, this->h);
		this->log();
	}
	this->j = 0;
	printf("j = %f\na = %f\nv = %f\nh = %f\n\n", this->j, this->a, this->v, this->h);
	this->log();
	this->closeLog();
	cout << "Time passed: " << this->timePassed << "s" << endl;
}

void Elevator::moveToFloor(int floor)
{
	this->simpleMoveToFloor(floor);
	this->openDoors();
	Call call(0);
	vector<int> indices;
	for (int i = 0; i < this->elevatorCalls.size(); i++) {
		call = elevatorCalls.at(i);
		if (call.getFloor() == floor) {
			cout << call.getName() << " leaves the elevator." << endl;
			this->passengerWeight -= call.getWeight();
			indices.push_back(i);
			this_thread::sleep_for(chrono::milliseconds(50));
		}
	}
	for (int i : indices) {
		this->elevatorCalls.erase(elevatorCalls.begin() + i);
	}
	cout << this->elevatorCalls.size() << " passengers in the elevator." << endl;
	this->closeDoors();
}

void Elevator::simpleMoveToFloor(int floor)
{
	double tS = this->cycleTime.count() / 1000.;
	if (this->floor < floor) {
		// move Up
		this->v = this->vn;
		while (this->h < (this->floorHeights.at(floor))) {
			this_thread::sleep_for(this->cycleTime);
			this->moveWithConstVel(this->cycleTime);
			this->checkFloor();
			this->timePassed += this->cycleTime.count() / 1000.;
			this->log();
		}
		this->v = 0;
	}
	else if (this->floor > floor) {
		//move Down
		this->v = -this->vn;
		while (this->h > (this->floorHeights.at(floor))) {
			this_thread::sleep_for(this->cycleTime);
			this->moveWithConstVel(this->cycleTime);
			this->checkFloor();
			this->timePassed += this->cycleTime.count() / 1000.;
			this->log();
		}
		this->v = 0;
	}
}

void Elevator::advMoveToFloor(int floor)
{
	double d = this->floorHeights.at(floor) - this->floorHeights.at(this->floor);
	if (d > 0) {
		d = abs(d);
		if (d >= (pow(this->an, 2) * this->vn + pow(this->vn, 2) * this->jn) / (this->jn * this->an)) {
			cout << "Up A" << endl;
			this->moveUpA(d);
		}
		else if (d >= 2 * pow(this->an, 3) / pow(this->jn, 2)) {
			cout << "Up B" << endl;
			this->moveUpB(d);
		}
		else {
			cout << "Up C" << endl;
			this->moveUpC(d);
		}
	}
	else if (d < 0) {
		d = abs(d);
		if (d >= (pow(this->an, 2) * this->vn + pow(this->vn, 2) * this->jn) / (this->jn * this->an)) {
			this->moveDownA(d);
		}
		else if (d >= 2 * pow(this->an, 3) / pow(this->jn, 2)) {
			this->moveDownB(d);
		}
		else {
			this->moveDownC(d);
		}
	}
}

void Elevator::openDoors()
{
	cout << "Opening doors" << endl;
	this_thread::sleep_for(chrono::seconds(2));
}
void Elevator::closeDoors() 
{
	cout << "Closing doors" << endl;
	this_thread::sleep_for(chrono::seconds(2));
}

void Elevator::log()
{
	if (this->logEnabled) {
		fprintf(this->logfile, "%f %f %f %f %f\n", this->timePassed, this->j, this->a, this->v, this->h);
	}
}

void Elevator::openLog()
{
	if (this->logEnabled) {
		this->logfile = fopen("movement.txt", "a");
	}
}

void Elevator::closeLog()
{
	if (this->logEnabled) {
		fclose(this->logfile);
	}
}

void Elevator::enableLog()
{
	this->logEnabled = true;
	this->logfile = fopen("movement.txt", "w");
	fclose(this->logfile);
}

void Elevator::disableLog()
{
	this->logEnabled = false;
}

int Elevator::checkFloor()
{
	if (this->h > floorHeights.at(this->floor) + (this->floorHeights.at(1) / 2)) {
		this->floor++;
		cout << "Floor: " << this->floor << endl;
	}
	else if (this->h < floorHeights.at(this->floor) - (this->floorHeights.at(1) / 2)) {
		this->floor--;
		cout << "Floor: " << this->floor << endl;
	}
	return this->floor;
}

double Elevator::checkPrecision()
{
	return this->h-this->floorHeights.at(this->floor);
}

vector<Call> Elevator::getCalls()
{
	return this->elevatorCalls;
}

int Elevator::getMaxFloor()
{
	return (this->floorHeights.size())-1;
}

double Elevator::getEnergy()
{
	return this->totalEnergy;
}

double Elevator::getAvgServiceTime()
{
	return this->avgServiceTime;
}

double Elevator::getMaxServiceTime()
{
	return this->maxServiceTime;
}

void Elevator::setRadius(double r)
{
	this->r = r;
}

double Elevator::getRadius()
{
	return this->r;
}

int Elevator::getFloor()
{
	return this->floor;
}

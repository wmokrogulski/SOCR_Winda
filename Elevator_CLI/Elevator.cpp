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
	this->v = 0;
	this->a = 0;
	this->j = 0;
	this->h = 0;
	this->floor = 0;
	this->setFloor = NULL;
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
	this->v = 0;
	this->a = 0;
	this->j = 0;
	this->h = 0;
	this->floor = 0;
	this->setFloor = NULL;
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
	this->v = 0;
	this->a = 0;
	this->j = 0;
	this->h = 0;
	this->floor = 0;
	this->setFloor = NULL;
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
	this->v = 0;
	this->a = 0;
	this->j = 0;
	this->h = 0;
	this->floor = 0;
	this->setFloor = NULL;
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
	this->v = 0;
	this->a = 0;
	this->j = 0;
	this->h = 0;
	this->floor = 0;
	this->setFloor = NULL;
	this->cabinWeight = cabinWeight;
	this->counterWeight = counterWeight;
	this->passengerWeight = 0;
	for (int i = 0; i <= numFloors; i++) {
		this->floorHeights.push_back(floorHeight * i);
	}
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
	while (this->timePassed < t1)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed < t2)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed < t3)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed < t4)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstVel(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed < t5)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed < t6)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed < t7)
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
	while (this->timePassed < t1)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed < t2)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed < t3)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed < t4)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstVel(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed < t5)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed < t6)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed < t7)
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
	while (this->timePassed < t1)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed < t2)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed < t3)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed < t4)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed < t5)
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
	while (this->timePassed < t1)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed < t2)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed < t3)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = 0;
	while (this->timePassed < t4)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstAcc(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed < t5)
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
	while (this->timePassed < t1)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed < t2)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed < t3)
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
	while (this->timePassed < t1)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed < t2)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed < t3)
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
	while (this->timePassed < t1)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		printf("j = %f\na = %f\nv = %f\nh = %f\n\n", this->j, this->a, this->v, this->h);
		this->log();
	}
	this->j = -this->jn;
	while (this->timePassed < t2)
	{
		this_thread::sleep_for(this->cycleTime);
		this->moveWithConstJerk(this->cycleTime);
		this->checkFloor();
		this->timePassed += this->cycleTime.count() / 1000.;
		printf("j = %f\na = %f\nv = %f\nh = %f\n\n", this->j, this->a, this->v, this->h);
		this->log();
	}
	this->j = this->jn;
	while (this->timePassed < t3)
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
	this->openDoors();
}

void Elevator::openDoors()
{
	cout << "Opening doors" << endl;
	for (int i = 0; i < 10; i++) {
		this_thread::sleep_for(this->cycleTime);
	}
	cout << "Closing doors" << endl;
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
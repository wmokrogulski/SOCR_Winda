#include "Elevator.h"

Elevator::Elevator()
{
	this->vn = 1;
	this->an = 1;
	this->jn = 1;
	this->v = 0;
	this->a = 0;
	this->j = 0;
	this->h = 0;
	this->floor = 0;
	this->setFloor = NULL;
	this->cabinWeight = 800;
	this->counterWeight = 1200;
	this->passengerWeight = 0;
}

Elevator::Elevator(double vn, double an, double jn)
{
	this->vn = vn;
	this->an = an;
	this->jn = jn;
	this->v = 0;
	this->a = 0;
	this->j = 0;
	this->h = 0;
	this->floor = 0;
	this->setFloor = NULL;
	this->cabinWeight = 800;
	this->counterWeight = 1200;
	this->passengerWeight = 0;
}

Elevator::Elevator(double vn, double an, double jn, double cabinWeight, double counterWeight)
{
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
}

void Elevator::moveWithConstJerk(chrono::milliseconds timeStep)
{
	double tS = timeStep.count()/1000.;
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

void Elevator::testMove(int fps)
{
	chrono::milliseconds timeStep(1000/fps);
	double timePassed = 0;
	this->j = this->jn;
	while ((this->a)<(this->an))
	{
		this_thread::sleep_for(timeStep);
		this->moveWithConstJerk(timeStep);
		timePassed += timeStep.count() / 1000.;
		printf("j = %f\na = %f\nv = %f\nh = %f\n\n", this->j, this->a, this->v, this->h);
	}
	this->j = 0;
	while ((this->v) < ((this->vn) - (this->an * this->an) / (2 * this->j)))
	{
		this_thread::sleep_for(timeStep);
		this->moveWithConstAcc(timeStep);
		timePassed += timeStep.count() / 1000.;
		printf("j = %f\na = %f\nv = %f\nh = %f\n\n", this->j, this->a, this->v, this->h);
	}
	this->j = -this->jn;
	while ((this->a) > 0)
	{
		this_thread::sleep_for(timeStep);
		this->moveWithConstJerk(timeStep);
		timePassed += timeStep.count() / 1000.;
		printf("j = %f\na = %f\nv = %f\nh = %f\n\n", this->j, this->a, this->v, this->h);
	}
	this->j = 0;
	// HERE GOES CONSTANT VELOCITY
	this->j = -this->jn;
	while ((this->a) > -this->an)
	{
		this_thread::sleep_for(timeStep);
		this->moveWithConstJerk(timeStep); 
		timePassed += timeStep.count() / 1000.;
		printf("j = %f\na = %f\nv = %f\nh = %f\n\n", this->j, this->a, this->v, this->h);
	}
	this->j = 0;
	while ((this->v) > (this->an * this->an) / (2 * this->j))
	{
		this_thread::sleep_for(timeStep);
		this->moveWithConstAcc(timeStep);
		timePassed += timeStep.count() / 1000.;
		printf("j = %f\na = %f\nv = %f\nh = %f\n\n", this->j, this->a, this->v, this->h);
	}
	this->j = this->jn;
	while ((this->a) < 0)
	{
		this_thread::sleep_for(timeStep);
		this->moveWithConstJerk(timeStep);
		timePassed += timeStep.count() / 1000.;
		printf("j = %f\na = %f\nv = %f\nh = %f\n\n", this->j, this->a, this->v, this->h);
	}
	this->j = 0;
	printf("j = %f\na = %f\nv = %f\nh = %f\n\n", this->j, this->a, this->v, this->h);
	cout << "Time passed: " << timePassed << "s" << endl;	
}

double Elevator::getHeight()
{
	return this->h;
}

#include <iostream>
#include "Call.h"
#include "Elevator.h"

using namespace std;

int main()
{
    cout << "Elevator\n";
    Elevator elevator=Elevator(5,2.5,2,1,1);
    elevator.enableLog();
    elevator.moveToFloor(3);
    elevator.moveToFloor(4);
    elevator.moveToFloor(2);
    elevator.moveToFloor(1);
}
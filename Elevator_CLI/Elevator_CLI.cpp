#include <iostream>
#include "Call.h"
#include "Elevator.h"
#include "ElevatorController.h"

using namespace std;

int main()
{
    cout << "Elevator\n";
   /* Elevator e(5);
    e.enableLog();
    e.advMoveToFloor(4);
    cout << e.checkPrecision() << endl;*/
    ElevatorController ec = ElevatorController(Elevator(5));
    ec.setMode(closestCall);
    ec.enableLog();
    ec.testCalls3();
    return 0;
}
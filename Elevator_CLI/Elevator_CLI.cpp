#include <iostream>
#include "Call.h"
#include "Elevator.h"
#include "ElevatorController.h"

using namespace std;

int main()
{
    srand(time(NULL));
    cout << "Elevator\n";
    /*Elevator e(5);
    e.enableLog();
    e.moveToFloor(2);*/
    //e.advMoveToFloor(4);
    //cout << e.checkPrecision() << endl;
    ElevatorController ec = ElevatorController(Elevator(5));
    ec.setMode(earliestCall);
    ec.enableLog();
    ec.testCalls3();
    ec.printQualityIndexes();
    return 0;
}
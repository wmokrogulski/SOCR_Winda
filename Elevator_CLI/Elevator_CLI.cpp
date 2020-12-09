#include <iostream>
#include "Call.h"
#include "Elevator.h"
#include "ElevatorController.h"

using namespace std;

int main()
{
    srand(time(NULL));
    cout << "Elevator\n";
    ElevatorController ec = ElevatorController(Elevator(5));
    ec.setMode(earliestCall);
    ec.enableLog();
    ec.testCalls3();
    ec.printQualityIndexes();
    return 0;
}
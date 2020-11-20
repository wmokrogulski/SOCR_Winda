#include <iostream>
#include "Call.h"
#include "Elevator.h"
#include "ElevatorController.h"

using namespace std;

int main()
{
    cout << "Elevator\n";
    ElevatorController ec = ElevatorController(Elevator(5, 2.5, 2, 1, 1));
    ec.enableLog();
    ec.activate();
    ec.addCall(Call(4));
    ec.addCall(Call(3));
    ec.addCall(Call(2));
    ec.addCall(Call(3));
    ec.addCall(Call(1));
    ec.addCall(Call(0));
    ec.deactivate();
    return 0;
}
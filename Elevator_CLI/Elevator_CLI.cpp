#include <iostream>
#include "Call.h"
#include "Elevator.h"

using namespace std;

int main()
{
    cout << "Elevator\n";
    Elevator elevator=Elevator(2,1,1);
    elevator.testMove(50);
}
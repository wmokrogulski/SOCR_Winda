#include "RTOS_Elevator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RTOS_Elevator w;
    w.show();
    return a.exec();
}

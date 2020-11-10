#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RTOS_Elevator.h"

class RTOS_Elevator : public QMainWindow
{
    Q_OBJECT

public:
    RTOS_Elevator(QWidget *parent = Q_NULLPTR);

private:
    Ui::RTOS_ElevatorClass ui;
};

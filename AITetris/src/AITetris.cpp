//============================================================================
// Name        : AITetris.cpp
// Author      : SKJ.Guan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Controller.h"
#include "Robot.h"
#include <thread>

void autoRunFunc() {

	auto robot = Robot::getRobot();
//	robot->PSOCalculator();
	robot->autoplay();

}

int main() {

	auto controller = Controller::getTcontroller();


	std::thread r(autoRunFunc);
	r.detach();

	controller->init();
	controller->runGame();

	return 0;
}

//============================================================================
// Name        : AITetris.cpp
// Author      : SKJ.Guan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Controller.h"

int main() {

	auto controller = Controller::getTcontroller();

	controller->init();
	controller->runGame();

	return 0;
}

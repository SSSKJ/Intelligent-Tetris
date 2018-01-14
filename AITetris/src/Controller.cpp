/*
 * Controller.cpp
 *
 *  Created on: 2018Äê1ÔÂ11ÈÕ
 *      Author: SKJ.Guan
 */

#include "Controller.h"
#include "Tetrisgenerator.h"
#include "Window.h"

Controller::Controller() {
	// TODO Auto-generated constructor stub

}

std::unique_ptr<Controller> Controller::getTcontroller() {

	if (Tcontroller == NULL)
		Tcontroller = std::unique_ptr<Controller>(new Controller());
	return Tcontroller;

}

void Controller::runGame() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();

	Tgenerator->generateTetris();

}

void Controller::KeyBoardHandler() {

}

void Controller::moveDown() {

}

void Controller::moveLeft() {

}

void Controller::moveRight() {

}

void Controller::fall() {

}

void Controller::transform() {

}

bool Controller::checkcollision() {
	return 1;
}

void Controller::insertTetris() {

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

std::unique_ptr<Controller> Controller::Tcontroller = NULL;


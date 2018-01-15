/*
 * Controller.cpp
 *
 *  Created on: 2018Äê1ÔÂ11ÈÕ
 *      Author: SKJ.Guan
 */

#include "Controller.h"
#include "Tetrisgenerator.h"
#include "Window.h"
#include <conio.h>

Controller::Controller() : end(false), level(1) {
	// TODO Auto-generated constructor stub

}

std::shared_ptr<Controller> Controller::getTcontroller() {

	if (Tcontroller == NULL)
		Tcontroller = std::shared_ptr<Controller>(new Controller());
	return Tcontroller;

}

void init() {
	//print the menu
}

void Controller::runGame() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	Tgenerator->generateTetris();
	insertTetris();
	KeyBoardHandler();

}

void autoRun() {
	//call the AI-function
}

void Controller::KeyBoardHandler() {

	int key = 0;
	clock_t last, now;
	last = clock();

	while (!end) {
		while (_kbhit()) {
			now = clock();
			autoMove(last, now);
			key = _getch();
			if (key == 27) { //esc
				end = 1;
				break;
			} else {
				switch(key) {
					case 'w' : case 'W' : case '8' : case '38' :
						if (!checkcollision())
							transform();
						break;
					case 's' : case 'S' : case '2' : case '40' :
						fall();
						break;
					case 'a' : case 'A' : case '4' : case '37' :
						if (!checkcollision())
							moveLeft();
						break;
					case 'd' : case 'D' : case '6' : case '39' :
						if (!checkcollision())
							moveRight();
						break;
					default:
						break;
				}
			}
		}
		now = clock();
		autoMove(last, now);
	}
}

void Controller::autoMove(clock_t& last, clock_t& now) {
	if (last - now > 1f / level) {
		moveDown();
		last = now;
	}
}

void removeTetris() {

}

void insertTetris() {

}

void Controller::moveDown() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	removeTetris();
	int y = Tgenerator->getY();
	Tgenerator->setY(y + 1);
	if (!checkcollision()) {
		insertTetris();
		//print the Tetris
	} else {
		Tgenerator->generateTetris();
		insertTetris();
	}
}

void Controller::moveLeft() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	removeTetris();
	int x = Tgenerator->getX();
	Tgenerator->setX(x - 1);
	if (!checkcollision()) {
		insertTetris();
		//print the Tetris
	} else {
		Tgenerator->setX(x);
		insertTetris();
	}
}

void Controller::moveRight() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	removeTetris();
	int x = Tgenerator->getX();
	Tgenerator->setX(x + 1);
	if (!checkcollision()) {
		insertTetris();
		//print the Tetris
	} else {
		Tgenerator->setX(x);
		insertTetris();
	}
}

void Controller::fall() {

}

void Controller::transform() {

}

bool Controller::checkcollision() {
	return 1;
}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

std::unique_ptr<Controller> Controller::Tcontroller = NULL;


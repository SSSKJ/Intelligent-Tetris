/*
 * Controller.cpp
 *
 *  Created on: 2018Äê1ÔÂ11ÈÕ
 *      Author: SKJ.Guan
 */

#include "Controller.h"
#include "Tetrisgenerator.h"
#include "Window.h"
#include "Vardefine.h"
#include <conio.h>
#include <cstring>
#include <stack>

Controller::Controller() : end(false), level(1), point(0), counter(0) {
	// TODO Auto-generated constructor stub
	memcpy(Gamepool, Originalgamepool, sizeof(uint16_t [poolDeep + Wall]));
	recorder = new Model();
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

void Controller::restart() {
	end = false;
	level = 0;
	point = 0;
	counter = 0;
	memcpy(Gamepool, Originalgamepool, sizeof(uint16_t [poolDeep + Wall]));
	//print the game pool
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
					case 'r' :
						restart();
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

void Controller::removeTetris() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	uint16_t Tetris = Tgenerator->getTetris();

	int y = Tgenerator->getY();
	int x = Tgenerator->getX();

	Gamepool[y] &= ~(((Tetris >> 12) & 0x000f) << (x - 3));
	Gamepool[y + 1] &= ~(((Tetris >> 8) & 0x000f) << (x - 3)) ;
	Gamepool[y + 2] &= ~(((Tetris >> 4) & 0x000f) << (x - 3)) ;
	Gamepool[y + 3] &= ~((Tetris & 0x000f) << (x - 3)) ;

}

void Controller::insertTetris() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	uint16_t Tetris = Tgenerator->getTetris();

	int y = Tgenerator->getY();
	int x = Tgenerator->getX();

	Gamepool[y] |= ((Tetris >> 12) & 0x000f) << (x - 3);
	Gamepool[y + 1] |= ((Tetris >> 8) & 0x000f) << (x - 3);
	Gamepool[y + 2] |= ((Tetris >> 4) & 0x000f) << (x - 3);
	Gamepool[y + 3] |= (Tetris & 0x000f) << (x - 3);

}

void Controller::checkerasing() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	uint16_t Tetris = Tgenerator->getTetris();

	int mark = 0;

	for (int i = 0; i < 4; i++) {
		if (Gamepool[Tgenerator->getY() + i] & 0xffff) {
			memmove(Gamepool + 1, Gamepool, sizeof(uint16_t) * Tgenerator->getY());
			mark++;
		}
	}

	if (mark == 0)
		return;

	switch(mark) {
		case 1 :
			point = point + 10;
			break;
		case 2 :
			point = point + 25;
			break;
		case 3 :
			point = point + 40;
			break;
		case 4 :
			point = point + 55;
			break;
		default:
			break;
	}

	counter = counter + mark;

	if (counter >= 30)
		level++;

	//print the game pool

}

void Controller::checkend() {
	if ((Gamepool[0] | Gamepool[1] | Gamepool[2] | Gamepool[3]) & 0x3ffc)
		return;
	end = 1;
}

void Controller::moveDown() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	removeTetris();
	Tgenerator->getStatus(recorder);
	Tgenerator->setY(recorder.y + 1);
	if (!checkcollision()) {
		insertTetris();
		//remove the last one
		//print the Tetris
	} else {
		checkerasing();
		checkend();
		Tgenerator->generateTetris();
		insertTetris();
		//print the Tetris
	}
}

void Controller::moveLeft() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	removeTetris();
	Tgenerator->getStatus(recorder);
	Tgenerator->setX(recorder.x - 1);
	if (!checkcollision()) {
		insertTetris();
		//remove the last one
		//print the Tetris
	} else {
		Tgenerator->reset(recorder);
		insertTetris();
	}
}

void Controller::moveRight() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	removeTetris();
	Tgenerator->getStatus(recorder);
	Tgenerator->setX(recorder.x + 1);
	if (!checkcollision()) {
		insertTetris();
		//remove the last one
		//print the Tetris
	} else {
		Tgenerator->reset(recorder);
		insertTetris();
	}
}

void Controller::fall() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	removeTetris();
	//remove the Tetris

	do {
		Tgenerator->getStatus(recorder);
		Tgenerator->setY(recorder.y + 1);
	} while (!checkcollision());

	Tgenerator->reset(recorder);
	insertTetris();
	//print the Tetris
	checkerasing();
	checkend();
	Tgenerator->reset(recorder);
	insertTetris();
	//print the Tetris
}

void Controller::transform() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	removeTetris();
	Tgenerator->getStatus(recorder);
	Tgenerator->CWRotate();
	if (!checkcollision()) {
		insertTetris();
		//remove the last one
		//print the Tetris
	} else {
		Tgenerator->reset(recorder);
		insertTetris();
	}
}

bool Controller::checkcollision() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	uint16_t Tetris = Tgenerator->getTetris();

	int y = Tgenerator->getY();
	int x = Tgenerator->getX();

	for (int i = 0; i < 4; i++) {
		if (Gamepool[y + i] & ((Tetris >> ((3 - i) * 4)) & 0x000f) << (x - 3))
			return 0;
	}

	return 1;
}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

std::unique_ptr<Controller> Controller::Tcontroller = NULL;


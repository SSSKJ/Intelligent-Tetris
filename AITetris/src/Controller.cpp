/*
 * Controller.cpp
 *
 *  Created on: 2018��1��11��
 *      Author: SKJ.Guan
 */

#include "Tetrisgenerator.h"
#include "DrawingTool.h"
#include "Controller.h"
//#include "Vardefine.h"
//#include "Robot.h"
//#include <time.h>
#include <thread>
#include <conio.h>
#include <cstring>
#include <stack>
//#include <iostream>
//#include <memory>

Controller::Controller() : end(false), level(1), point(0), counter(0) {
	// TODO Auto-generated constructor stub
	memcpy(Gamepool, Originalgamepool, sizeof(uint16_t [poolDeep + Wall]));
}

std::shared_ptr<Controller> Controller::getTcontroller() {

	if (Tcontroller == NULL)
		Tcontroller = std::shared_ptr<Controller>(new Controller());

	return Tcontroller;

}

void Controller::init() {

	auto tool = DrawingTool::getTool();
	tool->DrawTheMenu(); //print the menu

}

void Controller::runGame() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	auto tool = DrawingTool::getTool();

	Tgenerator->generateTetris();
	insertTetris();
	tool->printNextTetris(Tgenerator->getNextTetris(), Tgenerator->getNextColor());
	tool->handleCurrentTetris(iTetrispattern);
	KeyBoardHandler();

}

void Controller::restart() {

	auto tool = DrawingTool::getTool();
	auto Tgenerator = Tetrisgenerator::getTgenerator();

	end = false;
	level = 1;
	point = 0;
	counter = 0;
	memcpy(Gamepool, Originalgamepool, sizeof(uint16_t [poolDeep + Wall]));
	tool->updateInfo('l');
	tool->updateInfo('p');
	tool->updateInfo('c');
	tool->reprint(poolDeep - 1); //print the game pool
	Tgenerator->generateTetris();
	insertTetris();
	tool->handleCurrentTetris(iTetrispattern); //print the Tetris
	tool->printNextTetris(Tgenerator->getNextTetris(), Tgenerator->getNextColor());
	tool->printNextTetris(Tgenerator->getNextTetris(), Tgenerator->getNextColor());

}

void Controller::autoRun() {
	//call the AI-function
	auto robot = Robot::getRobot();
	robot->setStatus(!(robot->getStatus()));

}

void Controller::KeyBoardHandler() {

	auto tool = DrawingTool::getTool();

	int key = 0;
	clock_t last, now;
	last = clock();

	while (1) {

		while (end) {

			key = getch();
			if (key == 'r') {

				restart();
				last = clock();

			}

		};

		if (kbhit()) {

			now = clock();
			autoMove(last, now);
			key = getch();

			if (key == 27) { //esc

				end = 1;
				break;

			} else {
				InputHandler(key);
			}

		}

		now = clock();
		autoMove(last, now);

	}

//	tool->gameOver();

	while (1) {

		key = getch();

		if (key == 27)
			return;

	}

}

void Controller::autoMove(clock_t& last, clock_t& now) {

	if (now - last > 0.8f / level * CLOCKS_PER_SEC) {

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
	auto tool = DrawingTool::getTool();

	int mark = 0;
	int y = Tgenerator->getY();

	for (;(y < poolDeep) && y < Tgenerator->getY() + 4; y++) {

		if (Gamepool[y] == 0xffff) {

			memmove(Gamepool + 1, Gamepool, sizeof(uint16_t) * y);
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

	tool->updateInfo('p');

	counter = counter + mark;
	tool->updateInfo('c');

//	if (counter / ValueToLevelUp >= level) {
//
//		level++;
//		tool->updateInfo('l');
//
//	}

	tool->reprint(y - 1); //print the game pool

}

void Controller::checkend() {

	if ((Gamepool[0] | Gamepool[1] | Gamepool[2] | Gamepool[3]) & 0x3ffc)
		end = 1;

}

void Controller::moveDown() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	auto tool = DrawingTool::getTool();

	recorder = Tgenerator->getStatus();
	removeTetris();
	Tgenerator->setY(recorder.y + 1);

	if (!checkcollision()) {

		insertTetris();
		tool->handleTetris(recorder, rTetrispattern); //remove the last one
		tool->handleCurrentTetris(iTetrispattern); //print the Tetris

	} else {

		Tgenerator->reset(recorder);
		insertTetris();
		checkerasing();
		checkend();
		Tgenerator->generateTetris();
		insertTetris();
		tool->handleCurrentTetris(iTetrispattern); //print the Tetris
		tool->printNextTetris(Tgenerator->getNextTetris(), Tgenerator->getNextColor());

	}

}

void Controller::moveLeft() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	auto tool = DrawingTool::getTool();

	recorder = Tgenerator->getStatus();
	removeTetris();
	Tgenerator->setX(recorder.x + 1);

	if (!checkcollision()) {

		insertTetris();
		tool->handleTetris(recorder, rTetrispattern); //remove the last one
		tool->handleCurrentTetris(iTetrispattern); //print the Tetris

	} else {

		Tgenerator->reset(recorder);
		insertTetris();

	}

}

void Controller::moveRight() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	auto tool = DrawingTool::getTool();

	recorder = Tgenerator->getStatus();
	removeTetris();
	Tgenerator->setX(recorder.x - 1);

	if (!checkcollision()) {

		insertTetris();
		tool->handleTetris(recorder, rTetrispattern);//remove the last one
		tool->handleCurrentTetris(iTetrispattern);//print the Tetris

	} else {

		Tgenerator->reset(recorder);
		insertTetris();

	}

}

void Controller::fall() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	auto tool = DrawingTool::getTool();

	removeTetris();
	tool->handleCurrentTetris(rTetrispattern); //remove the Tetris

	do {

		recorder = Tgenerator->getStatus();
		Tgenerator->setY(recorder.y + 1);

	} while (!checkcollision());

	Tgenerator->reset(recorder);
	insertTetris();
	tool->handleCurrentTetris(iTetrispattern); //print the Tetris
	checkerasing();
	checkend();
	Tgenerator->generateTetris();
	insertTetris();
	tool->handleCurrentTetris(iTetrispattern); //print the Tetris
	tool->printNextTetris(Tgenerator->getNextTetris(), Tgenerator->getNextColor());

}

void Controller::transform() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	auto tool = DrawingTool::getTool();

	recorder = Tgenerator->getStatus();
	removeTetris();
	Tgenerator->CWRotate();

	if (!checkcollision()) {

		insertTetris();
		tool->handleTetris(recorder, rTetrispattern); //remove the last one
		tool->handleCurrentTetris(iTetrispattern); //print the Tetris

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

		if (Gamepool[y + i] & (((Tetris >> ((3 - i) * 4)) & 0x000f) << (x - 3)))
			return 1;

	}

	return 0;
}

uint16_t* Controller::getGamepool() {
	return Gamepool;
}

int Controller::getLevel() {
	return level;
}

int Controller::getPoint() {
	return point;
}

int Controller::getCounter() {
	return counter;
}

bool Controller::ifend() {
	return end;
}

void Controller::InputHandler(const char input) {

	switch(input) {

		case 'w' : case 'W' : case 72 :

			transform();
			break;

		case 's' : case 'S' : case 80 :

			moveDown();
			break;

		case 'a' : case 'A' : case 75 :
			moveLeft();
			break;

		case 'd' : case 'D' : case 77 :

			moveRight();
			break;

		case ' ' :

			fall();
			break;

		case 'v' : case 'V' :

			autoRun();
			break;

		case 'r' : case 'R' :

			restart();
			break;

		default:
			break;

	}

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<Controller> Controller::Tcontroller = NULL;


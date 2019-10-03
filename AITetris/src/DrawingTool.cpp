/*
 * Window.cpp
 *
 *  Created on: 2018Äê1ÔÂ14ÈÕ
 *      Author: SKJ.Guan
 */

#include "Tetrisgenerator.h"
#include "DrawingTool.h"
#include "Controller.h"
#include "Vardefine.h"
//#include <iostream>
//#include <string>
//#include <memory>
using std::cout;
using std::endl;
using std::string;

DrawingTool::DrawingTool() {

	// TODO Auto-generated constructor stub
	hout = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTitle("Tetris");
	SMALL_RECT rc = {0, 0, windowWidth, windowLength};
	SetConsoleWindowInfo(hout, true, &rc);// set the windows' size
	CONSOLE_CURSOR_INFO cci = { 25, false };
	SetConsoleCursorInfo(hout, &cci);// hide the cursor

}

void DrawingTool::DrawTheMenu() {

//	string s = "mode con cols=" + std::to_string(windowWidth) + " lines=" + std::to_string(windowLength);
//	const char * y = s.c_str();
//	system(y);
	for (int i = 0; i < windowLength; i++)
		cout << menu[i] << endl;

}

std::shared_ptr<DrawingTool> DrawingTool::getTool() {

	if (tool == NULL)
		tool = std::shared_ptr<DrawingTool>(new DrawingTool());
	return tool;

}

void DrawingTool::gotoXY(const int x, const int y) {

	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(hout, cd);

}

void DrawingTool::handleCurrentTetris(const string Tetrispattern) {//remove Tetris by passing the remove-Tetris-pattern and insert Tetris by passing the insert-Tetris-pattern

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	Model tetris = Tgenerator->getStatus();

	int color = Tgenerator->getColor();

	for (int i = 0; i < 4; i++) {

		int rY = tetris.coordinate[i] / 4;
		int rX = tetris.coordinate[i] % 4;
		int x = poolStartX + 2 * (poolWidth - 1 - (tetris.x - rX - Wall));
		int y = tetris.y + poolStartY + rY - 4;

		if (tetris.y + rY - 4 >= 0) {

			gotoXY(x, y);
			SetConsoleTextAttribute(hout, color);
			cout << Tetrispattern;

		}

	}

}

void DrawingTool::handleTetris(const Model tetris, const string Tetrispattern) {

	for (int i = 0; i < 4; i++) {

		int rY = tetris.coordinate[i] / 4;
		int rX = tetris.coordinate[i] % 4;
		int x = poolStartX + 2 * (poolWidth - 1 - (tetris.x - rX - Wall));
		int y = tetris.y + poolStartY + rY - 4;

		if (tetris.y + rY - 4 >= 0) {

			gotoXY(x, y);
			cout << Tetrispattern;

		}

	}

}

void DrawingTool::reprint(int y) {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	auto Tcontroller = Controller::getTcontroller();
	uint16_t* pool = Tcontroller->getGamepool();

	SetConsoleTextAttribute(hout, FOREGROUND_RED |  FOREGROUND_GREEN |  FOREGROUND_BLUE);

	for (int i = 4; i <= y; i++) {

		gotoXY(poolStartX, poolStartY + i - 4);
		uint16_t temp = *(pool + i) >> 2;

		for (int j = 11; j >= 0; j--) {

			if ((temp >> j) & 0x0001)
				cout << iTetrispattern;
			else
				cout << rTetrispattern;
		}

	}

}

void DrawingTool::printNextTetris(const uint16_t nextTetris, const int color) {



	for (int i = 3; i >= 0; i--) {

		gotoXY(showStartX, showStartY + 3 - i);

		for (int j = 3; j >= 0; j--) {

			if ((nextTetris >> ((i * 4) + j)) & 0x0001) {
				SetConsoleTextAttribute(hout, color);
				cout << iTetrispattern;
			} else
				cout << rTetrispattern;

		}

	}

}

void DrawingTool::updateInfo(const int info) {

	auto Tcontroller = Controller::getTcontroller();

	SetConsoleTextAttribute(hout, FOREGROUND_RED |  FOREGROUND_GREEN |  FOREGROUND_BLUE);

	switch(info) {

		case 'l' :

			gotoXY(showInfoX, showLevelY);
			cout << Tcontroller->getLevel();
			break;

		case 'p' :

			gotoXY(showInfoX, showPointY);
			cout << Tcontroller->getPoint();
			if (Tcontroller->getPoint() == 0)
				cout << "       ";
			break;

		case 'c' :

			gotoXY(showInfoX, showCounterY);
			cout << Tcontroller->getCounter();
			if (Tcontroller->getCounter() == 0)
				cout << "       ";
			break;

		default:

			break;

	}

}

void DrawingTool::gameOver() {

	gotoXY(showGameOverX, showGameOverY);
	SetConsoleTextAttribute(hout, FOREGROUND_RED |   FOREGROUND_GREEN);
	cout << "Game Over!!";

}

void DrawingTool::printtest(int mark, int i, int y) {

	gotoXY(0, 29 + i);
	cout << mark << " " << y;

}

DrawingTool::~DrawingTool() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<DrawingTool> DrawingTool::tool = NULL;


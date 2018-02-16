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
#include <iostream>
#include <string>
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
	cout << endl;
	for (int i = 0; i < windowLength; i++)
		cout << menu[i] << endl;

}

std::shared_ptr<DrawingTool> DrawingTool::getTool() {

	if (tool == NULL)
		tool = std::shared_ptr<DrawingTool>(new DrawingTool());
	return tool;

}

void DrawingTool::gotoXY(int x, int y) {

	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(hout, cd);

}

void DrawingTool::handleCurrentTetris(const string Tetrispattern) {//remove Tetris by passing the remove-Tetris-pattern and insert Tetris by passing the insert-Tetris-pattern

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	Model tetris;

	Tgenerator->getStatus(tetris);

	for (int i = 0; i < 4; i++) {

		int rY = tetris.coordinate[i] / 4;
		int rX = tetris.coordinate[i] % 4;
		gotoXY(poolStartX + 2 * poolWidth - (tetris.x - rX) , tetris.y + poolStartY + rY);
		cout << Tetrispattern;

	}

}

void DrawingTool::handleTetris(const Model tetris, const string Tetrispattern) {

	for (int i = 0; i < 4; i++) {

			int rY = tetris.coordinate[i] / 4;
			int rX = tetris.coordinate[i] % 4;
			gotoXY(poolStartX + 2 * poolWidth - (tetris.x - rX) , tetris.y + poolStartY + rY);
			cout << Tetrispattern;

	}

}

void DrawingTool::reprint(int y) {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	auto Tcontroller = Controller::getTcontroller();
	auto pool = Tcontroller->getGamepool();

	for (int i = 0; i < y; i++) {

		gotoXY(poolStartX, poolStartY + i);
		uint16_t temp = *(pool + i) >> 2;

		for (int j = 11; j > 0; j--) {

			if ((temp >> j) & 0x0001)
				cout << iTetrispattern;
			else
				cout << rTetrispattern;
		}

	}

}

void DrawingTool::printNextTetris() {

	auto Tgenerator = Tetrisgenerator::getTgenerator();
	auto Tetris = Tgenerator->getTetris();

	for (int i = 3; i >= 0; i--) {

		gotoXY(showStartX, showStartY + 3 - i);

		for (int j = 3; j >= 0; j--) {

			if ((Tetris >> ((i * 4) + j)) & 0x0001)
				cout << iTetrispattern;
			else
				cout << rTetrispattern;

		}

	}

}

void DrawingTool::printtest() {

}

DrawingTool::~DrawingTool() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<DrawingTool> DrawingTool::tool = NULL;


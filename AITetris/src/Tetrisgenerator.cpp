/*
 * Tetris.cpp
 *
 *  Created on: 2018Äê1ÔÂ10ÈÕ
 *      Author: SKJ.Guan
 */

#include "Tetrisgenerator.h"
#include "Vardefine.h"
#include <random>
#include <iostream>
#include <ctime>
#include <cstring>

Tetrisgenerator::Tetrisgenerator() : x(0), y(0) {
	memset(type, -1, sizeof(type));
	memset(orientation, -1, sizeof(orientation));
}

std::shared_ptr<Tetrisgenerator> Tetrisgenerator::getTgenerator() {

	if (Tgenerator == NULL) {
		Tgenerator = std::shared_ptr<Tetrisgenerator>(new Tetrisgenerator());
	}
	return Tgenerator;

}

int Tetrisgenerator::getX() {
	return x;
}

bool Tetrisgenerator::setX(int val) {
	x = val;
	return true;
}

int Tetrisgenerator::getY() {
	return y;
}

bool Tetrisgenerator::setY(int val) {
	y = val;
	return true;
}

void Tetrisgenerator::CWRotate() {

	if (orientation[0] == -1)
		return;

	orientation[0] = orientation[0] + 1;
	if (orientation[0] > 3)
		orientation[0] = 0;

	recordCoordinate();
}

void Tetrisgenerator::antiCWRotate() {

	if (orientation[0] == -1)
		return;

	orientation[0] = orientation[0] - 1;
	if (orientation[0] < 0)
		orientation[0] = 3;

	recordCoordinate();

}

void Tetrisgenerator::nextTetris() {

	static std::default_random_engine e(time(0));
	static std::uniform_int_distribution<unsigned> t(0, 6), o(0, 3);

	type[0] = type[1];
	orientation[0] = orientation[1];
	type[1] = t(e);
	orientation[1] = o(e);

	if (type[0] == -1)
		nextTetris();

}

void Tetrisgenerator::recordCoordinate() {

	uint16_t Tetris = getTetris();
	int mark = 0;

	for (int i = 0; i < 16; i++) {

		if (Tetris & 1 == 1) {
			coordinate[mark] = 15 - i;
			mark++;
		}

		if (mark >= 4)
			return;

		Tetris = Tetris >> 1;
	}
}

void Tetrisgenerator::generateTetris() {

	nextTetris();
	recordCoordinate();

	uint16_t Tetris = getTetris();

	if (Tetris & 0x000f)
		y = 0;
	else {
		y = (Tetris & 0x00f0)?1:2;
	}

	x = 9;

}

int* Tetrisgenerator::getCoordinate() {
	return coordinate;
}

void Tetrisgenerator::getStatus(Model& status) {

	status.x = x;
	status.y = y;
	status.orientation = orientation[0];
	memcpy(status.coordinate, coordinate, sizeof(int[4]));

}

void Tetrisgenerator::reset(Model lastStatus) {

	x = lastStatus.x;
	y = lastStatus.y;
	orientation[0] = lastStatus.orientation;
	memcpy(coordinate, lastStatus.coordinate, sizeof(int[4]));

}

uint16_t Tetrisgenerator::getTetris() {

	return Tetrisshape[type[0]][orientation[0]];

}

Tetrisgenerator::~Tetrisgenerator() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<Tetrisgenerator> Tetrisgenerator::Tgenerator = NULL;


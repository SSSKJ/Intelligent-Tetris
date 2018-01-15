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

void Tetrisgenerator::rotate() {
	if (orientation[0] > -1)
		orientation[0] = orientation[0] + 1;
	else
		orientation[0] = 0;
	if (orientation[0] > 3)
		orientation[0] = 0;
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

void Tetrisgenerator::generateTetris() {

	nextTetris();

	uint16_t Tetris = Tetrisshape[type[0]][orientation[0]];

	if (Tetris & 0x000f)
		y = 0;
	else {
		y = (Tetris & 0x00f0)?1:2;
	}

	x = 6;

}

Tetrisgenerator::~Tetrisgenerator() {
	// TODO Auto-generated destructor stub
}

std::unique_ptr<Tetrisgenerator> Tetrisgenerator::Tgenerator = NULL;


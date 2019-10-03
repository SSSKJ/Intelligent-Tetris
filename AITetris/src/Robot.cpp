/*
 * Robot.cpp
 *
 *  Created on: 2018Äê3ÔÂ25ÈÕ
 *      Author: SKJ.Guan
 */

#include "Tetrisgenerator.h"
#include "Controller.h"
#include "Robot.h"
#include <windows.h>
#include <time.h>
#include <math.h>

Robot::Robot() : status(false), a1(0), a2(0), a3(0), a4(0), a5(0), a6(0), timer(0), maxV(10), minV(1) {
	// TODO Auto-generated constructor stub

	srand((unsigned)time(NULL));

	for (int i = 0; i < 25; i++) {

		for (int j = 0; j < 6; j++) {
			calculate[i][j] = rand()/double(RAND_MAX) * 100 - 50;
//			if (j == 1)
//				calculate[i][j] = calculate[i][j] * (-1);
			v[i][j] = rand()/double(RAND_MAX) * 20 - 10;

//			std::cout << calculate[i][j] << " ";
		}

//		std::cout << std::endl;
	}
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<Robot> Robot::getRobot() {

	if (robot == NULL)
		robot = std::shared_ptr<Robot>(new Robot());
	return robot;

}

bool Robot::getStatus() {
	return status;
}

void Robot::setStatus(bool s) {
	status = s;
}

void Robot::autoplay() {

	auto Tcontroller = Controller::getTcontroller();

	a1 = -49.8714;
	a2 = 76.0128;
	a3 = -7.77284;
	a4 = -16.8268;
	a5 = -146.748;
	a6 = -56.097;
	status = 1;

	for (int i = 0; i < 4; i++) {

		timer = clock();
		keybd_event('R', 0, 0, 0);
		keybd_event('R', 0, KEYEVENTF_KEYUP, 0);
		Sleep(50);
		play();
		timer = clock() - timer;
		gotoXY(0, poolDeep + 4 + i);
		std::cout << Tcontroller->getCounter() << " " << timer << " " << Tcontroller->getPoint() << " i: " << i;
		std::cout << std::endl;

	}

}

void Robot::play() {

	auto Tcontroller = Controller::getTcontroller();
	auto Tgenerator = Tetrisgenerator::getTgenerator();

//	std::cout << "playing...please wait for losing" << std::endl;
	while (!Tcontroller->ifend()) {

		if (status) {

			while (!Tgenerator->getMarker()) {}
			tetris = Tgenerator->getStatus();
			Tgenerator->setMarker(0);
			setGamepool(Tcontroller->getGamepool());

			SimulatorModel position = getRecommandPos();


			for (int i = 0; i < position.rotateTimes; i++) {

				keybd_event('W', 0, 0, 0);
				keybd_event('W', 0, KEYEVENTF_KEYUP, 0);
				Sleep(RobotRate);

			}

			for (int i = 0; i < abs(position.moveTimes) && !Tcontroller->ifend(); i++) {

				if (position.moveTimes < 0) {

					keybd_event('A', 0, 0, 0);
					keybd_event('A', 0, KEYEVENTF_KEYUP, 0);

				} else if (position.moveTimes > 0) {

					keybd_event('D', 0, 0, 0);
					keybd_event('D', 0, KEYEVENTF_KEYUP, 0);

				}

				Sleep(RobotRate);

			}

			keybd_event(' ', 0, 0, 0);
			keybd_event(' ', 0, KEYEVENTF_KEYUP, 0);
			Sleep(RobotRate);

		}

	}
}

void Robot::PSOCalculator() {

	auto Tcontroller = Controller::getTcontroller();
	status = 1;

	for (int i = 0; i< 50000; i++) {

		for (int j = 0; j < 25; j++) {

			a1 = calculate[j][0];
			a2 = calculate[j][1];
			a3 = calculate[j][2];
			a4 = calculate[j][3];
			a5 = calculate[j][4];
			a6 = calculate[j][5];
			timer = clock();
//			std::cout << calculate[j][0] << " " << calculate[j][1] << " " << calculate[j][2] << " " << calculate[j][3] << " " << calculate[j][4] << " " << calculate[j][5];
//			std::cout << std::endl;
			keybd_event('R', 0, 0, 0);
			keybd_event('R', 0, KEYEVENTF_KEYUP, 0);
			Sleep(50);
			play();
			timer = clock() - timer;
			gotoXY(0, 1 + j);
			std::cout << calculate[j][0] << " " << calculate[j][1] << " " << calculate[j][2] << " " << calculate[j][3] << " " << calculate[j][4] << " " << calculate[j][5] << " " << Tcontroller->getCounter() << " " << timer << " " << Tcontroller->getPoint() << " i: " << i << " j: " << j;
			std::cout << std::endl;
			if (Tcontroller->getCounter() > calbest[j][6]) {
				calbest[j][0] = a1;
				calbest[j][1] = a2;
				calbest[j][2] = a3;
				calbest[j][3] = a4;
				calbest[j][4] = a5;
				calbest[j][5] = a6;
				calbest[j][6] = Tcontroller->getCounter();
				calbest[j][7] = timer;
			} else if (Tcontroller->getCounter() == calbest[j][6]) {
				if (timer > calbest[j][7]) {
					calbest[j][0] = a1;
					calbest[j][1] = a2;
					calbest[j][2] = a3;
					calbest[j][3] = a4;
					calbest[j][4] = a5;
					calbest[j][5] = a6;
					calbest[j][6] = Tcontroller->getCounter();
					calbest[j][7] = timer;
				}
			}

			if (Tcontroller->getCounter() > globalbest[6]) {
				globalbest[0] = a1;
				globalbest[1] = a2;
				globalbest[2] = a3;
				globalbest[3] = a4;
				globalbest[4] = a5;
				globalbest[5] = a6;
				globalbest[6] = Tcontroller->getCounter();
				globalbest[7] = timer;
				globalbest[8] = Tcontroller->getPoint();
				gotoXY(0, 0);
				std::cout << globalbest[0] << " " << globalbest[1] << " " << globalbest[2] << " " << globalbest[3] << " " << globalbest[4] << " " << globalbest[5] << " " << globalbest[6] << " " << globalbest[7] << " " << globalbest[8] << " global best";
				std::cout << std::endl;
			} else if (Tcontroller->getCounter() == globalbest[6]) {
				if (timer > globalbest[7]) {
					globalbest[0] = a1;
					globalbest[1] = a2;
					globalbest[2] = a3;
					globalbest[3] = a4;
					globalbest[4] = a5;
					globalbest[5] = a6;
					globalbest[6] = Tcontroller->getCounter();
					globalbest[7] = timer;
					globalbest[8] = Tcontroller->getPoint();
					gotoXY(0, 0);
					std::cout << globalbest[0] << " " << globalbest[1] << " " << globalbest[2] << " " << globalbest[3] << " " << globalbest[4] << " " << globalbest[5] << " " << globalbest[6] << " " << globalbest[7] << " " << globalbest[8] << " global best";
					std::cout << std::endl;
				}
			}

		}

		Move();
	}
}

void Robot::Move() {

	srand((unsigned)time(NULL));

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 6; j++) {
			v[i][j] = v[i][j] + 2 * rand()/double(RAND_MAX) * (calbest[i][j] - calculate[i][j]) + 2 * rand()/double(RAND_MAX) * (globalbest[j] - calculate[i][j]);
			calculate[i][j] = calculate[i][j] + v[i][j];
		}
	}
}

void Robot::gotoXY(const int x, const int y) {

	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(hout, cd);

}

SimulatorModel Robot::getRecommandPos() {

	SimulatorModel bestMove = {0, 0, 0, 0, -10000000, 0, 0, 0, {0, 0, 0, {0, 0, 0, 0}, 0}};
	uint16_t backupPool[poolDeep + Wall];
	Model backupTetris;

	memcpy(backupPool, Gamepool, sizeof(uint16_t [poolDeep + Wall]));
	backupTetris = tetris;

	for (int i = 0; i < rotationTimes[tetris.type]; i++) {

		if (i > 0 && !(transform()))
			break;

		for (int j = 0; j < 16; j++) {

			SimulatorModel sResult = Simulator(i, j, backupTetris.x);

			if (sResult.tetris.x == -1) {

				if (tetris.x < backupTetris.x) {

					j = tetris.x - 1;
					continue;

				} else
					break;

			}

			if (sResult.evaluation > bestMove.evaluation)
				bestMove = sResult;
			else if (sResult.evaluation == bestMove.evaluation) {

				if (sResult.priority > bestMove.priority)
					bestMove = sResult;

			}

			memcpy(Gamepool, backupPool, sizeof(uint16_t [poolDeep + Wall]));
			tetris.y = backupTetris.y;
		}

		tetris.x = backupTetris.x;

	}

	return bestMove;
}

void Robot::setGamepool(uint16_t const* pool) {

	memcpy(Gamepool, pool, sizeof(uint16_t [poolDeep + Wall]));
	removeTetris();

}

int Robot::getLandingHeight() {

	int height = tetris.y;

	for (int i = 3; i >= 0; i--) {

		if (getTetris() >> (i * 4) == 0)
			height++;
		else
			break;

	}

	return poolDeep - height;
}

int Robot::getErodedPieceCellsMetric() {

	int EPCM = 0;
	int y = tetris.y;
	int erodedRow = 0;

	for (;(y < poolDeep) && y < tetris.y + 4; y++) {

		if (Gamepool[y] == 0xffff) {

			for (int j = 0; j < 4; j++)
				if (((getTetris() >> ((3 - (tetris.y - y)) * 4)) >> j) & 1)
					EPCM++;

			memmove(Gamepool + 1, Gamepool, sizeof(uint16_t) * y);
			erodedRow++;

		}
	}

	return EPCM * erodedRow;

}

int Robot::getRowsTransitions() {

	int rTrans = 0;

	for (int i = 4; i < poolDeep; i++) {

		if (Gamepool[i] > 0xc003) {

			int row = Gamepool[i] >> 2;
			int mark = row & 0x0001;
			for (int j = 0; j < 11; j++) {

				row = row >> 1;
				if (mark != (row & 0x0001))
					rTrans++;
				mark = row & 0x0001;

			}
		}
	}

	return rTrans;
}

int Robot::getSumColTransHoleWell() {

	int hMark = 0, Welldeep = 0, last = -1;
	int holes = 0, cTrans = 0, WellsSum = 0;

	for (int i = 2; i < 14; i++) {

		hMark = Welldeep = 0;
		last = -1;

		for (int j = poolDeep - 1; j > 3; j--) {

			if (((Gamepool[j] >> i) & 0x0001) != last) {

				if (last != -1)
					cTrans++;

				last = (Gamepool[j] >> i) & 0x0001;

				if (Welldeep > 0 || hMark > 0) {

					holes = holes + Welldeep + hMark;
					hMark = Welldeep = 0;

				} else if (!last){

					if ((Gamepool[j] >> (i + 1) & 0x0001) && (Gamepool[j] >> (i - 1) & 0x0001))
						Welldeep = 1;
					else
						hMark = 1;

				}

			} else {

				last = (Gamepool[j] >> i) & 0x0001;
				if (!last) {

					if ((Gamepool[j] >> (i + 1) & 0x0001) && (Gamepool[j] >> (i - 1) & 0x0001))
						Welldeep++;
					else
						hMark++;

				}

			}

		}

		if (Welldeep > 0)
			for (int z = 1; z <= Welldeep; z++)
				WellsSum = WellsSum + z;

	}

	return a4 * cTrans + a5 * holes +  a6 * WellsSum;

}


bool Robot::moveLeft() {

	int backupX = tetris.x;

	tetris.x = tetris.x + 1;

	if (!checkCollision())
		return 1;
	else {

		tetris.x = backupX;
		return 0;

	}

}

bool Robot::moveRight() {

	int backupX = tetris.x;

	tetris.x = tetris.x - 1;

	if (!checkCollision())
		return 1;
	else {

		tetris.x = backupX;
		return 0;

	}

}

void Robot::fall() {

	Model backup;

	do {
		backup = tetris;
		tetris.y = tetris.y + 1;
	} while (!checkCollision());

	tetris = backup;
	insertTetris();

}

bool Robot::transform() {

	Model backup = tetris;

	tetris.orientation = tetris.orientation + 1;
	if (tetris.orientation > 3)
		tetris.orientation = 0;

	if (!checkCollision())
		return 1;
	else {

		tetris = backup;
		return 0;

	}
}

bool Robot::checkCollision() {

	int y = tetris.y;
	int x = tetris.x;

	auto Tetris = getTetris();

	for (int i = 0; i < 4; i++) {

		if (Gamepool[y + i] & (((Tetris >> ((3 - i) * 4)) & 0x000f) << (x - 3))) {
			return 1;
		}

	}

	return 0;
}

void Robot::insertTetris() {

	int y = tetris.y;
	int x = tetris.x;
	auto Tetris = getTetris();

	Gamepool[y] |= ((Tetris >> 12) & 0x000f) << (x - 3);
	Gamepool[y + 1] |= ((Tetris >> 8) & 0x000f) << (x - 3);
	Gamepool[y + 2] |= ((Tetris >> 4) & 0x000f) << (x - 3);
	Gamepool[y + 3] |= (Tetris & 0x000f) << (x - 3);
}

void Robot::removeTetris() {

	int y = tetris.y;
	int x = tetris.x;
	auto Tetris = getTetris();

	Gamepool[y] &= ~(((Tetris >> 12) & 0x000f) << (x - 3));
	Gamepool[y + 1] &= ~(((Tetris >> 8) & 0x000f) << (x - 3)) ;
	Gamepool[y + 2] &= ~(((Tetris >> 4) & 0x000f) << (x - 3)) ;
	Gamepool[y + 3] &= ~((Tetris & 0x000f) << (x - 3)) ;

}

uint16_t Robot::getTetris() {
	return Tetrisshape[tetris.type][tetris.orientation];
}

SimulatorModel Robot::Simulator(int rotate, int x, int originalX) {

	SimulatorModel result;
	result.tetris.x = -1;

	while (tetris.x != x) {

		if (x - tetris.x > 0) {

			if (!(moveLeft()))
				return result;

		} else if (x - tetris.x < 0) {

			if (!(moveRight()))
				return result;

		}

	}

	fall();
	int LH = getLandingHeight();
	int EPCM = getErodedPieceCellsMetric();
	int rTrans = getRowsTransitions();
	int SumCHW = getSumColTransHoleWell();

	result.evaluation = a1 * LH + a2 * EPCM + a3 * rTrans + SumCHW;

	result.EPCM = EPCM;
	result.LH = LH;
	result.rTrans = rTrans;
	result.SumCHW = SumCHW;
	result.rotateTimes = rotate;

	int move = originalX - tetris.x;

	result.moveTimes = move;

	if (move > 0)
		result.priority = 100 * move + rotate;
	else
		result.priority = rotate + 10 - 100 * move;

	result.tetris = tetris;

	return result;

}

std::shared_ptr<Robot> Robot::robot = NULL;

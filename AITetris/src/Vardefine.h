/*
 * Vardefine.h
 *
 *  Created on: 2018Äê1ÔÂ10ÈÕ
 *      Author: SKJ.Guan
 */

#include <stdint.h>
#include <iostream>

using std::string;

#ifndef VARDEFINE_H_
#define VARDEFINE_H_

static const int poolDeep = 26;

static const int poolWidth = 12;

static const int Wall = 2;

static const uint16_t Tetrisshape[7][4] =  //clockwise
{
		{0x2222, 0x0f00, 0x2222, 0x0f00}, //I
		{0x0720, 0x2620, 0x2700, 0x2320}, //T
		{0x2230, 0x0740, 0x6220, 0x1700}, //L
		{0x2260, 0x4700, 0x3220, 0x0710}, //J
		{0x0630, 0x2640, 0x0630, 0x2640}, //Z
		{0x0360, 0x4620, 0x0360, 0x4620}, //S
		{0x0660, 0x0660, 0x0660, 0x0660}, //O
};

static const uint16_t Originalgamepool[poolDeep + Wall] =
{
		0xc003, 0xc003, 0xc003, 0xc003, //hide
		0xc003, 0xc003, 0xc003, 0xc003,
		0xc003, 0xc003, 0xc003, 0xc003,
		0xc003, 0xc003, 0xc003, 0xc003,
		0xc003, 0xc003, 0xc003, 0xc003,
		0xc003, 0xc003, 0xc003, 0xc003,
		0xc003, 0xc003, 0xffff, 0xffff,
};

static const int rotationTimes[7] = {2, 4, 4, 4, 2, 2, 1}; // times the tetris can rotate

struct Model {
	int x;
	int y;
	int orientation;
	int coordinate[4];
	int type;
};

struct SimulatorModel {
	int EPCM;
	int LH;
	int rTrans;
	int SumCHW;
	int evaluation;
	int priority;
	int rotateTimes;
	int moveTimes;
	Model tetris;
};

static const int windowWidth = 38;

static const int windowLength = 30;

static const string menu[windowLength] = {
		"©³©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©·©³©¥©¥©¥©¥©¥©¥©¥©¥©¥©·",
		"©§                         ©§©§         ©§",
		"©§                         ©§©§         ©§",
		"©§                         ©§©§         ©§",
		"©§                         ©§©§         ©§",
		"©§                         ©§©»©¥©¥©¥©¥©¥©¥©¥©¥©¥©¿",
		"©§                         ©§©³©¥©¥©¥©¥©¥©¥©¥©¥©¥©·",
		"©§                         ©§©§MoveLeft ©§",
		"©§                         ©§©§  D or ¡û©§",
		"©§                         ©§©§MoveRight©§",
		"©§                         ©§©§  R or ¡ú©§",
		"©§                         ©§©§MoveDown ©§",
		"©§                         ©§©§  S or ¡ý©§",
		"©§                         ©§©§Rotate   ©§",
		"©§                         ©§©§  W or ¡ü©§",
		"©§                         ©§©§DropDown ©§",
		"©§                         ©§©§  Space  ©§",
		"©§                         ©§©§AutoPlay ©§",
		"©§                         ©§©§  V      ©§",
		"©§                         ©§©»©¥©¥©¥©¥©¥©¥©¥©¥©¥©¿",
		"©§                         ©§©³©¥©¥©¥©¥©¥©¥©¥©¥©¥©·",
		"©§                         ©§©§ Point   ©§",
		"©§                         ©§©§ 0       ©§",
		"©»©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¿©§ Counter ©§",
		"©³©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©·©§ 0       ©§",
		"©§                         ©§©§ Level   ©§",
		"©§                         ©§©§ 1       ©§",
		"©»©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¿©»©¥©¥©¥©¥©¥©¥©¥©¥©¥©¿"
};

static const int poolStartX = 2;

static const int poolStartY = 1;

static const int showStartX = 28;

static const int showStartY = 1;

static const string iTetrispattern = "¡ö"; //use for inserting Tetris

static const string rTetrispattern = "  "; //use for removing Tetris

static const int showInfoX = 29;

static const int showLevelY = 26;

static const int showPointY = 22;

static const int showCounterY = 24;

static const int showGameOverX = 9;

static const int showGameOverY = 25;

static const int ValueToLevelUp = 10; //the threshold value to level up

static const int RobotRate = 1000;

#endif /* VARDEFINE_H_ */

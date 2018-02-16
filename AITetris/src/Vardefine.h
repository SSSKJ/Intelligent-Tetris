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
		{0x00f0, 0x4444, 0x00f0, 0x4444}, //I
		{0x0720, 0x2620, 0x2700, 0x2320}, //T
		{0x2230, 0x0170, 0x6220, 0x0f40}, //L
		{0x2260, 0x0710, 0x3220, 0x4700}, //J
		{0x0630, 0x2640, 0x0630, 0x2640}, //Z
		{0x0360, 0x2310, 0x0360, 0x2310}, //S
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

struct Model {
	int x;
	int y;
	int orientation;
	int coordinate[4];
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
		"©§                         ©§©§DropDown ©§",
		"©§                         ©§©§  S or ¡ý©§",
		"©§                         ©§©§Rotate   ©§",
		"©§                         ©§©§  Space  ©§",
		"©§                         ©§©§Restart  ©§",
		"©§                         ©§©§  R      ©§",
		"©§                         ©§©§AutoPlay ©§",
		"©§                         ©§©§  V      ©§",
		"©§                         ©§©»©¥©¥©¥©¥©¥©¥©¥©¥©¥©¿",
		"©§                         ©§©³©¥©¥©¥©¥©¥©¥©¥©¥©¥©·",
		"©§                         ©§©§ Score   ©§",
		"©§                         ©§©§ 0       ©§",
		"©§                         ©§©§ Erased  ©§",
		"©§                         ©§©§ 0       ©§",
		"©§                         ©§©§ Level   ©§",
		"©§                         ©§©§ 1       ©§",
		"©»©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¿©»©¥©¥©¥©¥©¥©¥©¥©¥©¥©¿"
};

static const int poolStartX = 2;

static const int poolStartY = 2;

static const int showStartX = 37;

static const int showStartY = 1;

static const string iTetrispattern = "¡ö"; //use for inserting Tetris

static const string rTetrispattern = "  "; //use for removing Tetris


#endif /* VARDEFINE_H_ */

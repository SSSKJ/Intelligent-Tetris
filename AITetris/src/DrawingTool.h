/*
 * Window.h
 *
 *  Created on: 2018Äê1ÔÂ14ÈÕ
 *      Author: SKJ.Guan
 */

#include "Vardefine.h"
#include <windows.h>
#include <iostream>
#include <memory>

#ifndef DRAWINGTOOL_H_
#define DRAWINGTOOL_H_

class DrawingTool {

	public:
		virtual ~DrawingTool();
		static std::shared_ptr<DrawingTool> getTool();
		void DrawTheMenu();
		void handleCurrentTetris(const std::string);
		void handleTetris(const Model, const std::string);
		void reprint(int y);
		void printNextTetris(const uint16_t, const int);
		void updateInfo(const int);
		void gameOver();
		void printtest(int ,int, int);

	private:
		DrawingTool();
		HANDLE hout;
		void gotoXY(const int, const int);
		static std::shared_ptr<DrawingTool> tool;

};

#endif /* WINDOW_H_ */

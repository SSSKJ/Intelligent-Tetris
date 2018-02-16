/*
 * Window.h
 *
 *  Created on: 2018Äê1ÔÂ14ÈÕ
 *      Author: SKJ.Guan
 */

#include <memory>
#include <windows.h>
#include "Vardefine.h"

#ifndef DRAWINGTOOL_H_
#define DRAWINGTOOL_H_

class DrawingTool {

	public:
		virtual ~DrawingTool();
		static std::shared_ptr<DrawingTool> getTool();
		void DrawTheMenu();
		void handleCurrentTetris(const string);
		void handleTetris(const Model, const string);
		void reprint(int y);
		void printNextTetris();
		void printtest();

	private:
		DrawingTool();
		HANDLE hout;
		void gotoXY(int, int);
		static std::shared_ptr<DrawingTool> tool;

};

#endif /* WINDOW_H_ */

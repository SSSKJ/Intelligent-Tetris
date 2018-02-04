/*
 * Controller.h
 *
 *  Created on: 2018Äê1ÔÂ11ÈÕ
 *      Author: SKJ.Guan
 */

#include <memory>
#include <time.h>
#include "Vardefine.h"

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

class Controller {
	public:

		static std::shared_ptr<Controller> getTcontroller();
		virtual ~Controller();
		void init(); //print the menu
		void runGame();
		void autoRun(); //AI

	private:

		Controller();
		void KeyBoardHandler();
		void autoMove(clock_t&, clock_t&);
		void removeTetris();
		void insertTetris();
		void moveDown();
		void moveLeft();
		void moveRight();
		void fall();
		void transform();
		void checkerasing();
		void checkend();
		void restart();
		bool checkcollision();
		bool end;
		int level;
		int point;
		int counter;
		uint16_t Gamepool[poolDeep + Wall];
		static std::shared_ptr<Controller> Tcontroller;
		Model recorder;

};

#endif /* CONTROLLER_H_ */

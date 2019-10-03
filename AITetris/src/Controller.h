/*
 * Controller.h
 *
 *  Created on: 2018Äê1ÔÂ11ÈÕ
 *      Author: SKJ.Guan
 */

#include "Vardefine.h"
#include "Robot.h"
#include <iostream>
#include <memory>
#include <time.h>

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

class Controller {

	public:

		static std::shared_ptr<Controller> getTcontroller();
		virtual ~Controller();
		void init(); //print the menu
		void runGame();
		uint16_t* getGamepool();
		int getLevel();
		int getPoint();
		int getCounter();
		bool ifend();

	private:

		Controller();
		void KeyBoardHandler();
		void autoMove(clock_t&, clock_t&); // move down automatically
		void removeTetris(); // remove Tetris from Gamepool
		void insertTetris(); // insert Tetris into Gamepool
		void moveDown();
		void moveLeft();
		void moveRight();
		void fall();
		void transform();
		void checkerasing();
		void checkend(); // check whether the game is end
		void restart();
		bool checkcollision();
		void autoRun(); //AI
		void InputHandler(const char);
		bool end;
		int level;
		int point;
		int counter;
		uint16_t Gamepool[poolDeep + Wall];
		static std::shared_ptr<Controller> Tcontroller;
		Model recorder;

};

#endif /* CONTROLLER_H_ */

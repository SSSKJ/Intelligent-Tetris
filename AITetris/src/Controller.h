/*
 * Controller.h
 *
 *  Created on: 2018Äê1ÔÂ11ÈÕ
 *      Author: SKJ.Guan
 */

#include <memory>

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

class Controller {
	public:

		static std::unique_ptr<Controller> getTcontroller();
		virtual ~Controller();
		void init(); //print the menu
		void runGame();
		void autoRun(); //AI

	private:

		Controller();
		void moveDown();
		void moveLeft();
		void moveRight();
		void fall();
		void transform();
		bool checkcollision();
		void KeyBoardHandler();
		void insertTetris();
		static std::unique_ptr<Controller> Tcontroller;

};

#endif /* CONTROLLER_H_ */

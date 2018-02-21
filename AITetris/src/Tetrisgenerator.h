/*
 * Tetris.h
 *
 *  Created on: 2018Äê1ÔÂ10ÈÕ
 *      Author: SKJ.Guan
 */

#include <stdint.h>
#include <memory>
#include "Vardefine.h"

#ifndef TETRISGENERATOR_H_
#define TETRISGENERATOR_H_

class Tetrisgenerator {

	public:

		static std::shared_ptr<Tetrisgenerator> getTgenerator(); //singleton mode
		virtual ~Tetrisgenerator();
		void generateTetris(); // generate the next Tetris and set up the x and y of the current Tetris
		int getX();
		bool setX(int);
		int getY();
		bool setY(int);
		void CWRotate();
		void antiCWRotate();
		int* getCoordinate();
		void getStatus(Model&);
		void reset(Model);
		uint16_t getTetris();
		uint16_t getNextTetris();

	private:

		Tetrisgenerator();
		void nextTetris();  // generate the next Tetris
		void recordCoordinate();  //record 4 relative coordinates of the Tetris
		static std::shared_ptr<Tetrisgenerator> Tgenerator;
		int x, y; //top left cornor
		int type[2]; //save the type of current Tetris and the next Tetris
		int orientation[2]; // save the orientation of current Tetris and the next Tetris
		int coordinate[4];
};

#endif /* TETRIS_H_ */

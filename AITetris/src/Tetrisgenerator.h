/*
 * Tetris.h
 *
 *  Created on: 2018Äê1ÔÂ10ÈÕ
 *      Author: SKJ.Guan
 */

#include <stdint.h>
#include <memory>

#ifndef TETRISGENERATOR_H_
#define TETRISGENERATOR_H_

class Tetrisgenerator {

	public:

		static std::unique_ptr<Tetrisgenerator> getTgenerator(); //singleton mode
		virtual ~Tetrisgenerator();
		void generateTetris(); // generate the next Tetris and set up the x and y of the current Tetris

	private:

		Tetrisgenerator();
		void nextTetris();  // generate the next Tetris
		static std::unique_ptr<Tetrisgenerator> Tgenerator;
		int8_t x, y;
		int type[2]; //save the type of current Tetris and the next Tetris
		int orientation[2]; // save the orientation of current Tetris and the next Tetris
};

#endif /* TETRIS_H_ */

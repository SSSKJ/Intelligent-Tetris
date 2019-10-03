/*
 * Robot.h
 *
 *  Created on: 2018Äê3ÔÂ25ÈÕ
 *      Author: SKJ.Guan
 */
#include "Vardefine.h"
#include <memory>
#include <iostream>

#ifndef ROBOT_H_
#define ROBOT_H_

class Robot {
	public:

		static std::shared_ptr<Robot> getRobot();
		bool getStatus();
		void setStatus(bool);
		void autoplay();
		void PSOCalculator();
		void play();
		virtual ~Robot();

	private:

		Robot();
		SimulatorModel getRecommandPos();
		void setGamepool(uint16_t const*);
		int getLandingHeight();
		int getErodedPieceCellsMetric();
		int getRowsTransitions();
		int getSumColTransHoleWell(); //sum of Column transition, number of holes and wells
		bool moveLeft();
		bool moveRight();
		void fall();
		bool transform();
		bool checkCollision();
		void insertTetris();
		void removeTetris();
		uint16_t getTetris();
		SimulatorModel Simulator(int, int, int);
		static std::shared_ptr<Robot> robot;
		bool status; // record whether the auto function is on
		Model tetris;
		uint16_t Gamepool[poolDeep + Wall];
		void gotoXY(const int, const int);
		void Move();
		float a1, a2, a3, a4, a5, a6; // for LH, EPCM, rTrans, cTrans, hole, wells
		float calculate[25][6];
		float calbest[25][8]; //for cal best a1, a2, a3, a4, a5, a6, score, time
		float globalbest[9]; //for globalbest a1, a2, a3, a4, a5, a6, counter, time,  score
		float v[25][6]; // for velocities
		float timer;
		float maxV; //max of velocity
		float minV; //min of velocity

};

#endif /* ROBOT_H_ */

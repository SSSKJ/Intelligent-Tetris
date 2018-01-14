/*
 * Window.h
 *
 *  Created on: 2018Äê1ÔÂ14ÈÕ
 *      Author: SKJ.Guan
 */

#include <memory>

#ifndef WINDOW_H_
#define WINDOW_H_

class Window {

	public:
		virtual ~Window();
		static std::unique_ptr<Window> getWindow();

	private:
		Window();
		static std::unique_ptr<Window> window;

};

#endif /* WINDOW_H_ */

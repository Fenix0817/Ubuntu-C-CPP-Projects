/*
 * Application.h
 *
 *  Created on: Nov 18, 2018
 *      Author: jack
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <gtkhpp/gtk.hpp>

#include "OpenDialog.h"

class Application {
public:
	Application();
	virtual ~Application();

	OpenDialog*od;
};

#endif /* APPLICATION_H_ */

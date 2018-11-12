/*
 * Window.h
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include "gtk_include.h"
#include "Container.h"

namespace gui {

class Window : public Container {
public:
	Window();
	virtual ~Window();

	void create(GtkWindowType type);
	void setPosition(GtkWindowPosition pos);
	void setSize(int w,int h);
	void setTitle(const char*title);

	void enableQuitOnExit();

	int getWidth();
	int getHeight();
};

} /* namespace gui */

#endif /* WINDOW_H_ */

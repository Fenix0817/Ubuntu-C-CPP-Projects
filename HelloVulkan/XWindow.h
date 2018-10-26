/*
 * XWindow.h
 *
 *  Created on: Oct 23, 2018
 *      Author: jack
 */

#ifndef XWINDOW_H_
#define XWINDOW_H_

#include <stdlib.h>
#include <xcb/xcb.h>
#include <stdio.h>
#include <string.h>

class XWindow {
public:
	XWindow();
	virtual ~XWindow();

	xcb_connection_t*connection;
	xcb_screen_t*screen;
	uint32_t window;

	xcb_atom_t wmDeleteWin;
	xcb_atom_t wmProtocols;

	xcb_generic_event_t* event;
	xcb_client_message_event_t* clientEvent;

	bool running;

	void beginSetup();
	void endSetup();

	void createWindow(int w,int h);
	void setTitle(const char*appName);

	void addExitHandler();

	bool isLoopRunning();

	void beginLoop();
	void beginLoopIteration();
	void endLoopIteration();
	void endLoop();

};

#endif /* XWINDOW_H_ */

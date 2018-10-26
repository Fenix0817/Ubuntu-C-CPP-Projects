/*
 * XWindow.cpp
 *
 *  Created on: Oct 23, 2018
 *      Author: jack
 */

#include "XWindow.h"

XWindow::XWindow() {
	// TODO Auto-generated constructor stub

}

XWindow::~XWindow() {
	// TODO Auto-generated destructor stub
}


void XWindow::beginSetup(){
	int screenp=0;
	connection = xcb_connect(NULL,&screenp);

	if(xcb_connection_has_error(connection)){
		printf("Failed to connect to X server using XCB\n");
		exit(EXIT_FAILURE);
	}

	xcb_screen_iterator_t screenIterator = xcb_setup_roots_iterator(xcb_get_setup(connection));

	for(int i=0;i<screenp;i++){
		xcb_screen_next(&screenIterator);
	}

	screen = screenIterator.data;

	window = xcb_generate_id(connection);
}
void XWindow::endSetup(){
	xcb_map_window(connection,window);
	xcb_flush(connection);
}

void XWindow::createWindow(int w,int h){
	uint32_t eventMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;


	uint32_t valueList[] = {screen->black_pixel,0};

	xcb_create_window(connection,
					  XCB_COPY_FROM_PARENT,
					  window,
					  screen->root,
					  0,
					  0,
					  w,
					  h,
					  0,
					  XCB_WINDOW_CLASS_INPUT_OUTPUT,
					  screen->root_visual,
					  eventMask,
					  valueList);
}
void XWindow::setTitle(const char*appName){
	xcb_change_property(connection,
						XCB_PROP_MODE_REPLACE,
						window,
						XCB_ATOM_WM_NAME,
						XCB_ATOM_STRING,
						8,
						strlen(appName),
						appName);
}

void XWindow::addExitHandler(){
	xcb_intern_atom_cookie_t wmDeleteCookie = xcb_intern_atom(connection,0,strlen("WM_DELETE_WINDOW"),"WM_DELETE_WINDOW");
	xcb_intern_atom_cookie_t wmProtocolsCookie = xcb_intern_atom(connection,0,strlen("WM_PROTOCOLS"),"WM_PROTOCOLS");
	xcb_intern_atom_reply_t* wmDeleteReply = xcb_intern_atom_reply(connection,wmDeleteCookie,NULL);
	xcb_intern_atom_reply_t* wmProtocolsReply = xcb_intern_atom_reply(connection,wmProtocolsCookie,NULL);

	wmDeleteWin = wmDeleteReply->atom;
	wmProtocols = wmProtocolsReply->atom;
}

bool XWindow::isLoopRunning(){
	return running;
}

void XWindow::beginLoop(){
	running=true;
}
void XWindow::beginLoopIteration(){
	event=xcb_wait_for_event(connection);
}
void XWindow::endLoopIteration(){
	switch(event->response_type & ~0x80){
	case XCB_CLIENT_MESSAGE:
		clientEvent = (xcb_client_message_event_t*) event;
		if(clientEvent->data.data32[0] == wmDeleteWin){
			running=false;
		}
		break;
	}
}
void XWindow::endLoop(){
	xcb_destroy_window(connection,window);
}


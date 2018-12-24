/*
 * OpenDialog.h
 *
 *  Created on: Nov 18, 2018
 *      Author: jack
 */

#ifndef OPENDIALOG_H_
#define OPENDIALOG_H_

#include <gtkhpp/gtk.hpp>

void OpenDialog_onOpen(GtkButton*btn,gpointer userData);
void OpenDialog_onClose(GtkButton*btn,gpointer userData);

typedef void (*OpenDialog_callback)(std::string);

class OpenDialog {
public:
	OpenDialog();
	virtual ~OpenDialog();

	gtk::Window*window;
	gtk::xml::UI*ui;

	gtk::Entry*text;
	gtk::Button*open;
	gtk::Button*close;

	OpenDialog_callback callback;

	void init();
	void show();
	void destroy();
	inline void setCallback(OpenDialog_callback c){callback=c;}
};

#endif /* OPENDIALOG_H_ */

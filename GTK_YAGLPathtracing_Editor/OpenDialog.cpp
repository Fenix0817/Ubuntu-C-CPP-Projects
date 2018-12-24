/*
 * OpenDialog.cpp
 *
 *  Created on: Nov 18, 2018
 *      Author: jack
 */

#include "OpenDialog.h"

OpenDialog::OpenDialog() {
	// TODO Auto-generated constructor stub

}

OpenDialog::~OpenDialog() {
	// TODO Auto-generated destructor stub
}

void OpenDialog_onOpen(GtkButton*btn,gpointer userData){
	OpenDialog*od=static_cast<OpenDialog*>(userData);
	od->callback(od->text->getText());
}
void OpenDialog_onClose(GtkButton*btn,gpointer userData){
	OpenDialog*od=static_cast<OpenDialog*>(userData);
	printf("Close.\n");
	od->destroy();
}

void OpenDialog::init(){
	window=new gtk::Window();
	window->create(GTK_WINDOW_TOPLEVEL);
	window->setPosition(GTK_WIN_POS_CENTER);
	window->setSize(0,0);
	window->setTitle("Open XML file");

	ui=new gtk::xml::UI();
	ui->loadUI("open-dialog.xml","open-dialog");

	text=gtk::entry(ui->findWidgetWithName("text-field",true));
	open=gtk::button(ui->findWidgetWithName("open",true));
	close=gtk::button(ui->findWidgetWithName("close",true));

	open->addClickListener(OpenDialog_onOpen,this);
	close->addClickListener(OpenDialog_onClose,this);

	window->add(ui);
}

void OpenDialog::show(){
	window->showAll();
	window->enableQuitOnExit();
}

void OpenDialog::destroy(){
	window->destroy();
}

/*
 * main.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#include <gtkhpp/gtk.hpp>

void click(GtkButton*w,gpointer userData){
	printf("Clicked\n");
}

void otherClick(GtkButton*w,gpointer userData){
	printf("Other clicked\n");
}

int main(int argc, char *argv[]) {

	gtk::init(argc,argv);

	//TODO: Fully implement GTK object heirarchy, with boxes and bins and stuff
	//TODO: This should be a full translation, not just a select library
	gtk::Window*window=new gtk::Window();
	window->create(GTK_WINDOW_TOPLEVEL);
	window->setPosition(GTK_WIN_POS_CENTER);
	window->setSize(500,500);
	window->setTitle("Hello GTK");

	gtk::xml::UI*ui=new gtk::xml::UI();
	ui->loadUI("ui.xml","my_ui");
	gtk::button(ui->findWidgetWithName("clickableButton"))->addClickListener(click,(gpointer)nullptr);
	window->add(ui);

//	gtk::Button*btn=new gtk::Button();
//	btn->create();
//	btn->addLabel("Hi");
//	btn->addClickListener(click,(gpointer)nullptr);
//	btn->addClickListener(otherClick,(gpointer)nullptr);
//	window->add(btn);

	window->enableQuitOnExit();

	window->showAll();

	gtk::startMain();


	return 0;
}


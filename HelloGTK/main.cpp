/*
 * main.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#include <gtkhpp/gtk.hpp>

int main(int argc, char *argv[]) {

	gtk::init(argc,argv);

	gtk::Window*window=new gtk::Window();
	window->create(GTK_WINDOW_TOPLEVEL);
	window->setPosition(GTK_WIN_POS_CENTER);
	window->setSize(500,500);
	window->setTitle("Hello GTK");

	gtk::Box*box=new gtk::Box();
	box->create(GTK_ORIENTATION_VERTICAL,100);

	gtk::Label*label=new gtk::Label();
	label->create();
	label->setText("Label");
	box->add(label);

	gtk::ButtonBox*btnBox=new gtk::ButtonBox();
	btnBox->create(GTK_ORIENTATION_VERTICAL);
	gtk::Button*btn=new gtk::Button();
	btn->create();
	btn->addLabel("Button");
	btnBox->add(btn);
	box->add(btnBox);

//	window->add(box);

	gtk::xml::UI*ui=new gtk::xml::UI();
	ui->loadUI("ui.xml","my_ui");
	window->add(ui);

	window->enableQuitOnExit();

	window->showAll();

	gtk::startMain();


	return 0;
}


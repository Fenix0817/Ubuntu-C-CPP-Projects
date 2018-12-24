/*
 * main.cpp
 *
 *  Created on: Nov 18, 2018
 *      Author: jack
 */

#include <gtkhpp/gtk.hpp>

gtk::Button*btn0;
gtk::Button*btn1;
gtk::Button*btn2;
gtk::Button*btn3;
gtk::Button*btn4;
gtk::Button*btn5;
gtk::Button*btn6;
gtk::Button*btn7;
gtk::Button*btn8;
gtk::Button*btn9;
gtk::Button*btnDot;

gtk::Label*lbl;
gtk::Entry*txt;

int main(int argc,char**argv){
	gtk::init(argc,argv);
	gtk::Window*window=new gtk::Window();
	window->create(GTK_WINDOW_TOPLEVEL);
	window->setSize(0,0);
	window->setTitle("GTK Calculator");

	gtk::xml::UI*ui=new gtk::xml::UI();
	ui->loadUI("ui.xml","calculator");
	window->add(ui);

	btn0=gtk::button(ui->findWidgetWithName("0"));
	btn1=gtk::button(ui->findWidgetWithName("1"));
	btn2=gtk::button(ui->findWidgetWithName("2"));
	btn3=gtk::button(ui->findWidgetWithName("3"));
	btn4=gtk::button(ui->findWidgetWithName("4"));
	btn5=gtk::button(ui->findWidgetWithName("5"));
	btn6=gtk::button(ui->findWidgetWithName("6"));
	btn7=gtk::button(ui->findWidgetWithName("7"));
	btn8=gtk::button(ui->findWidgetWithName("8"));
	btn9=gtk::button(ui->findWidgetWithName("9"));
	btnDot=gtk::button(ui->findWidgetWithName("."));

	lbl=gtk::label(ui->findWidgetWithName("lbl"));
	txt=gtk::entry(ui->findWidgetWithName("txt"));

	window->showAll();
	window->enableQuitOnExit();

	gtk::startMain();
}

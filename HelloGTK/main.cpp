/*
 * main.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#include <gui/gui.h>

int main(int argc, char *argv[]) {

//	gtk_init(&argc,&argv);
//
//	GtkWidget*window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
//	gtk_window_set_default_size(GTK_WINDOW(window),500,500);
//	gtk_window_set_title(GTK_WINDOW(window),"Hello GTK");

	gui::init(argc,argv);

	gui::Window window;
	window.create(GTK_WINDOW_TOPLEVEL);
	window.setPosition(GTK_WIN_POS_CENTER);
	window.setSize(500,500);
	window.setTitle("Hello GTK");

	GtkWidget*table=gtk_table_new(4,4,TRUE);
	gtk_table_set_row_spacings(GTK_TABLE(table),2);
	gtk_table_set_col_spacings(GTK_TABLE(table),2);

	for(int x=0;x<4;x++){
		for(int y=0;y<4;y++){
			GtkWidget*btn=gtk_button_new_with_label("Button");
			gtk_table_attach_defaults(GTK_TABLE(table),btn,x,x+1,y,y+1);
		}
	}

	gui::Widget tableWidget;
	tableWidget.widget=table;

//	gtk_container_add(GTK_CONTAINER(window.widget),table);
	window.add(tableWidget);


//	g_signal_connect(G_OBJECT(window.window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	window.enableQuitOnExit();

//	gtk_widget_show_all(window);
	window.showAll();

	gtk_main();


	return 0;
}


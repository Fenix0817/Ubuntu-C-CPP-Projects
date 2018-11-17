/*
 * Grid.cpp
 *
 *  Created on: Nov 14, 2018
 *      Author: jack
 */

#include "Grid.h"

namespace gtk {

Grid::Grid() {
	// TODO Auto-generated constructor stub

}

Grid::~Grid() {
	// TODO Auto-generated destructor stub
}

void Grid::create(){
	widget=gtk_grid_new();
}
void Grid::add(Widget*wi,int x,int y,int w,int h){
	gtk_grid_attach(GTK_GRID(widget),wi->widget,x,y,w,h);
}

} /* namespace gtk */

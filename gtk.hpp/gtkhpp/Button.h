/*
 * Button.h
 *
 *  Created on: Nov 13, 2018
 *      Author: jack
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Container.h"
#include "Label.h"

namespace gtk {

typedef void (*ButtonClickCallback)(GtkButton*button,gpointer userData);

class Button : public Container {
public:
	Button();
	virtual ~Button();

	void create();
	void addLabel(std::string s);
	void addClickListener(ButtonClickCallback callback,gpointer userData);
};

} /* namespace gtk */

#endif /* BUTTON_H_ */

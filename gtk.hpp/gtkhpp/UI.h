/*
 * UI.h
 *
 *  Created on: Nov 13, 2018
 *      Author: jack
 */

#ifndef UI_H_
#define UI_H_

#include "Container.h"
#include "Label.h"
#include "Box.h"
#include "Button.h"
#include "Grid.h"

namespace gtk {
namespace xml {

void addChildrenGrid(Grid*to,tinyxml2::XMLNode*node);
void addChildren(Container*to,tinyxml2::XMLNode*node);
Widget* createWidgetFromXML(tinyxml2::XMLNode*elem);

struct UIElement {
	std::string id;
	Widget*widget;
};

class UI : public Container {
public:
	UI();
	virtual ~UI();

	void loadUI(std::string fileName,std::string name);

	void parseNode(tinyxml2::XMLElement*node);
};

} /* namespace xml */
} /* namespace gtk */

#endif /* UI_H_ */

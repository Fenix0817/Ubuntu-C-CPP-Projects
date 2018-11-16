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

class UI;

void addChildrenGrid(Grid*to,tinyxml2::XMLNode*node,UI*ui);
void addChildren(Container*to,tinyxml2::XMLNode*node,UI*ui);
Widget* createWidgetFromXML(tinyxml2::XMLNode*elem,UI*ui);

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

	void addNamedElement(Widget*w,std::string n);

	Widget* findWidgetWithName(std::string n,bool failIfNotFound=true);

	std::vector<UIElement>elements;
};

} /* namespace xml */
} /* namespace gtk */

#endif /* UI_H_ */

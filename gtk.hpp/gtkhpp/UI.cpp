/*
 * UI.cpp
 *
 *  Created on: Nov 13, 2018
 *      Author: jack
 */

#include "UI.h"

namespace gtk {
namespace xml {

void addChildren(Container*to,tinyxml2::XMLNode*node){
	using namespace tinyxml2;
	printf("Adding children\n");
	XMLElement*elem=node->ToElement();
	XMLNode*n=elem->FirstChild();
	if(n==NULL)return;
	printf("First child gotten\n");
	elem=n->ToElement();
	while(elem!=NULL){
		printf("Elem\n");
		to->add(createWidgetFromXML(elem));
		printf("Elem added\n");
		XMLNode*newNode=elem->NextSibling();
		if(newNode==NULL)return;
		elem=newNode->ToElement();
		printf("Next sibling\n");
	}
}

void addChildrenGrid(Grid*to,tinyxml2::XMLNode*node){
	using namespace tinyxml2;
	printf("Adding children\n");
	XMLElement*elem=node->ToElement();
	XMLNode*n=elem->FirstChild();
	if(n==NULL)return;
	printf("First child gotten\n");
	elem=n->ToElement();
	while(elem!=NULL){
		printf("Elem\n");
		to->add(createWidgetFromXML(elem),elem->IntAttribute("gridx"),elem->IntAttribute("gridy"),elem->IntAttribute("gridw"),elem->IntAttribute("gridh"));
		printf("Elem added\n");
		XMLNode*newNode=elem->NextSibling();
		if(newNode==NULL)return;
		elem=newNode->ToElement();
		printf("Next sibling\n");
	}
}
Widget* createWidgetFromXML(tinyxml2::XMLNode*n){
	printf("Creating widget\n");
	using namespace tinyxml2;
	XMLElement*elem=n->ToElement();
	printf("%s\n",elem->Name());
	std::string elemName(elem->Name());
	if(elemName=="label"){
		printf("Label elem\n");
		Label*lbl=new Label();
		lbl->create();
		lbl->setText(std::string(elem->GetText()));
		printf("Done with label elem\n");
		return lbl;
	}
	if(elemName=="box"){
		std::string orientation(elem->Attribute("orientation"));
		int spacing(elem->IntAttribute("spacing"));
		GtkOrientation o=GTK_ORIENTATION_HORIZONTAL;
		if(orientation=="vertical")o=GTK_ORIENTATION_VERTICAL;
		else if(orientation=="horizontal")o=GTK_ORIENTATION_HORIZONTAL;
		else{
			printf("Cannot recognize orientation %s for box element.\n",orientation.c_str());
			exit(EXIT_FAILURE);
		}
		Box*bx=new Box();
		bx->create(o,spacing);
		printf("Adding children to box\n");
		addChildren(bx,n);
		printf("Children added\n");
		return bx;
	}
	if(elemName=="button"){
		Button*btn=new Button();
		btn->create();
		addChildren(btn,n);
		return btn;
	}
	if(elemName=="button-with-label"){
		Button*btn=new Button();
		btn->create();
		Label*lbl=new Label();
		lbl->create();
		lbl->setText(std::string(elem->GetText()));
		btn->add(lbl);
		return btn;
	}
	if(elemName=="grid"){
		Grid*grid=new Grid();
		grid->create();
		addChildrenGrid(grid,n);
		return grid;
	}
//	return NULL;
	return nullptr;
}

UI::UI() {
	// TODO Auto-generated constructor stub

}

UI::~UI() {
	// TODO Auto-generated destructor stub
}

void UI::loadUI(std::string fileName,std::string name){
	widget=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
	using namespace tinyxml2;
	XMLDocument doc;
	doc.LoadFile(fileName.c_str());

	XMLElement*root=doc.RootElement();

	XMLNode*elem=root->FirstChild();
	bool done=false;
	while(elem!=NULL&&!done){
		if(strcmp(elem->ToElement()->Name(),name.c_str())){
			printf("UI::loadUI --- Parsing element %s\n",elem->ToElement()->Name());
			parseNode(elem->ToElement());
			done=true;
		}
		elem=elem->NextSibling();
	}
}

void UI::parseNode(tinyxml2::XMLElement*node){
	using namespace tinyxml2;
	printf("Before creating widget\n");
	Widget*w=createWidgetFromXML(node->FirstChild());
	printf("Created widget\n");
	if(w!=NULL)add(w);
}

} /* namespace xml */
} /* namespace gtk */

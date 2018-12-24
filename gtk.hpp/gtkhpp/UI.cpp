/*
 * UI.cpp
 *
 *  Created on: Nov 13, 2018
 *      Author: jack
 */

#include "UI.h"

namespace gtk {
namespace xml {

void addChildren(Container*to,tinyxml2::XMLNode*node,UI*ui){
	using namespace tinyxml2;
	printf("Adding children\n");
	XMLElement*elem=node->ToElement();
	XMLNode*n=elem->FirstChild();
	if(n==NULL)return;
	printf("First child gotten\n");
	elem=n->ToElement();
	while(elem!=NULL){
		printf("Elem\n");
		Widget*w=createWidgetFromXML(elem,ui);
		to->add(w);
		if(elem->Attribute("name")!=0)ui->addNamedElement(w,std::string(elem->Attribute("name")));
		printf("Elem added\n");
		XMLNode*newNode=elem->NextSibling();
		if(newNode==NULL)return;
		elem=newNode->ToElement();
		printf("Next sibling\n");
	}
}

void addChildrenGrid(Grid*to,tinyxml2::XMLNode*node,UI*ui){
	using namespace tinyxml2;
	printf("Adding children\n");
	XMLElement*elem=node->ToElement();
	XMLNode*n=elem->FirstChild();
	if(n==NULL)return;
	printf("First child gotten\n");
	elem=n->ToElement();
	while(elem!=NULL){
		printf("Elem\n");
		Widget*w=createWidgetFromXML(elem,ui);
		to->add(w,elem->IntAttribute("gridx"),elem->IntAttribute("gridy"),elem->IntAttribute("gridw"),elem->IntAttribute("gridh"));
		if(elem->Attribute("name")!=0)ui->addNamedElement(w,std::string(elem->Attribute("name")));
		printf("Elem added\n");
		XMLNode*newNode=elem->NextSibling();
		if(newNode==NULL)return;
		elem=newNode->ToElement();
		printf("Next sibling\n");
	}
}

void addChildrenMenuBar(MenuBar*bar,tinyxml2::XMLNode*node,UI*ui){
	using namespace tinyxml2;
	XMLElement*elem=node->ToElement();
	XMLNode*n=elem->FirstChild();
	if(n==NULL)return;
	elem=n->ToElement();
	while(elem!=NULL){
		Widget*w=createWidgetFromXML(elem,ui);
		bar->addMenu(gtk::menu(w));
		if(elem->Attribute("name")!=0)ui->addNamedElement(w,std::string(elem->Attribute("name")));
		XMLNode*newNode=elem->NextSibling();
		if(newNode==NULL)return;
		elem=newNode->ToElement();
	}
}

Widget* createWidgetFromXML(tinyxml2::XMLNode*n,UI*ui){
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
		if(elem->Attribute("name")!=0)ui->addNamedElement(lbl,std::string(elem->Attribute("name")));
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
		if(elem->Attribute("name")!=0)ui->addNamedElement(bx,std::string(elem->Attribute("name")));
		addChildren(bx,n,ui);
		printf("Children added\n");
		return bx;
	}
	if(elemName=="button"){
		Button*btn=new Button();
		btn->create();
		addChildren(btn,n,ui);
		if(elem->Attribute("name")!=0)ui->addNamedElement(btn,std::string(elem->Attribute("name")));
		return btn;
	}
	if(elemName=="button-with-label"){
		Button*btn=new Button();
		btn->create();
		Label*lbl=new Label();
		lbl->create();
		lbl->setText(std::string(elem->GetText()));
		btn->add(lbl);
		if(elem->Attribute("name")!=0)ui->addNamedElement(btn,std::string(elem->Attribute("name")));
		return btn;
	}
	if(elemName=="grid"){
		Grid*grid=new Grid();
		grid->create();
		addChildrenGrid(grid,n,ui);
		if(elem->Attribute("name")!=0)ui->addNamedElement(grid,std::string(elem->Attribute("name")));
		return grid;
	}
	if(elemName=="entry"){
		Entry*entry=new Entry();
		entry->create();
		if(elem->Attribute("text")!=0)entry->setText(std::string(elem->Attribute("text")));
		if(elem->Attribute("name")!=0)ui->addNamedElement(entry,std::string(elem->Attribute("name")));
		return entry;
	}
	if(elemName=="menu-item"){
		MenuItem*item=new MenuItem();
		item->create();
		addChildren(item,n,ui);
		if(elem->Attribute("name")!=0)ui->addNamedElement(item,std::string(elem->Attribute("name")));
		return item;
	}
	if(elemName=="menu"){
		Menu*menu=new Menu();
		menu->create();
		if(elem->Attribute("name")!=0)ui->addNamedElement(menu,std::string(elem->Attribute("name")));
		return menu;
	}
	if(elemName=="menu-bar"){
		MenuBar*bar=new MenuBar();
		bar->create();
		addChildrenMenuBar(bar,n,ui);
		if(elem->Attribute("name")!=0)ui->addNamedElement(bar,std::string(elem->Attribute("name")));
		return bar;
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

void UI::addNamedElement(Widget*w,std::string n){
	UIElement uie;
	uie.id=n;
	uie.widget=w;
	elements.push_back(uie);
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

Widget* UI::findWidgetWithName(std::string n,bool failIfNotFound){
	for(UIElement uie:elements){
		if(uie.id==n)return uie.widget;
	}
	printf("Element with name %s not found. Exiting.\n",n.c_str());
	exit(EXIT_FAILURE);
}

void UI::parseNode(tinyxml2::XMLElement*node){
	using namespace tinyxml2;
	printf("Before creating widget\n");
	Widget*w=createWidgetFromXML(node->FirstChild(),this);
	printf("Created widget\n");
	if(w!=NULL)add(w);
}

} /* namespace xml */
} /* namespace gtk */

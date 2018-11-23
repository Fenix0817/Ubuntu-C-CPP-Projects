/*
 * TextAtlasMonospaced.cpp
 *
 *  Created on: Nov 22, 2018
 *      Author: jack
 */

#include "TextAtlasMonospaced.h"

TextAtlasMonospaced::TextAtlasMonospaced() {
	// TODO Auto-generated constructor stub

}

TextAtlasMonospaced::~TextAtlasMonospaced() {
	// TODO Auto-generated destructor stub
}

TextAtlasPos TextAtlasMonospaced::getPos(char c){
	int w=20;
	int h=6;
	if(c=='A')return TextAtlasPos(0,0, w,h);
	if(c=='B')return TextAtlasPos(1,0, w,h);
	if(c=='C')return TextAtlasPos(2,0, w,h);
	if(c=='D')return TextAtlasPos(3,0, w,h);
	if(c=='E')return TextAtlasPos(4,0, w,h);
	if(c=='F')return TextAtlasPos(5,0, w,h);
	if(c=='G')return TextAtlasPos(6,0, w,h);
	if(c=='H')return TextAtlasPos(7,0, w,h);
	if(c=='I')return TextAtlasPos(8,0, w,h);
	if(c=='J')return TextAtlasPos(9,0, w,h);
	if(c=='K')return TextAtlasPos(10,0, w,h);
	if(c=='L')return TextAtlasPos(11,0, w,h);
	if(c=='M')return TextAtlasPos(12,0, w,h);
	if(c=='N')return TextAtlasPos(13,0, w,h);
	if(c=='O')return TextAtlasPos(14,0, w,h);
	if(c=='P')return TextAtlasPos(15,0, w,h);
	if(c=='Q')return TextAtlasPos(16,0, w,h);
	if(c=='R')return TextAtlasPos(17,0, w,h);
	if(c=='S')return TextAtlasPos(18,0, w,h);
	if(c=='T')return TextAtlasPos(19,0, w,h);
	if(c=='U')return TextAtlasPos(0,1, w,h);
	if(c=='V')return TextAtlasPos(1,1, w,h);
	if(c=='W')return TextAtlasPos(2,1, w,h);
	if(c=='X')return TextAtlasPos(3,1, w,h);
	if(c=='Y')return TextAtlasPos(4,1, w,h);
	if(c=='Z')return TextAtlasPos(5,1, w,h);


	if(c=='a')return TextAtlasPos(0,2, w,h);
	if(c=='b')return TextAtlasPos(1,2, w,h);
	if(c=='c')return TextAtlasPos(2,2, w,h);
	if(c=='d')return TextAtlasPos(3,2, w,h);
	if(c=='e')return TextAtlasPos(4,2, w,h);
	if(c=='f')return TextAtlasPos(5,2, w,h);
	if(c=='g')return TextAtlasPos(6,2, w,h);
	if(c=='h')return TextAtlasPos(7,2, w,h);
	if(c=='i')return TextAtlasPos(8,2, w,h);
	if(c=='j')return TextAtlasPos(9,2, w,h);
	if(c=='k')return TextAtlasPos(10,2, w,h);
	if(c=='l')return TextAtlasPos(11,2, w,h);
	if(c=='m')return TextAtlasPos(12,2, w,h);
	if(c=='n')return TextAtlasPos(13,2, w,h);
	if(c=='o')return TextAtlasPos(14,2, w,h);
	if(c=='p')return TextAtlasPos(15,2, w,h);
	if(c=='q')return TextAtlasPos(16,2, w,h);
	if(c=='r')return TextAtlasPos(17,2, w,h);
	if(c=='s')return TextAtlasPos(18,2, w,h);
	if(c=='t')return TextAtlasPos(19,2, w,h);
	if(c=='u')return TextAtlasPos(0,3, w,h);
	if(c=='v')return TextAtlasPos(1,3, w,h);
	if(c=='w')return TextAtlasPos(2,3, w,h);
	if(c=='x')return TextAtlasPos(3,3, w,h);
	if(c=='y')return TextAtlasPos(4,3, w,h);
	if(c=='z')return TextAtlasPos(5,3, w,h);
	if(c=='0')return TextAtlasPos(6,3, w,h);
	if(c=='1')return TextAtlasPos(7,3, w,h);
	if(c=='2')return TextAtlasPos(8,3, w,h);
	if(c=='3')return TextAtlasPos(9,3, w,h);
	if(c=='4')return TextAtlasPos(10,3, w,h);
	if(c=='5')return TextAtlasPos(11,3, w,h);
	if(c=='6')return TextAtlasPos(12,3, w,h);
	if(c=='7')return TextAtlasPos(13,3, w,h);
	if(c=='8')return TextAtlasPos(14,3, w,h);
	if(c=='9')return TextAtlasPos(15,3, w,h);

	if(c=='~')return TextAtlasPos(0,4, w,h);
	if(c=='`')return TextAtlasPos(1,4, w,h);
	if(c=='!')return TextAtlasPos(2,4, w,h);
	if(c=='@')return TextAtlasPos(3,4, w,h);
	if(c=='#')return TextAtlasPos(4,4, w,h);
	if(c=='$')return TextAtlasPos(5,4, w,h);
	if(c=='%')return TextAtlasPos(6,4, w,h);
	if(c=='^')return TextAtlasPos(7,4, w,h);
	if(c=='&')return TextAtlasPos(8,4, w,h);
	if(c=='*')return TextAtlasPos(9,4, w,h);
	if(c=='(')return TextAtlasPos(10,4, w,h);
	if(c==')')return TextAtlasPos(11,4, w,h);
	if(c=='_')return TextAtlasPos(12,4, w,h);
	if(c=='+')return TextAtlasPos(13,4, w,h);
	if(c=='-')return TextAtlasPos(14,4, w,h);
	if(c=='=')return TextAtlasPos(15,4, w,h);
	if(c=='{')return TextAtlasPos(16,4, w,h);
	if(c=='}')return TextAtlasPos(17,4, w,h);
	if(c=='|')return TextAtlasPos(18,4, w,h);
	if(c=='[')return TextAtlasPos(19,4, w,h);
	if(c==']')return TextAtlasPos(0,5, w,h);
	if(c=='\\')return TextAtlasPos(1,5, w,h);
	if(c==':')return TextAtlasPos(2,5, w,h);
	if(c=='\"')return TextAtlasPos(3,5, w,h);
	if(c==';')return TextAtlasPos(4,5, w,h);
	if(c=='\'')return TextAtlasPos(5,5, w,h);
	if(c=='<')return TextAtlasPos(6,5, w,h);
	if(c=='>')return TextAtlasPos(7,5, w,h);
	if(c=='?')return TextAtlasPos(8,5, w,h);
	if(c==',')return TextAtlasPos(9,5, w,h);
	if(c=='.')return TextAtlasPos(10,5, w,h);
	if(c=='/')return TextAtlasPos(11,5, w,h);

	if(c==' ')return TextAtlasPos(w-2,h-1, w,h);
	return TextAtlasPos(0,0,1,1);
}
std::string TextAtlasMonospaced::getFile(){
	return "TextAtlas/monospaced.png";
}
float TextAtlasMonospaced::getAspectRatio(){
	return 0.6;
}

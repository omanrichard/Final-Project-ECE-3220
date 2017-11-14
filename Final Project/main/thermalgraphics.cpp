#include "thermalGraphics.h"


progressBar::progressBar(int x, int y, int length, int width){
	
	//(x,y) cordinate upper left corner of object
	xMin = x;
	yMin = y;
	xSize = length;
	ySize = width;

	//background rectangle
	fill(50,127,17);
	rec(x,y,length,width);

	//empty bar
	fill(40,0,127);
	rec(x,y+width/4,length,width-width/2);

	//draw tracker

}

void progressBar::update(int percent){

	//clear object
	fill(50,127,17);
	rec(xMin,yMin,xSize,ySize);

	//redraw empty bar
	fill(40,0,127);
	rec(xMin,yMin+ySize/4,xSize,ySize-ySize/2);

	//draw filled bar
	fill(255,0,0);
	rect(xMin,yMin,(xSize*percent)/100 ,ySize-ySize/2);
}
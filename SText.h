/*
 *  SText.h
 *  Sybil
 *
 *  Created by Will Gallia on 07/03/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _STEXT
#define _STEXT


#include "ofMain.h"


class SText {
	
	private: //don't really need this, just a reminder
	
	ofPoint pos, dim;
	string text, textStart;
	char mdown;
	
	ofTrueTypeFont ttf;
	float lineHeight, genCharWidth;
	
	int xOffset, yOffset;
	int initMX, initMY;
	int xDimS, yDimS;
	
	int resizeMargin;
	
	int count;
	
	vector<ofPoint> refPoints;
	
	public:
	
	SText();
	~SText();
	
	
	void setPos(float x, float y);
	void setPos(ofPoint p);
	void setDim(float w, float h);
	void setAll(float x, float y, float w, float h);
	void setAll(string s, float x, float y, float w, float h);

	void setText(string s);
	
	void cursor(int x, int y, int b);
	void setMouseOffset(int x, int y);
	void mouseDown();
	void mouseUp();
	
	void doLines();
	
	
	void draw();
	
	
	
};


#endif
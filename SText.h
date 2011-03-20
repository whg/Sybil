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
#include "SPreview.h"


class SText {
	
	private: 
	
	int uid;
	ofPoint pos, dim;
	string text, textStart;
	char mdown;
	
	ofTrueTypeFont ttf;
	float lineHeight, genCharWidth;
	
	int xOffset, yOffset;
	int initMX, initMY;
	int xDimS, yDimS;
	
	int resizeMargin;
	bool focus;
	
		
	vector<ofPoint> refPoints;
	
	//SPreview* previewPtr;

	
	public:
	
	SText();
	SText(int i);
	~SText();
	
	
	void setPos(float x, float y);
	void setPos(ofPoint p);
	void setDim(float w, float h);
	void setAll(float x, float y, float w, float h);
	void setAll(string s, float x, float y, float w, float h);

	void setText(string s);
	
	void cursor(int x, int y, int b);
	void setMouseOffset(int x, int y);
	void setMouseType();
	void resetMouse();
	
	void wrapLines();
	void setYDim();
	
	void draw();
	void drawBoundingBox();
	void drawBoundingLines();
	
	

};


#endif
/*
 *  SItem.h
 *  Sybil
 *
 *  Created by Will Gallia on 20/03/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _SITEM
#define _SITEM

#include "ofMain.h"


class SItem {
	
private: 	
	
	//these are used for mouse actions
	int xOffset, yOffset;
	int initMX, initMY;
	int xDimS, yDimS;
	
	
public:
	
	//think these need to be public to be accessed in sub class
	int uid; //unique id
	bool focus;
	ofPoint pos, dim;
	int resizeMargin;
		
	enum cursorTypes {
		NONE,
		MOVE,
		RESIZEX,
		RESIZEY,
		RESIZEBOTH
	};
	
	cursorTypes cursorType;

	
	SItem();
	SItem(int i);
	virtual ~SItem(); //always have a virtual deconstructor in a base class...
	
	
	void setPos(float x, float y);
	void setPos(ofPoint p);
	void setDim(float w, float h);
	void setAll(float x, float y, float w, float h);
		
	void cursor(int x, int y);
	void setCurrentParams(int x, int y);
	bool setCursorType(int x, int y);
	bool setActionType(int x, int y, int b);
	void resetCursorType();
	void mouseActions(int x, int y);
	
	void drawBoundingBox();
	
	void setFocus(bool b);

	
	virtual void draw();
	
	
	virtual void setText(string s) = 0;
	virtual void hello();
	
	
};


#endif
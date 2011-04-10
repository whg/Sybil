/*
 *  SItem.h
 *  Sybil
 *
 *  Created by Will Gallia on 20/03/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

#ifndef _SITEM
#define _SITEM

#include "STypes.h"
#include "ofMain.h"

class SPreview;

class SItem {
	
private: 	
	
	//these are used for mouse actions
	SPoint offset, initPos, initDim;
//	int xOffset, yOffset;
//	int initMX, initMY;
//	int xDimS, yDimS;
	
	
public:
	
	//think these need to be public to be accessed in sub class
	int uid; //unique id
	bool focus;
	SPoint pos, dim;
	int resizeMargin;
	SPreview *previewPtr;

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
	
	
	void setPos(int x, int y);
	void setDim(int w, int h);
	void setAll(int x, int y, int w, int h);
		
	void cursor(int x, int y);
	void setCurrentParams(int x, int y);
	bool setCursorType(int x, int y);
	bool setActionType(int x, int y, int b);
	void resetCursorType();
	void mouseActions(int x, int y);
	
	void drawBoundingBox();
	
	void setFocus(bool b);

	
	virtual void draw();
	
	virtual void updateWindow() {};
	virtual void setText(string s) {};
	virtual void loadImage(string s) {};
	
	virtual void hello();
	
	
};


#endif
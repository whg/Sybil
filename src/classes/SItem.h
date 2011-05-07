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

class SPreview;
class SSerial;

#include "STypes.h"
#include "ofMain.h"
#include "SConstants.h"

class SItem {
	
private: 	
	
	//these are used for mouse actions
	SPoint offset, initPos, initDim;	
	
public:
	
	int uid; //unique id
	bool focus;
	SPoint pos, dim;
	int resizeMargin;
	
	SPoint screenPos;
	
	//pointers
	SPreview *previewPtr;
	SSerial *serialPtr;
	
	cursorTypes cursorType;

	
	SItem();
	SItem(int i);
	virtual ~SItem();
	
	
	void setPos(int x, int y);
	void setDim(int w, int h);
	void setAll(int x, int y, int w, int h);
		
	void setUid(int i);
	int getUid();
	
	void cursor(int x, int y);
	void setCurrentParams(int x, int y);
	bool setCursorType(int x, int y);
	bool setActionType(int x, int y, int b);
	void resetCursorType();
	void mouseActions(int x, int y);
	
	void drawBoundingBox();
	
	void setFocus(bool b);

	
	virtual void draw();
	virtual void update() {};
	virtual void updateWindow() {};
	
	virtual void hello();
	
	virtual void giveAllPoints(vector<SPoint> &points) = 0;
	
	
};


#endif
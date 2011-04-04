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

@class STextController;

#include "ofMain.h"
#include "SItem.h"
#import <Cocoa/Cocoa.h>
#import "STextController.h"

class SText : public SItem {
	
	private: 

	string text;
	vector<ofPoint> refPoints;
	
	ofTrueTypeFont ttf;
	float lineHeight, genCharWidth;
	
	STextController* windowController;
	
	public:
	
	SText();
	SText(int i);
	~SText();
	

	void setText(string s);
	
	void updateWindow();
	
	void wrapLines();
	void setYDim();
	
	void draw();

	void hello();
	

};


#endif
/*
 *  SText.h
 *  Sybil
 *
 *  Created by Will Gallia on 07/03/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

#ifndef _STEXT
#define _STEXT

#include "ofMain.h"
#include "SItem.h"
#import <Cocoa/Cocoa.h>
#import "STextController.h"
#include "STypes.h"

@class STextController;

class SText : public SItem {
	
private: 

	string text;
	vector<ofPoint> refPoints;
	vector<SPoint> textPoints;
	
	ofTrueTypeFont ttf;
	float lineHeight, genCharWidth;
	
	int fontSize;
	string fontName;
	
	STextController* windowController;
	
	void wrapLines();
	void setYDim();
	
	void findTextPoints();
	
public:
	
	SText();
	SText(int i);
	~SText();
	

	void setText(string s);
	void setFont(string fontname);
	void setFontSize(int s);
		
	void updateWindow();

	void draw();
	void update();

	void hello();
	
	void giveAllPoints(vector<SPoint> &points);
	

};


#endif
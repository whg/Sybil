/*
 *  SText.cpp
 *  Sybil
 *
 *  Created by Will Gallia on 07/03/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "SText.h"



SText::SText(int i)
: SItem(i) {

	text = "hello my name:";
	
	ttf.loadFont("Georgia.ttf", 20, true, true, true);
	lineHeight = ttf.getLineHeight();
	genCharWidth = lineHeight/3;
	
	
	//really not sure about this, getting some pretty wierd errors in the console
	STextController* windowController;
	windowController = [[STextController alloc] initWithWindowNibName:@"STextWindow"];
	//[windowController set_uid: i];
	[windowController showWindow:nil];
	
	//NSLog(@"id for window = %i", [windowController uid]);
	
	[windowController release];
}

SText::~SText() {

}


void SText::draw() {
	ofPushMatrix();
	ofTranslate(pos.x, pos.y);
		
	if(focus) drawBoundingBox();
		
	wrapLines();
	
	//the y dimension is set automatically in text mode
	setYDim();
		
	ofNoFill();
	ofSetColor(0, 0, 0);
	
	//to place the characters nicely, we have to draw each character...
	//...character by character, one by one 
	//and place each character where wrapLines() says
	int j = 0;
	for (int i = 0; i < text.length(); i++) {

		ofPushMatrix();
		ofTranslate(refPoints[j].x, refPoints[j].y, 0);
		if (text[i] != ' ') {
		
			int cy = ((unsigned char)text[i]) - NUM_CHARACTER_TO_START;
			ttf.drawCharAsShape(cy, 0, 0);
			
			j++;
		}
		
		ofPopMatrix();

	}
	
	ofPopMatrix();

}


void SText::setText(string s) {
	text = s;
}


//this method wraps lines around a given box: given by the ofPoint: dim
//it wraps a word (i.e. places on the next line) if the first letter of
//the next word is over the x dimension of the box + a generic character width (lineHeight/3)
void SText::wrapLines() {
		
	int lus = 0; //letters until space
	int tll = 0; //temp letter length
	int ls = 0; //last space
	
	//get the reference points
	ttf.getReferencePoints(text, refPoints);
	
	for (int i = 0; i < text.size(); i++) {
		
		if (refPoints[lus].x > (dim.x + genCharWidth)) {
			
			int k = refPoints[ls].x;
			//reset the new lines to spaces
			for (int j = ls; j < refPoints.size(); j++) {
				refPoints[j].x = refPoints[j].x - k;
				refPoints[j].y += lineHeight;
			}
		} //end if				
		
		
		if (text[i] == ' ') {
			ls = lus; //set position of last space
		} 
		else {
			//add a lineHeight to all characters so the origin for each text box is the 
			//top left corner, not the top left corner plus a lineHeight
			refPoints[lus].y += lineHeight;
			lus++; //only increment if the character isn't a space
		}
	}
	
	
	
}
	
void SText::setYDim() {
	if (text == "") {
		dim.y = lineHeight*1.2;
	}
	else {
		dim.y = refPoints.back().y + (lineHeight*0.2); 
	}
}
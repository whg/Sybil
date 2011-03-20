/*
 *  SText.cpp
 *  Sybil
 *
 *  Created by Will Gallia on 07/03/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "SText.h"

SText::SText(int i) {
	uid = i; //set unique id
	
	pos = ofPoint(0, 0);
	dim = ofPoint(50, 0);
	text = "";
	
	ttf.loadFont("Georgia.ttf", 20, true, true, true);
	lineHeight = ttf.getLineHeight();
	genCharWidth = lineHeight/3;
	
	resizeMargin = 5;
	mdown = 'n';
	focus = false;
	cursorType = NONE;
		
	//pointer to preview
	//previewPtr = (SPreview*) ofGetAppPtr();
		
}

SText::~SText() {

}

void SText::setPos(float x, float y) {
	pos.set(x, y);
}

void SText::setPos(ofPoint p) {
	pos = p;
}

void SText::setDim(float w, float h) {
	dim.set(w, h);
}

void SText::setAll(float x, float y, float w, float h) {
	pos.set(x, y);
	dim.set(w, h);
}

void SText::setAll(string s, float x, float y, float w, float h) {
	pos.set(x, y);
	dim.set(w, h);
	textStart = s;
	text = s;
	ttf.getReferencePoints(s, refPoints);
}

void SText::draw() {
	ofPushMatrix();
	ofTranslate(pos.x, pos.y);
	
	ofCircle(0, 0, 2);
	
	if(focus) drawBoundingBox();
	
	wrapLines();
	setYDim();
		
	ofNoFill();
	ofSetColor(0, 0, 0);
	
	//do place the characters nicely, we have to draw each character...
	//...character by character, one by one 
	//and place each character where wrapLines() says
	int j = 0;
	for (int i = 0; i < text.length(); i++) {

		ofPushMatrix();
		ofTranslate(refPoints[j].x, refPoints[j].y, 0);
		int cy = ((unsigned char)text[i]) - NUM_CHARACTER_TO_START;
		ttf.drawCharAsShape(cy, 0, 0);
		ofPopMatrix();
		if (text[i] != ' ') {
			j++;
		}
	}
	
	ofPopMatrix();

}

void SText::drawBoundingBox() {
	//simple rectangle
	ofNoFill();
	ofSetColor(0, 250, 200);
	ofRect(0, 0, dim.x, dim.y);
}

void SText::drawBoundingLines() {
	//lines on left & right side
	ofSetColor(0, 250, 200);
	ofNoFill();
	ofLine(0, 0, 0, dim.y);
	ofLine(dim.x, 0, dim.x, dim.y);
}

void SText::setText(string s) {
	textStart = s + " ";
	text = s;
}

void SText::cursor(int x, int y) {
	
	setCursorType(x, y);
	
	mouseActions(x, y);
	
	
	if (focus) {
		//previewPtr->setFocus(uid);
	}
	
}

void SText::setCurrentParams(int x, int y) {
	xOffset = x - pos.x;
	yOffset = y - pos.y;
	xDimS = dim.x;
	yDimS = dim.y;
	initMX = x;
	initMY = y;
}

void SText::setCursorType(int x, int y) {
	
	//for moving, this shows a crosshair
	if (x > pos.x && x < pos.x + dim.x &&
			y > pos.y && y < pos.y + dim.y) {
		glutSetCursor(GLUT_CURSOR_CROSSHAIR); 		
	} 
	
	//this is for increasing x, ie right border
	else if (x > pos.x + dim.x - resizeMargin && x < pos.x + dim.x + resizeMargin &&
					 y > pos.y && y < pos.y + dim.y) {
		glutSetCursor(GLUT_CURSOR_LEFT_RIGHT);		
	}

	//normal cursor
	else {
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}
	
}

void SText::setActionType(int x, int y, int b) {
	
	//for moving
	if (x > pos.x && x < pos.x + dim.x &&
			y > pos.y && y < pos.y + dim.y) {
		if (b) { // if mousepressed
			cursorType = MOVE;
			focus = true;
		}
	} 
	
	//this is for increasing x, ie right border
	else if (x > pos.x + dim.x - resizeMargin && x < pos.x + dim.x + resizeMargin &&
					 y > pos.y && y < pos.y + dim.y) {
		if (b) { // if mousepressed
			cursorType = RESIZE;
			focus = true;
		}
	}
	
}

void SText::resetCursorType() {
	cursorType = NONE;
}

void SText::mouseActions(int x, int y) {
	
	//this is to move
	if (cursorType == MOVE) { 
		printf("move move move\n");
		pos.set(x-xOffset, y-yOffset); //do the move
	}
	
	//this is to resize
	if (cursorType == RESIZE) {
		dim.x = xDimS + x - initMX;
		//do the line wrapping as well
		wrapLines();
	}
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
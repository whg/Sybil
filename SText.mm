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
	
	if(focus) drawBoundingBox();
	
	wrapLines();
	setYDim();
		
	ofNoFill();
	ofSetColor(0, 0, 0);
	
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
	ofRect(0, -lineHeight, dim.x, dim.y);
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

void SText::mouseUp() {
	mdown = 'n';
}
//
//void SText::mouseDown() {
//	mdown = true;
//}

void SText::cursor(int x, int y, int b) {
	
	setMouseOffset(x, y);
	
	//for moving, this shows a crosshair
	if ((x > pos.x && x < pos.x+dim.x - resizeMargin &&
			 y > pos.y && y < pos.y+dim.y - resizeMargin) && mdown != 'x') {
		glutSetCursor(GLUT_CURSOR_CROSSHAIR); 		
		if (b) {
			focus = true;
			mdown = 'm';
			pos.set(x-xOffset, y-yOffset);
		}
	} 
	
	//this is for increasing x, ie right border
	else if ((x > pos.x+dim.x - resizeMargin && 
					  x < pos.x+dim.x + resizeMargin) || mdown != 'm') {
		glutSetCursor(GLUT_CURSOR_LEFT_RIGHT);		
		if (b) {
			focus = true;
			mdown = 'x';
			dim.x = xDimS + x - initMX;
			//text = textStart;
			wrapLines();
		}
	}
	
	//normal cursor
	else {
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}
	
	if (focus) {
		//previewPtr->setFocus(uid);
	}
	
}

void SText::setMouseOffset(int x, int y) {
	xOffset = x - pos.x;
	yOffset = y - pos.y;
	xDimS = dim.x;
	yDimS = dim.y;
	initMX = x;
	initMY = y;
}

void SText::wrapLines() {
		
	int lus = 0; //letters until space
	int tll = 0; //temp letter length
	int ls = 0; //last space
	string tempText = text;
	
	//get the reference points
	int li = ttf.getReferencePoints(tempText, refPoints);
	
	for (int i = 0; i < tempText.size(); i++) {
		
		if (refPoints[lus].x > dim.x) {
			
			int k = refPoints[ls].x;
			//reset the new lines to spaces
			for (int j = ls; j < refPoints.size(); j++) {
				refPoints[j].x = refPoints[j].x - k;
				refPoints[j].y += lineHeight;
			}
		} //end if				
		
		if (tempText[i] == ' ') {
			ls = lus; //set position of last space
		} 
		else {
			lus++;
		}
	}
	
	
	text = tempText;
	
}
	
void SText::setYDim() {
	if (text == "") {
		dim.y = lineHeight*1.2;
	}
	else {
		dim.y = refPoints.back().y + (lineHeight*1.2); 
	}
}
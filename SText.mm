/*
 *  SText.cpp
 *  Sybil
 *
 *  Created by Will Gallia on 07/03/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "SText.h"

SText::SText() {
	pos = ofPoint(0, 0);
	dim = ofPoint(0, 0);
	text = "";
	
	ttf.loadFont("Georgia.ttf", 20, true, true, true);
	lineHeight = ttf.getLineHeight();
	genCharWidth = lineHeight/3;
	
	resizeMargin = 20;
	mdown = 'n';
	
	count = 0;
	
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
	
	ofNoFill();
	ofSetColor(0, 0, 0);
	ofRect(0, 0, dim.x, dim.y);
	
	doLines();
	
	//ttf.drawStringAsShapes(text, 0, lineHeight);	
	
	ofFill();
	ofSetColor(255, 100, 50);
	//ttf.drawDotsOnFirst(text, 0, lineHeight);
		
	ofSetColor(0, 255, 100);
	
	ofNoFill();
	ofSetColor(0, 0, 0);
	
	int j = 0;
	for (int i = 0; i < text.length(); i++) {

		ofPushMatrix();
		ofTranslate(refPoints[j].x, refPoints[j].y+lineHeight, 0);
		ofCircle(0, 0, 3);
		int cy = ((unsigned char)text[i]) - NUM_CHARACTER_TO_START;
		ttf.drawCharAsShape(cy, 0, 0);
		ofPopMatrix();
		if (text[i] != ' ') {
			j++;
		}
	}
	
	ofPopMatrix();

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
	
	//this is the crosshair, for moving
	if ((x > pos.x && x < pos.x+dim.x - resizeMargin &&
			 y > pos.y && y < pos.y+dim.y - resizeMargin) || mdown == 'm') {
		glutSetCursor(GLUT_CURSOR_CROSSHAIR); 		
		if (b) {
			mdown = 'm';
			pos.set(x-xOffset, y-yOffset);
		}
	} 
	
	//this is for increasing x, ie right border
	else if ((x > pos.x+dim.x - resizeMargin && 
					  x < pos.x+dim.x + resizeMargin) || mdown == 'x') {
		glutSetCursor(GLUT_CURSOR_LEFT_RIGHT);		
		if (b) {
			mdown = 'x';
			dim.x = xDimS + x - initMX;
			//text = textStart;
			doLines();
		}
	}
	
	//this is for increasing y, ie bottom border
	else if ((y > pos.y+dim.y - resizeMargin && 
						y < pos.y+dim.y + resizeMargin) || mdown == 'y') {
		glutSetCursor(GLUT_CURSOR_UP_DOWN);
		if (b) {
			mdown = 'y';
			dim.y = yDimS + y - initMY;
		}
	}
	
	//normal cursor
	else {
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
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

void SText::doLines() {
		
	int rw = 0; //reset width
	int lus = 0; //letters until space
	int tll = 0; //temp letter length
	int ls = 0; //last space
	int ns = 0; //number of spaces
	string tempText = text;
	
	int li = ttf.getReferencePoints(tempText, refPoints);
	
	//printf("refpoints = %i, text = %i\n", (int) refPoints.size(), (int) text.length());
//	float tsl = refPoints.back().x; //total string length, ie last element

	
	//for (int i = textStart.size()-1; i <= 0; i--) {
//		if (textStart[i] == ' ') {
//			if (tsl - refPoints[lus].x - rw > dim.x) {
//				tempText[i] = '\n';
//				rw = refPoints[lus].x;
//			}
//		}
//		lus++;
//	}
	
//	for (int i = 0; i < textStart.size()-1; i++) {
//		if (textStart[i] == ' ') {
//			if (refPoints[lus+1].x - (dim.x*rw) > dim.x) {
//				tempText[ls] = '\n';
//				rw++;
//			}
//			ls = i;
//		} 
//		else {
//			lus++;
//		}
//	}
	
	for (int i = 0; i < tempText.size(); i++) {
		
		if (refPoints[lus].x > dim.x) {
			
			int k = refPoints[ls].x;
			int m = 0;
			//reset the new lines to spaces
			for (int j = (ls); j < refPoints.size(); j++) {
				m = (refPoints[j].x - k);
				refPoints[j].x = m;
				refPoints[j].y += lineHeight;
			}
						
			rw++;
		}
				
		
		if (tempText[i] == ' ') {
			ls = lus; //set position of last space
			ns++;
		} 
		else {
			lus++;
		}
	}
	
	
	text = tempText;
	
}
	

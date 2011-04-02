/*
 *  SItem.cpp
 *  Sybil
 *
 *  Created by Will Gallia on 20/03/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include "SItem.h"
#include "SPreview.h"

//this is a silly way of doing things
SPreview *previewPtr;


SItem::SItem(int i) {
	uid = i; //set unique id
	
	pos = ofPoint(ofRandom(10, 100), 10);
	dim = ofPoint(200, 50);

	
	resizeMargin = 5;
	focus = false;
	cursorType = NONE;
	
	//pointer to preview
	previewPtr = (SPreview*) ofGetAppPtr();
	
}

SItem::~SItem() {	
	
	pos = ofPoint(10, 10);
	dim = ofPoint(50, 0);
	
	resizeMargin = 5;
	focus = false;
	cursorType = NONE;
}

void SItem::setPos(float x, float y) {
	pos.set(x, y);
}

void SItem::setPos(ofPoint p) {
	pos = p;
}

void SItem::setDim(float w, float h) {
	dim.set(w, h);
}

void SItem::setAll(float x, float y, float w, float h) {
	pos.set(x, y);
	dim.set(w, h);
}

void SItem::setFocus(bool b) {
	focus = b;
}

void SItem::draw() {
	ofPushMatrix();
	ofTranslate(pos.x, pos.y);
		
	if(focus) drawBoundingBox();
	
	ofPopMatrix();
	
}

void SItem::drawBoundingBox() {
	//simple rectangle, in a nice blue
	ofNoFill();
	ofSetColor(0, 250, 200);
	ofRect(0, 0, dim.x, dim.y);
}


void SItem::cursor(int x, int y) {
	
	setCursorType(x, y);
	mouseActions(x, y);
	
	
	if (focus) {
		previewPtr->setFocus(uid);
	}
	
}

void SItem::setCurrentParams(int x, int y) {
	xOffset = x - pos.x;
	yOffset = y - pos.y;
	xDimS = dim.x;
	yDimS = dim.y;
	initMX = x;
	initMY = y;
}

bool SItem::setCursorType(int x, int y) {
	
	//for moving, this shows a crosshair
	if (x > pos.x && x < pos.x + dim.x &&
			y > pos.y && y < pos.y + dim.y) {
		glutSetCursor(GLUT_CURSOR_CROSSHAIR); 	
		return true;
	} 
	
	//this is for increasing x, ie right border
	else if (x > pos.x + dim.x - resizeMargin && x < pos.x + dim.x + resizeMargin &&
					 y > pos.y && y < pos.y + dim.y) {
		glutSetCursor(GLUT_CURSOR_LEFT_RIGHT);	
		return true;
	}
	
	//this is for increasing y, ie the bottom
	else if (x > pos.x && x < pos.x + dim.x &&
					 y > pos.y  + dim.y - resizeMargin && y < pos.y + dim.y + resizeMargin) {
		glutSetCursor(GLUT_CURSOR_UP_DOWN);
		return true;
	}
	
	//normal cursor
	else {
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}
	
	return false;
}

bool SItem::setActionType(int x, int y, int b) {
	
	
	//for moving
	if (x > pos.x && x < pos.x + dim.x &&
			y > pos.y && y < pos.y + dim.y) {
		if (b) { // if mousepressed
			cursorType = MOVE;
			focus = true;
			previewPtr->setFocus(uid);
			return true;
		}
	} 
	
	//this is for increasing x, ie right border
	else if (x > pos.x + dim.x - resizeMargin && x < pos.x + dim.x + resizeMargin &&
					 y > pos.y && y < pos.y + dim.y) {
		if (b) { // if mousepressed
			cursorType = RESIZEX;
			focus = true;
			previewPtr->setFocus(uid);
			return true;
		}
	}
	
	//this is for increasing y, ie the bottom
	else if (x > pos.x && x < pos.x + dim.x &&
					 y > pos.y  + dim.y - resizeMargin && y < pos.y + dim.y + resizeMargin) {
		if (b) { // if mousepressed
			cursorType = RESIZEY;
			focus = true;
			previewPtr->setFocus(uid);
			return true;
		}	
	}

	return false;
}

void SItem::resetCursorType() {
	cursorType = NONE;
}

void SItem::mouseActions(int x, int y) {
	
	//this is to move
	if (cursorType == MOVE) { 
		pos.set(x-xOffset, y-yOffset); //do the move
	}
	
	//this is to resize
	else if (cursorType == RESIZEX) {
		dim.x = xDimS + x - initMX;
		//do the line wrapping as well
	}
	
	else if (cursorType == RESIZEY) {
		dim.y = yDimS + y - initMY;
	}
}

void SItem::hello() {
	printf("hello from SItem\n");
}

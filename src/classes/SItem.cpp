/*
 *  SItem.cpp
 *  Sybil
 *
 *  Created by Will Gallia on 20/03/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */


#include "SItem.h"
#include "SPreview.h"
#include "SSerial.h"


SItem::SItem(int i) {
	uid = i; //set unique id
	
	//set initial attributes
	pos = SPoint((int) ofRandom(0, 100), (int) ofRandom(0, 100));
	dim = SPoint(150, 50);

	//init variables
	resizeMargin = 20;
	focus = false;
	cursorType = NONE;
	
	//pointer to preview
	previewPtr = (SPreview*) ofGetAppPtr();
	
	//pointer to serial
	serialPtr = previewPtr->getSerialConnection();
	
}

SItem::~SItem() {	
	
	printf("SItem deconstructor called\n");
}


// all of these setters only work if
// the value given is not -1, this way 
// we can set only one component with 
// one method...
void SItem::setPos(int x, int y) {
	if (x != -1) pos.x = x;
	if (y != -1) pos.y = y;
}

void SItem::setDim(int w, int h) {
	if (w != -1) dim.x = w;
	if (h != -1) dim.y = h;
}

void SItem::setAll(int x, int y, int w, int h) {
	if (x != -1) pos.x = x;
	if (y != -1) pos.y = y;
	if (w != -1) dim.x = w;
	if (h != -1) dim.y = h;
}

void SItem::setFocus(bool b) {
	focus = b;
}

// - - - uid - - -

void SItem::setUid(int i) {
	uid = i;
}

int SItem::getUid() {
	return uid;
}


//generic draw method, just draws a bounding box
//will never be called...
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
	
	//scale the points
	SPoint scale = previewPtr->getDrawingArea();	
	x*= scale.x/ofGetWidth();
	y*= scale.y/ofGetHeight();
	
	offset.set(x - pos.x, y - pos.y);
	initDim.set(dim.x, dim.y);
	initPos.set(x, y);

}

bool SItem::setCursorType(int x, int y) {
	
	//scale the points....
	SPoint scale = previewPtr->getDrawingArea();
	x*= scale.x/ofGetWidth();
	y*= scale.y/ofGetHeight();
	
	//for moving, this shows a crosshair
	if (x > pos.x && x < pos.x + dim.x &&
			y > pos.y && y < pos.y + dim.y) {
		glutSetCursor(GLUT_CURSOR_CROSSHAIR); 	
		return true;
	} 
	
	//this is for increasing x, ie right border
	else if (x > pos.x + dim.x - resizeMargin && x < pos.x + dim.x + resizeMargin &&
					 y > pos.y && y < pos.y + dim.y &&
					 dim.x > 0 && dim.y > 0) {
		glutSetCursor(GLUT_CURSOR_LEFT_RIGHT);	
		return true;
	}
	
	//this is for increasing y, ie the bottom
	else if (x > pos.x && x < pos.x + dim.x &&
					 y > pos.y  + dim.y - resizeMargin && y < pos.y + dim.y + resizeMargin &&
					 dim.x > 0 && dim.y > 0) {
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
	
	//scale the input points...
	SPoint scale = previewPtr->getDrawingArea();	
	x*= scale.x/ofGetWidth();
	y*= scale.y/ofGetHeight();
	
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
	
	//do some scaling before hand...
	SPoint scale = previewPtr->getDrawingArea();
	x*= scale.x/ofGetWidth();
	y*= scale.y/ofGetHeight();
	
	//this is to move
	if (cursorType == MOVE) { 
		pos.x = x-offset.x; //do the move
		pos.y = y-offset.y; 
	}
	
	//this is to resize
	else if (cursorType == RESIZEX) {
		dim.x = initDim.x + x - initPos.x;
		//do the line wrapping as well
	}
	
	else if (cursorType == RESIZEY) {
		dim.y = initDim.y + y - initPos.y;
	}
	
	updateWindow();
}

void SItem::hello() {
	printf("hello from SItem\n");
}

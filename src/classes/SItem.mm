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

//this is a silly way of doing things
SPreview *previewPtr;


SItem::SItem(int i) {
	uid = i; //set unique id
	
	//set initial attributes
	pos.x = (int) ofRandom(0, 100);
	pos.y = (int) ofRandom(0, 100);
	dim.x = 200;
	dim.y = 50;

	//init variables
	resizeMargin = 5;
	focus = false;
	cursorType = NONE;
	
	//pointer to preview
	previewPtr = (SPreview*) ofGetAppPtr();
	
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
	if (x != -1) pos.y = y;
	if (x != -1) dim.x = w;
	if (x != -1) dim.y = h;
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
		pos.x = x-xOffset; //do the move
		pos.y = y-yOffset; 
	}
	
	//this is to resize
	else if (cursorType == RESIZEX) {
		dim.x = xDimS + x - initMX;
		//do the line wrapping as well
	}
	
	else if (cursorType == RESIZEY) {
		dim.y = yDimS + y - initMY;
	}
	
	update();
}

void SItem::hello() {
	printf("hello from SItem\n");
}

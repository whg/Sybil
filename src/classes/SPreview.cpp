/*
 *  SPreview.cpp
 *  Sybil
 *
 *  Created by Will Gallia on 06/02/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */


#include "SPreview.h"

// - - - DECONSRUCTOR - - -
SPreview::~SPreview() {
	
	//delete all items
	for (int i = 0; i < items.size(); i++) {
		delete items[i];
	}
	
	delete terminal;
	delete serial;
	delete commander;
	
}


// - - - SETUP - - -
void SPreview::setup(){
	
	//set up all oF things...
	ofBackground(255, 255, 255);
	ofSetBackgroundAuto(true);
	ofSetFrameRate(NORMAL_FRAMERATE);
	ofEnableSmoothing();
	ofEnableAlphaBlending();

	
	idc = 0;
	fid = -1;
	ztrans = 0;
	isDrawing = false;
	
	//instantiate serial
	serial = new SSerial();
	
	//now instantiate commander, passing serial pointer
	commander = new SCommand(serial);
	
	//instantiate terminal, passing commander pointer
	terminal = new STerm(commander);
	
	setViewMode(TERMINAL);
	
	//set up cocoa part - do this last
	NSApplicationMain(0, NULL);

}

/* - - - UPDATE - - -

 this is where we do the serial stuff...
 things can happen pretty fast so we need to check every frame...

 */

void SPreview::update(){
	
	//printf("SSerial done is %i\n", serial->isDone());
	
	if (isDrawing) {
		serial->update();
		
		if (serial->isDone() && commander->isDoingFile()) {
			printf("we are iterating\n");
			if (!terminal->iterateFile()) {
				commander->setDoingFile(false);
			}
		}
	}
	
}

// - - - DRAW - - -
void SPreview::draw(){
	
	switch (mode) {
			
		//draw preview mode.
		//this draws all items...
		case PREVIEW:
			
			ofPushMatrix();
			ofTranslate(0, 0, ztrans);
			
			ofSetColor(0, 0, 0);
			for (int i = 0; i < items.size(); i++) {
				items[i]->draw();
			}
			ofPopMatrix();
			
			break;
			
		//draw the terminal
		case TERMINAL:
			
			terminal->draw();
			break;

	}

}

//focus stuff... 
//this is so only one thing is change at a time...
void SPreview::setFocus(int i) {
	fid = i;
}

int SPreview::getFocus() {
	return fid;
}


/* 
 - - - KEYS - - -
 
 not a lot going on here...
 if in terminal mode, send all keypressses to terminal
 
 */

void SPreview::keyPressed(int key){
	
	//send the keypresses to the terminal
	if (mode == TERMINAL) {
		terminal->keyPressed(key);
	}

}

void SPreview::keyReleased(int key){
	
}

/*
 
 - - - MOUSE ACTIONS - - -
 
 all mouse actions are sent to the items,
 where items can be moved, resized, etc...
 only do these if we are in preview mode
 
 */


void SPreview::mouseMoved(int x, int y){
	if (mode == PREVIEW) {
		for (int i = 0; i < items.size(); i++) {
			if(items[i]->setCursorType(x, y)) {
				break;
			}
		}
	}
}

void SPreview::mouseDragged(int x, int y, int button){
	if (mode == PREVIEW) {
		for (int i = 0; i < items.size(); i++) {
			items[i]->cursor(x, y);
		}
	}
	
	if (button == 2) {
		ztrans = x-100;
		printf("ztrans = %i", ztrans);
	}
}

void SPreview::mousePressed(int x, int y, int button){
	if (mode == PREVIEW) {
		bool hit = false;
		for (int i = 0; i < items.size(); i++) {
			items[i]->setCurrentParams(x, y);
			if (items[i]->setActionType(x, y, ++button)) {
				hit = true;
				break;
			}
		}
		if (hit) {
			//this is so only one is in focus at any time
			for (int i = 0; i < items.size(); i++) {
				items[i]->setFocus(false);
			}
			printf("fid = %i, size of items = %i\n", fid, (int) items.size());
			if (fid != -1) items[fid]->setFocus(true);
		}
	}// end if
}

void SPreview::mouseReleased(int x, int y, int button){
	if (mode == PREVIEW) {
		for (int i = 0; i < items.size(); i++) {
			items[i]->resetCursorType();
		}
	}
}


// - - - ITEM HOUSEWORK - - -

void SPreview::addTextItem() {
	
	items.push_back(new SText(idc++));
	
}

void SPreview::addImageItem(string file) {
	
	items.push_back(new SImage(idc++, file));
	
}

void SPreview::removeItem(int i) {

	for (int j = 0 ; j < items.size(); j++) {
		if (items[j]->uid == i) {
			delete items[j];
			items.erase(items.begin()+j);
			break;
		}
	}
	
	//now reset uids
	for (int i = 0; i < items.size(); i++) {
		items[i]->setUid(++i);
	}
	
	fid = -1;
	idc = (int) items.size();
}

// - - - SET VIEW MODE - - -

void SPreview::setViewMode(int m) {
	switch (m) {
		case PREVIEW:
			mode = PREVIEW;
			ofSetWindowShape(PREVIEW_WIDTH, PREVIEW_HEIGHT);
			break;
		case TERMINAL:
			mode = TERMINAL;
			ofSetWindowShape(TERMINAL_WIDTH, TERMINAL_HEIGHT);
			break;

	}
}

// - - - DRAWING - - -

void SPreview::startedDrawing() {
	isDrawing = true;
	ofSetFrameRate(SERIAL_FRAMERATE);
}

void SPreview::stoppedDrawing() {
	isDrawing = false;
	ofSetFrameRate(NORMAL_FRAMERATE);
}

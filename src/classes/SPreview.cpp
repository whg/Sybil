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
	ztrans = -1900;
	isDrawing = false;
	pointsDone = 0;
	useProgressIndicator = false;
	numPoints = 1;

	drawingArea = SPoint(3850, 2800);
	
	//instantiate serial
	serial = new SSerial();
	
	//now instantiate commander, passing serial pointer
	commander = new SCommand(serial);
	
	//instantiate terminal, passing commander pointer
	terminal = new STerm(commander);
	
	setViewMode(PREVIEW);
		
	//set up cocoa part - do this last
	NSApplicationMain(0, NULL);

}

/* - - - UPDATE - - -

 this is where we do the serial stuff...
 things can happen pretty fast so we need to check every frame...

 */

void SPreview::update(){
	
		
	if (isDrawing) {
		serial->update();
				
		if (commander->isDoingFile()) {
			terminal->iterateFile();
		}
		
		updateProgressIndicator();
	}
	
}

// - - - DRAW - - -
void SPreview::draw(){
	
	switch (mode) {
			
		//draw preview mode.
		//this draws all items...
		case PREVIEW:
			
			ofPushMatrix();
			ofTranslate(-drawingArea.x/2.5, -drawingArea.y/2.5, ztrans);
			
			ofNoFill();
			ofSetColor(0, 0, 0);
			ofRect(0, 0, drawingArea.x, drawingArea.y);
			
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
	
	//ofSetColor(0, 0, 0);
//	ofDrawBitmapString(ofToString(ofGetFrameRate(), 1), 400, 300);

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
	
	else {
		//this is a little secret...
		//ctrl - to zoom out 
		//ctrl = to zoom in
		switch (key) {
			case 31:
				ztrans-= 100;
				break;
			case 61:
				ztrans+= 100;
				break;
		}
		
	}

	printf("key = %i\n", key);
	
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
			//printf("fid = %i, size of items = %i\n", fid, (int) items.size());
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
			ofSetWindowPosition(50, 50);
			break;
		case TERMINAL:
			mode = TERMINAL;
			ofSetWindowShape(TERMINAL_WIDTH, TERMINAL_HEIGHT);
			ofSetWindowPosition(440, 200);
			break;

	}
}

// - - - DRAWING - - -

void SPreview::startedDrawing() {
	isDrawing = true;
	ofSetFrameRate(SERIAL_FRAMERATE);
	serial->flush();
	
	if (useProgressIndicator) {
		showProgressWindow();
	}
	printf("startDrawing() called\n");
}

void SPreview::stoppedDrawing() {
	isDrawing = false;
	ofSetFrameRate(NORMAL_FRAMERATE);
	
	if (useProgressIndicator) {
		closeProgressWindow();
		useProgressIndicator = false;
	}	
	printf("stoppedDrawing() called\n");
}

bool SPreview::isCurrentlyDrawing() {
	return isDrawing;
}

SPoint SPreview::getScalingVector() {
	float factor = drawingArea.x/ofGetWidth();
	return SPoint(factor, factor);
}

SPoint SPreview::getDrawingArea() {
	return drawingArea;
}

// - - -
SSerial* SPreview::getSerialConnection() {
	return serial;
}

// - - - PLOT EVERYTHING - - -
void SPreview::plotEverything() {

	vector<SPoint> allPoints = vector<SPoint>();
	
	//go through all items and collect their points...
	//5 points will get you a hat, 20 points a stereo
	//and 100 points will get a huge cuddly toy
	for (int i = 0; i < items.size(); i++) {
		items[i]->giveAllPoints(allPoints);
	}
	
	printf("WE HAVE %i NUMBER OF POINTS\n", (int) allPoints.size());
	
	serial->sendMultipleMove(allPoints);
	useProgressIndicator = true;
	startedDrawing();
	numPoints = allPoints.size();
	
}

void SPreview::showProgressWindow() {
	
	progressWindow = [[NSWindow alloc] initWithContentRect:NSMakeRect(500, 500, 500, 200)
																							 styleMask: (NSResizableWindowMask | NSClosableWindowMask | NSTitledWindowMask)
																								 backing:NSBackingStoreBuffered
																									 defer:FALSE];
	
	progressIndicator = [[NSProgressIndicator alloc] initWithFrame:NSMakeRect(50, 150, 400, 25)];
	[progressIndicator setStyle:NSProgressIndicatorBarStyle];
	[progressIndicator setIndeterminate:FALSE];
	[progressIndicator setMinValue:0];
	[progressIndicator setMaxValue:100];
	[progressIndicator setDoubleValue:0];
	
	[[progressWindow contentView] addSubview:progressIndicator];
	[progressWindow makeKeyAndOrderFront:nil];
	
	[progressWindow release];
	
}

void SPreview::closeProgressWindow() {

	[progressWindow close];
}

void SPreview::setPointsDone(int i) {
	pointsDone = i;
	
}

void SPreview::updateProgressIndicator() {
	
	double progress = (pointsDone/(double)numPoints) * 100.0;

	[progressIndicator setDoubleValue:progress];
	printf("progress set to %f\n", progress);
}

void SPreview::setUseProgressIndicator(bool b) {
	useProgressIndicator = b;
}




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
	audioNeeded = false;
	
	//set drawing areas...
 		
	//instantiate serial
	serial = new SSerial();
	
	//now instantiate commander, passing serial pointer
	commander = new SCommand(serial);
	
	//instantiate terminal, passing commander pointer
	terminal = new STerm(commander);
	
	setLayout(A3LANDSCAPE);
	setViewMode(PREVIEW);
	
	//set up audio
	//this is a very minimal mono setup
	ofSoundStreamSetup(0,1,this, 44100, 256, 1);	
	
	//init menuController, this is used for a few things here and there...
	menuController = [[SMenuController alloc] init];
														
	
	//now check to see if serial was set up...
	//if not disable plotting...
	[menuController enablePlot:serial->isConnected()];
	
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
			ofTranslate(-currentDrawingArea.x/2.5, -currentDrawingArea.y/2.5, ztrans);
			
			//draw the drawing area...
			ofNoFill();
			ofSetColor(0, 0, 0);
			ofRect(0, 0, currentDrawingArea.x, currentDrawingArea.y);
			
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
		// - to zoom out 
		// = to zoom in
		switch (key) {
			case 45:
				ztrans-= 100;
				break;
			case 61:
				ztrans+= 100;
				break;

		}
		
	}

	printf("ztrans = %i\n", ztrans);
	
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

void SPreview::addAudioClipItem() {
	items.push_back(new SAudioClip(idc++));
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
			ofSetWindowShape(currentWindowShape.x, currentWindowShape.y);
			ofSetWindowPosition(50, 50);
			ofSetWindowTitle("Preview");
			break;
		case TERMINAL:
			mode = TERMINAL;
			ofSetWindowShape(TERMINAL_WIDTH, TERMINAL_HEIGHT);
			ofSetWindowPosition(440, 200);
			ofSetWindowTitle("Terminal");
			break;

	}
}

void SPreview::setLayout(int layout) {

	switch (layout) {
		case A4PORTRAIT:
			currentWindowShape = SPoint(PREVIEW_A4_PORTRAIT_WIDTH, PREVIEW_A4_PORTRAIT_HEIGHT);
			currentDrawingArea = drawingAreaA4Portrait;
			ztrans = ZTRANS_A4_PORTRAIT;
			break;
		case A4LANDSCAPE:
			currentWindowShape = SPoint(PREVIEW_A4_LANDSCAPE_WIDTH, PREVIEW_A4_LANDSCAPE_HEIGHT);
			currentDrawingArea = drawingAreaA4Landscape;
			ztrans = ZTRANS_A4_LANDSCAPE;
			break;
		case A3PORTRAIT:
			currentWindowShape = SPoint(PREVIEW_A3_PORTRAIT_WIDTH, PREVIEW_A3_PORTRAIT_HEIGHT);
			currentDrawingArea = drawingAreaA3Portrait;
			ztrans = ZTRANS_A3_PORTRAIT;
			break;
		case A3LANDSCAPE:
			currentWindowShape = SPoint(PREVIEW_A3_LANDSCAPE_WIDTH, PREVIEW_A3_LANDSCAPE_HEIGHT);
			currentDrawingArea = drawingAreaA3Landscape;
			ztrans = ZTRANS_A3_LANDSCAPE;
			break;

		default:
			break;
	}
	
	//switch to preview if we are not already in it...
	setViewMode(PREVIEW);
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
	float factor = currentDrawingArea.x/ofGetWidth();
	return SPoint(factor, factor);
}

SPoint SPreview::getDrawingArea() {
	return currentDrawingArea;
}

// - - -
SSerial* SPreview::getSerialConnection() {
	return serial;
}

// - - - PLOT EVERYTHING - - -
void SPreview::plotEverything() {
	
	//don't try and plot something if we don't have the plotter connected
	if (serial->isConnected()) {

		vector<SPoint> allPoints = vector<SPoint>();
		
		//go through all items and collect their points...
		//5 points will get you a hat, 20 points a stereo
		//and 100 points will get a huge cuddly toy
		for (int i = 0; i < items.size(); i++) {
			items[i]->giveAllPoints(allPoints);
		}
			
		serial->sendMultipleMove(allPoints);
		useProgressIndicator = true;
		startedDrawing();
		
	}
	
}

void SPreview::cancelDrawing() {
	vector<SPoint> cancelPoints;
	cancelPoints.push_back(SPoint(PEN_UP_POINT, 0));
	cancelPoints.push_back(SPoint(CHANGE_DELAY_POINT, 7));
	cancelPoints.push_back(SPoint(0, 0));
	cancelPoints.push_back(SPoint(CHANGE_DELAY_POINT, 16));
	serial->sendMultipleMove(cancelPoints);
	[progressWindow close];
}

/*
 - - - PROGRESS WINDOW - - -
 */

void SPreview::showProgressWindow() {
	
	progressWindow = [[NSWindow alloc] initWithContentRect:NSMakeRect(500, 500, 500, 90)
																							 styleMask: (NSResizableWindowMask | NSClosableWindowMask | NSTitledWindowMask)
																								 backing:NSBackingStoreBuffered
																									 defer:FALSE];
	
	progressIndicator = [[NSProgressIndicator alloc] initWithFrame:NSMakeRect(25, 40, 400, 25)];
	
	//set the indicator to look nice...
	[progressIndicator setStyle:NSProgressIndicatorBarStyle];
	[progressIndicator setIndeterminate:FALSE];
	[progressIndicator setMinValue:0];
	[progressIndicator setMaxValue:100];
	[progressIndicator setDoubleValue:0];
	
	percentageLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(430, 38, 50, 25)];
	
	[percentageLabel setEditable:FALSE];
	[percentageLabel setSelectable:FALSE];
	[percentageLabel setDrawsBackground:FALSE];
	[percentageLabel setBezeled:FALSE];
	[percentageLabel setBordered:FALSE];
	
	errorLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(30, 10, 300, 25)];
	
	[errorLabel setEditable:FALSE];
	[errorLabel setSelectable:FALSE];
	[errorLabel setDrawsBackground:FALSE];
	[errorLabel setBezeled:FALSE];
	[errorLabel setBordered:FALSE];
	[errorLabel setStringValue:@"hello"];
	
	NSButton* stopButton = [[NSButton alloc] initWithFrame:NSMakeRect(350, 5, 80, 30)];
	[stopButton setBezelStyle:NSRoundedBezelStyle];
	[stopButton setTitle:@"Cancel"];
		
	[stopButton setTarget:menuController];
	[stopButton setAction:@selector(cancelDrawing:)];
		
	[[progressWindow contentView] addSubview:stopButton];
	[[progressWindow contentView] addSubview:errorLabel];
	[[progressWindow contentView] addSubview:percentageLabel];
	[[progressWindow contentView] addSubview:progressIndicator];
	[progressWindow makeKeyAndOrderFront:nil];
}

void SPreview::closeProgressWindow() {

	[progressWindow close];
	printf("closed progress window\n");
}

void SPreview::setPointsDone(int i) {
	pointsDone = i;	
}

void SPreview::setNumPoints(int i) {
	numPoints = i;
}

void SPreview::updateProgressIndicator() {
	
	double progress = (pointsDone/(double)numPoints) * 100.0;

	[progressIndicator setDoubleValue:progress];
	[percentageLabel setIntValue:round(progress)];
		
	string ps = ofToString(progress, 1) + "%";
	NSString* percentageString = [[NSString alloc] initWithCString:ps.c_str()];
	
	[percentageLabel setStringValue:percentageString];
}

void SPreview::setUseProgressIndicator(bool b) {
	useProgressIndicator = b;
}

void SPreview::writeProgressErrorMessage(string message) {
	[errorLabel setStringValue:[[NSString alloc] initWithCString:message.c_str()]];
}

// - - - AUDIO - - -

void SPreview::audioReceived(float* input, int bufferSize, int nChannels) {

	if (audioNeeded) {
		((SAudioClip*)items[fid])->audioReceived(input);
	}
	
}

void SPreview::setAudioNeeded(bool b) {
	audioNeeded = b;	
}


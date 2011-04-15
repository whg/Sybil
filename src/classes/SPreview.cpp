#include "SPreview.h"


@class SItemController;

// - + - DECONSRUCTOR - + -
SPreview::~SPreview() {
	
	//delete all items
	for (int i = 0; i < items.size(); i++) {
		delete items[i];
	}
	
	//delete the terminal
	delete terminal;
}


// - + - SETUP - + -
void SPreview::setup(){
	
	//set up all oF things...
	ofBackground(255, 255, 255);
	ofSetBackgroundAuto(true);
	ofSetFrameRate(25);
	ofEnableSmoothing();
	ofEnableAlphaBlending();

	
	idc = 0;
	fid = -1;
	ztrans = 0;
	
	//instantiate terminal
	terminal = new STerm();
	
	//start with preview
	mode = TERMINAL;
	
	//set up cocoa part - do this last
	NSApplicationMain(0, NULL);

}

// - + - UPDATE - + -
void SPreview::update(){
}

// - + - DRAW - + -
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


// - + - KEYS - + -
void SPreview::keyPressed(int key){
	
	//send the keypresses to the terminal
	if (mode == TERMINAL) {
		terminal->keyPressed(key);
	}

}

void SPreview::keyReleased(int key){
	
}

// - + - MOUSE - + -
void SPreview::mouseMoved(int x, int y){
	for (int i = 0; i < items.size(); i++) {
		if(items[i]->setCursorType(x, y)) {
			break;
		}
	}
}

void SPreview::mouseDragged(int x, int y, int button){
	for (int i = 0; i < items.size(); i++) {
		items[i]->cursor(x, y);
	}
	
	if (button == 2) {
		ztrans = x-100;
		printf("ztrans = %i", ztrans);
	}
}

void SPreview::mousePressed(int x, int y, int button){
	for (int i = 0; i < items.size(); i++) {
		items[i]->setCurrentParams(x, y);
		if (items[i]->setActionType(x, y, ++button)) {
			break;
		}
	}
	
	//this is so only one is in focus at any time
	for (int i = 0; i < items.size(); i++) {
		items[i]->setFocus(false);
	}
	if (fid != -1) items[fid]->setFocus(true);
}

void SPreview::mouseReleased(int x, int y, int button){
	for (int i = 0; i < items.size(); i++) {
		items[i]->resetCursorType();
	}
}


void SPreview::addTextItem() {
	items.push_back(new SText(idc++));
	
}

void SPreview::addImageItem() {
	items.push_back(new SImage(idc++));
	
}

void SPreview::removeItem(int i) {

	for (int j = 0 ; j < items.size(); j++) {
		if (items[j]->uid == i) {
			delete items[j];
			items.erase(items.begin()+j);
			break;
		}
	}
}

void SPreview::setMode(int m) {
	switch (m) {
		case 0:
			mode = PREVIEW;
			break;
		case 1:
			mode = TERMINAL;
			break;

	}
}
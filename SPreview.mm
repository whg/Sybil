#include "SPreview.h"

// - + - DECONSRUCTOR - + -
SPreview::~SPreview() {
	for (int i = 0; i < t.size(); i++) {
		delete t[i];
	}
}


// - + - SETUP - + -
void SPreview::setup(){
	
	ofBackground(255, 255, 255);
	ofSetBackgroundAuto(true);
	ofSetFrameRate(50);
	ofEnableSmoothing();
	
	idc = 0;
	
	t.push_back(new SText(idc++));
		
	t[0]->setText("hello hello hello hello");
	
	//set up interface - do this last
	NSApplicationMain(0, NULL);

}

// - + - UPDATE - + -
void SPreview::update(){
}

// - + - DRAW - + -
void SPreview::draw(){
	
	ofSetColor(0, 0, 0);
	for (int i = 0; i < t.size(); i++) {
		t[i]->draw();
	}

}

void SPreview::setFocus(int i) {
	fid = i;
}


//- + - KEYS - + -
void SPreview::keyPressed(int key){
	printf("%i", key);
	switch (key) {
		case 'a':
			//t->setText("ASDF ADF AS REAF ASDF ADFS");
			break;

		default:
			break;
	}
}

void SPreview::keyReleased(int key){

}

//- + - MOUSE - + -
void SPreview::mouseMoved(int x, int y){
	for (int i = 0; i < t.size(); i++) {
		t[i]->setCursorType(x, y);
	}
}

void SPreview::mouseDragged(int x, int y, int button){
	for (int i = 0; i < t.size(); i++) {
		t[i]->cursor(x, y);
	}
}

void SPreview::mousePressed(int x, int y, int button){
	for (int i = 0; i < t.size(); i++) {
		t[i]->setCurrentParams(x, y);
		t[i]->setCursorType(x, y);
		t[i]->setActionType(x, y, ++button);
	}
}

void SPreview::mouseReleased(int x, int y, int button){
	for (int i = 0; i < t.size(); i++) {
		t[i]->resetCursorType();
	}
}



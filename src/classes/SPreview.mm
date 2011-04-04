#include "SPreview.h"

// - + - DECONSRUCTOR - + -
SPreview::~SPreview() {
	for (int i = 0; i < items.size(); i++) {
		delete items[i];
	}
}


// - + - SETUP - + -
void SPreview::setup(){
	
	ofBackground(255, 255, 255);
	ofSetBackgroundAuto(true);
	ofSetFrameRate(50);
	ofEnableSmoothing();
	
	idc = 0;
	fid = -1;
	
	items.push_back(new SText(idc++));
	
	//items.push_back(new SText(idc++));
	//items.push_back(new SText(idc++));
		
//	items[0]->setText("hello hello hello hello");
	
	//set up interface - do this last
	NSApplicationMain(0, NULL);

}

// - + - UPDATE - + -
void SPreview::update(){
}

// - + - DRAW - + -
void SPreview::draw(){
	
	ofSetColor(0, 0, 0);
	for (int i = 0; i < items.size(); i++) {
		items[i]->draw();
	}

}

void SPreview::setFocus(int i) {
	fid = i;
}

int SPreview::getFocus() {
	return fid;
}

void SPreview::setText(int i, string text) {
	//items[i]->setText(text);
	tt = "hello";
	cout << "i = " << i << ", text = " << text << endl;
}


// - + - KEYS - + -
void SPreview::keyPressed(int key){
	printf("key = %i\n", key);
	switch (key) {
		case 'a':
			//t->setText("ASDF ADF AS REAF ASDF ADFS");
			break;

		default:
			break;
	}
}

void SPreview::keyReleased(int key){
	setText(0, "hello method");
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
}

void SPreview::mousePressed(int x, int y, int button){
	for (int i = 0; i < items.size(); i++) {
		items[i]->setCurrentParams(x, y);
		//items[i]->setCursorType(x, y);
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

void SPreview::hello() {
	printf("hello\n");
}


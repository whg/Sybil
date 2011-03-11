#include "SPreview.h"

// - + - DECONSRUCTOR - + -
SPreview::~SPreview() {
	delete t;
}


// - + - SETUP - + -
void SPreview::setup(){
	
	ofBackground(255, 255, 255);
	ofSetBackgroundAuto(true);
	ofSetFrameRate(50);
	ofEnableSmoothing();
	
	t = new SText();
	t->setAll("hello hello hello hello e e e hello hello", 100, 100, 600, 200);
	
	//t->setText("hello hello hello hello");
	
	//set up interface - do this last
	NSApplicationMain(0, NULL);

}

// - + - UPDATE - + -
void SPreview::update(){
}

// - + - DRAW - + -
void SPreview::draw(){
	
	ofSetColor(0, 0, 0);
	t->draw();

}

void SPreview::setText(string s) {
	tt = s;
	t->setText(tt);

}


//- + - KEYS - + -
void SPreview::keyPressed(int key){
	printf("%i", key);
	switch (key) {
		case 'a':
			t->setText("ASDF ADF AS REAF ASDF ADFS");
			break;

		default:
			break;
	}
}

void SPreview::keyReleased(int key){

}

//- + - MOUSE - + -
void SPreview::mouseMoved(int x, int y){
	t->cursor(x, y, 0);
}

void SPreview::mouseDragged(int x, int y, int button){
	button++;
	t->cursor(x, y, ++button);
}

void SPreview::mousePressed(int x, int y, int button){
	t->setMouseOffset(x, y);
	t->cursor(x, y, ++button);
	//t->mouseDown();
}

void SPreview::mouseReleased(int x, int y, int button){
	//t->setMouseOffset(0, 0, false);
	t->mouseUp();
}



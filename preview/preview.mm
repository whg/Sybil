#include "GLee.h"
#import <Cocoa/Cocoa.h>
#include "preview.h"

// - + - DECONSRUCTOR - + -
preview::~preview() {

}


// - + - SETUP - + -
void preview::setup(){
	
	printf("%f", oneDecimalPoint(0.9875));

	//set up interface - do this last
	NSApplicationMain(0, NULL);

}

// - + - UPDATE - + -
void preview::update(){

}

// - + - DRAW - + -
void preview::draw(){

}


//- + - KEYS - + -
void preview::keyPressed(int key){

}

void preview::keyReleased(int key){

}

//- + - MOUSE - + -
void preview::mouseMoved(int x, int y ){
}

void preview::mouseDragged(int x, int y, int button){
}

void preview::mousePressed(int x, int y, int button){
}

void preview::mouseReleased(int x, int y, int button){
}



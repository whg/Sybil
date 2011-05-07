/*
 *  SAudioClip.cpp
 *  Sybil
 *
 *  Created by Will Gallia on 07/05/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

#include "SAudioClip.h"

SAudioClip::SAudioClip(int i)
: SItem(i){

	dim = SPoint(1000, 200);
	points = vector<SPoint>();
	rawAudio = vector<float>();
	rawAudio.push_back(0);
	halt = false;

	//this is a fix to a bug that i don't quite understand...
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	
	windowController = [[SAudioClipController alloc] initWithWindowNibName:@"SAudioClipWindow"];
	[windowController setUid: i];
	[windowController setParent:this];
	[windowController showWindow:nil];
	[pool drain];

	updateWindow();
	
}

SAudioClip::~SAudioClip() {
	[windowController release];
}

void SAudioClip::update() { }

void SAudioClip::updateWindow() {
	
	[windowController updatePosFields:pos.x:pos.y];
	[windowController updateDimFields:dim.x :dim.y];
	
}

void SAudioClip::draw() {
		
	scaleAudio();
	
	ofPushMatrix();
	ofTranslate(pos.x, pos.y);
	
	if (focus) drawBoundingBox();
	
	ofSetColor(10, 10, 10);
	ofLine(0, dim.y/2, dim.x, dim.y/2);
	
	for (int i = 0; i < points.size() -1; i++) {
		ofLine(points[i].x, points[i].y, points[i+1].x, points[i+1].y);
	}
	
	ofPopMatrix();
		
}

void SAudioClip::audioReceived(float* input) {
	
	//add the first sample to the array, discard the rest
	rawAudio.push_back(input[0]);
}

void SAudioClip::scaleAudio() {
	
	points.clear();
	
	float xscale = (float)dim.x/rawAudio.size();
	
	for (int i = 0; i < rawAudio.size(); i++) {
		//scale the height so it fits nicely in the box...		
		//scale x point to fit x dimension... and...
		//convert all points to SPoints, so they can be plotted
		points.push_back(SPoint(i*xscale, (rawAudio[i]*(dim.y/2))+dim.y/2));
		
	}
		
}

void SAudioClip::reset() {
	rawAudio.clear();
	rawAudio.push_back(0);
}

void SAudioClip::setForDraw() {

	//translate
	for (int i = 0; i < points.size(); i++) {
		points[i]+= pos;
	}
	
	//insert a pen up at begining
	points.insert(points.begin(), SPoint(PEN_UP_POINT, 0));
	//insert pen down when it got to first point
	points.insert(points.begin()+2, SPoint(PEN_DOWN_POINT, 0));
	//add pen up at end
	points.push_back(SPoint(PEN_UP_POINT, 0));
	
}

void SAudioClip::giveAllPoints(vector<SPoint> &p) {

	setForDraw();
	
	for (int i = 0; i < points.size(); i++) {
		p.push_back(points[i]);
	}
}
/*
 *  SImage.cpp
 *  Sybil
 *
 *  Created by Will Gallia on 21/03/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */



#include "SImage.h"

SImage::SImage(int i, string file)
:SItem(i){
	printf("constructed SImage\n");
	
		
	//init variables
	imageSet = false;
	imgRatio = 0;
	showImage = true;
	fixAspectRatio = true;

	//image option variables
	baseThreshold = 125; //roughly half 
	numOf = 3; 
	diff = 20;
	minArea = 5;
	doSmoothing = false;
	smoothingRadius = 5;
	
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	windowController = [[SImageController alloc] initWithWindowNibName:@"SImageWindow"];
	
	//do this now so we can delete it if no file is opened
	[windowController setUid: i];
	[windowController setParent:this];
	
	//if it's all good show the window
	[windowController showWindow:nil];
	[pool drain];
		
	//load the image
	loadImage(file);
	
	//do an update
	updateWindow();

	
}

SImage::SImage() {
	
}


SImage::~SImage() {
	
	if (imageSet) {
		//delete baseImage;
	}
	
	printf("desconstructed from SImage\n");
	[windowController release];
}

void SImage::loadImage(string path) {
	
	//load images
	bool b = baseImage.loadImage(path);
	cout << "loaded image = " << b << endl;
	
	//set dimension variables
	int width = baseImage.width;
	int height = baseImage.height;
	imgRatio = height/(float)width;
	
	//set dimension variables so all are in check...
	dim.set(width, height);
	
	imageSet = true;
	
	findPoints();
	
}

void SImage::draw() {
	
	//this is an option
	if (fixAspectRatio) dim.y = dim.x*imgRatio;
	
	//don't try and draw an image that hasn't been loaded
	if (imageSet) {
		
		ofPushMatrix();
		ofTranslate(pos.x, pos.y);
		
		if(focus) drawBoundingBox();
		
		//this shows original image
		if (showImage) {
			ofFill();
			ofSetColor(0xffffff);
			colourImg.draw(0, 0, dim.x, dim.y);
		}
		
		//this shows the lines...
		else {
			
		//	ofNoFill();
//			ofSetColor(0x111111);
//			
//			for (int i = 0; i < points.size(); i++) {
//				if (points[i].x == PEN_UP_POINT) ofNextContour(true);
//				else ofVertex(points[i].x, points[i].y);
//			}
			
			ofBeginShape();
			
			for (int i = 0; i < points.size(); i++) {
				
				ofNoFill();
				ofSetColor(0, 0, 0);
				
				if (points[i].x == PEN_UP_POINT) {
					ofNextContour(true);
				} 
				else if (points[i].x == PEN_DOWN_POINT) {}
				else {
					ofVertex(points[i].x, points[i].y);
					
					//ofNoFill();
					//ofSetColor(50, 100, 200);
					//ofCircle(textPoints[i].x, textPoints[i].y, 1);
				}
				
				
			}
			
			ofEndShape(true);
			
		}
		
		ofPopMatrix();
		
	}
	
}

// - - -
// uses openCV to find blobs and the contours of those blobs
// all coordinates are in one big STL vector...
// points with (PEN_UP_POINT, 0) are for separate contours
void SImage::findPoints() {

	initialPoints.clear();
	
	//do this now, so the dimensions are correct
	if (fixAspectRatio) dim.y = dim.x*imgRatio;
	
	//allocate space for openCV space with correct dimensions
	colourImg.clear();
	grayImg.clear();
	colourImg.allocate(dim.x, dim.y);
	grayImg.allocate(dim.x, dim.y);
	
	//set the image to the right dimensions
	ofImage resizedImg;
	resizedImg.setFromPixels(baseImage.getPixels(), baseImage.width, baseImage.height, OF_IMAGE_COLOR, true);
	resizedImg.resize(dim.x, dim.y);
	colourImg.setFromPixels(resizedImg.getPixels(), dim.x, dim.y);
	
	// - - find the points - -
	
	//this loop is for the each contour
	for (int n = 0; n < numOf; n++) {
		grayImg = colourImg;
		grayImg.threshold(baseThreshold+(n*diff));
		
		contourFinder.findContours(grayImg, minArea, 50000, 100, true, true);
		
		//this loob is for blobs
		for (int i = 0; i < contourFinder.nBlobs; i++) {
			
			initialPoints.push_back(SPoint(PEN_UP_POINT, 0));
			
			//push first position
			initialPoints.push_back(SPoint(contourFinder.blobs[i].pts[0]));
			
			initialPoints.push_back(SPoint(PEN_DOWN_POINT, 0));
			
			//this loop is for points within a blob
			//add all the points... NB starting at 1 as we have already added 0
			for (int j = 1; j < contourFinder.blobs[i].pts.size(); j++) {
				initialPoints.push_back(SPoint(contourFinder.blobs[i].pts[j]));
			}
			
			//add last point...
			initialPoints.push_back(SPoint(contourFinder.blobs[i].pts[0]));
		}
		
	} //end for
	
	
	// - - now do the custom bits - - 
	
	points.clear();
	
	//smoothed points...
	if (doSmoothing) {
		
		
		//this is an implementation of McMasters slide averaging algorithm
		//it was done a while ago and it looks pretty messy...
		
		//set smoothing radius, using n as it looks a little neater...
		int n = smoothingRadius;
		
		for (int i = 0; i < initialPoints.size()-n; i++) {
			if (initialPoints[i].x < 0) {
				points.push_back(initialPoints[i]);
			}
			
			//this is so we don't get lines coming out of nowhere
			//it looks ahead to see if the next contour is n number of steps ahead
			bool a = false;
			for (int j = 0; j < n; j++) {
				if (initialPoints[i+j].x < 0) {
					a = true;
				}				
			}
			
			if (a) continue;
			else {
				int j = 0;
				ofPoint av = ofPoint(0, 0);
				while (j < n) {
					if (initialPoints[i+j].x >= 0) {
						av.x+= initialPoints[i+j].x;
						av.y+= initialPoints[i+j].y;
					}
					else {
						n++;
					}
					j++;
				}
				av/= n;
				points.push_back(SPoint(av.x, av.y));
			}
		} //end for 
	} //end if
	
	
	//for unsmoothed points just copy the whole thing
	else {
		points = initialPoints;
	}
	
}

void SImage::update() {

	if (!showImage) findPoints();
	
}


void SImage::updateWindow() {
	
	update();
	
	[windowController updatePosFields:pos.x:pos.y];
	[windowController updateDimFields:dim.x :dim.y];
}


// - - - SETTERS - - -

void SImage::setBaseThreshold(float v) {
	baseThreshold = v;
}

void SImage::setNumberOfLines(int v) {
	numOf = v;
}

void SImage::setMinArea(float v) {
	minArea = v;
}

void SImage::enableSmoothing(bool b) {
	doSmoothing = b;
}

void SImage::setSmoothingRadius(int v) {
	smoothingRadius = v;
}

void SImage::setLineSpacing(float v) {
	diff = v;
}

void SImage::setFixAspectRatio(bool b) {
	fixAspectRatio = b;
}

void SImage::drawOriginalImage(bool b) {
	showImage = b;
}
	
// - - - GIVE ALL POINTS - - -
void SImage::giveAllPoints(vector<SPoint> &p) {

	for (int i = 0; i < points.size(); i++) {
		p.push_back(points[i]);
	}
	
}


/*
 *  SImage.cpp
 *  Sybil
 *
 *  Created by Will Gallia on 21/03/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */



#include "SImage.h"

SImage::SImage(int i)
:SItem(i){
	printf("constructed SImage\n");
	
	fixAspectRatio = true;
		
	//init variables
	imageSet = false;
	imgRatio = 0;
	
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	
	windowController = [[SImageController alloc] initWithWindowNibName:@"SImageWindow"];
	
	//do this now so we can delete it if no file is opened
	[windowController setUid: i];
	[windowController setParent:this];
	
	//open window to open file
	[windowController openFile:nil];
	
	//if it's all good show the window
	[windowController showWindow:nil];
	[pool drain];
	
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
	
	//load image
	baseImage.loadImage(path);
	
	//set dimension variables
	int width = baseImage.width;
	int height = baseImage.height;
	imgRatio = height/(float)width;
	
	//allocate space for openCV space
	colourImg.allocate(width, height);
	grayImg.allocate(width, height);
	
	//set openCV image
	colourImg.setFromPixels(baseImage.getPixels(), width, height);
	
	imageSet = true;
	
}

void SImage::draw() {
	
	//this is an option
	if (fixAspectRatio) dim.y = dim.x*imgRatio;
	
	//don't try and draw an image that hasn't been loaded
	if (imageSet) {
		
		ofPushMatrix();
		ofTranslate(pos.x, pos.y);
		
		if(focus) drawBoundingBox();
		ofFill();
		ofSetColor(0xffffff);
		baseImage.draw(0, 0, dim.x, dim.y);
		
		ofPopMatrix();
		
	}
	
}

// - - -
void SImage::findInitPoints() {

	initPoints.clear();
	
	//this loop is for the each contour
	for (int n = 0; n < numOf; n++) {
		grayImg = colourImg;
		grayImg.threshold(baseThreshold+(n*diff));
		
		contourFinder.findContours(grayImg, minArea, 50000, 100, true, true);
		
		//this loob is for blobs
		for (int i = 0; i < contourFinder.nBlobs; i++) {
			//this loop is for points within a blob
			for (int j = 0; j < contourFinder.blobs[i].pts.size(); j++) {
				SPoint p(0,0);
				p.x = round(contourFinder.blobs[i].pts[j].x);
				p.y = round(contourFinder.blobs[i].pts[j].y);
				points.push_back(p);
			}
			//put in pen up vector... this is for drawing only
			//points.push_back(ofPoint(-1, 0));
		}
		
		
	}
	
}

void SImage::updateWindow() {
	[windowController updatePosFields:pos.x:pos.y];
	[windowController updateDimFields:dim.x :dim.y];
}
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
	
	//init variables
	imageSet = false;
	baseHeight = baseWidth = 0;
	imgRatio = 0;
	
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	
	windowController = [[SImageController alloc] initWithWindowNibName:@"SImageWindow"];
	[windowController setUid: i];
	[windowController setParent:this];
	[windowController showWindow:nil];
	//open window to open file
	[windowController openFile:nil];
	[pool drain];
	
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
	
	baseImage.loadImage(path);
	baseWidth = baseImage.width;
	baseHeight = baseImage.height;
	imgRatio = baseHeight/(float)baseWidth;
	imageSet = true;

}

void SImage::draw() {
	
	dim.y = dim.x*imgRatio;
	
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
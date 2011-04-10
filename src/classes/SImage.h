/*
 *  SImage.h
 *  Sybil
 *
 *  Created by Will Gallia on 21/03/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

#ifndef _SIMAGE
#define _SIMAGE

@class SImageController;

#include "ofMain.h"
//#include "SItem.h"
#import <Cocoa/Cocoa.h>
#import "SImageController.h"
#include "ofxOpenCv.h"


class SImage : public SItem {
	
private:
	ofImage baseImage;
	//int baseWidth, baseHeight;
	
	//ofx openCV types
	ofxCvGrayscaleImage colourImg, grayImg;
	ofxCvContourFinder contourFinder;
	
	//these will hold the points... integer coordinates (SPoint)...
	vector<SPoint> initPoints, points;
	
	
	float imgRatio;
	bool imageSet;
	SImageController *windowController;
	
	float baseThreshold, numOf, diff, minArea;
	
	void findInitPoints();
	
	
public:
	SImage();
	SImage(int i);
	~SImage();
	
	void draw();
	
	void loadImage(string path);
	
	void updateWindow();
	
	bool fixAspectRatio, showImage;
	
};


#endif
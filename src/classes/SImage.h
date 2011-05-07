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
#import <Cocoa/Cocoa.h>
#import "SImageController.h"
#include "STypes.h"
#include "ofxOpenCv.h"


class SImage : public SItem {
	
private:
	ofImage baseImage;
	
	//ofx openCV types
	ofxCvColorImage colourImg;
	ofxCvGrayscaleImage grayImg;
	ofxCvContourFinder contourFinder;
	
	//these will hold the points... integer coordinates (SPoint)...
	vector<SPoint> initialPoints, points;
	
	float imgRatio;
	bool imageSet;
	SImageController *windowController;
	
	int numOf, smoothingRadius;
	float baseThreshold, diff, minArea;
	bool doSmoothing;
	bool fixAspectRatio, showImage;
	int skipPoints;
	
	string currentStyle;
	float styleParameter;

	void findPoints();
	
public:
	SImage();
	SImage(int i, string file);
	~SImage();
	
	void draw();
	
	void loadImage(string path);
	
	void update();
	void updateWindow();
	
	//setters
	void setBaseThreshold(float v);
	void setNumberOfLines(int v);
	void setMinArea(float v);
	void enableSmoothing(bool b);
	void setSmoothingRadius(int v);
	void setLineSpacing(float v);
	void setFixAspectRatio(bool b);
	void drawOriginalImage(bool b);
	void setSkipPoints(int i);
	void setStyle(string s);
	void setStyleParameter(float v);
	
	void enableStyleSlider(BOOL show);
	
	void giveAllPoints(vector<SPoint> &p);

};


#endif
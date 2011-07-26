/*
 *  SPreview.h
 *  Sybil
 *
 *  Created by Will Gallia on 06/02/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

#ifndef _SPREVIEW
#define _SPREVIEW

#include "GLee.h"
#import <Cocoa/Cocoa.h>
#include "ofMain.h"
#include "SItem.h"
#include "SText.h"
#include "SImage.h"
#include "SAudioClip.h"
#include "STerm.h"
#include "SConstants.h"
#include "SSerial.h"
#include "SCommand.h"
#include "STypes.h"
#import "SMenuController.h"

class SItem;
class SImage;
class SAudioClip;
@class SItemController;
class STerm;
class SCommand;
@class SMenuController;

class SPreview : public ofBaseApp {
	
private:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void audioReceived(float* input, int bufferSize, int nChannels);
	
	int idc; //id counter
	int fid; //focused id
	bool isDrawing;
	int ztrans;
	bool audioNeeded;
	
	viewModes mode;
	layoutTypes layout;
	
	SPoint currentWindowShape, currentDrawingArea;
	
	//pointers
	STerm* terminal;
	SCommand* commander;
	SSerial* serial;
	
	//these are where all the items are stored...
	vector<SItem *> items;
	
	SMenuController* menuController;
	int currentLayout;
	
	//things for the progress window
	unsigned int numPoints, pointsDone;
	bool useProgressIndicator;
	NSWindow* progressWindow;
	NSProgressIndicator* progressIndicator;
	NSTextField* percentageLabel, *errorLabel;

public:
	
	~SPreview();
	
	void setFocus(int i);
	int getFocus();
	
	void startedDrawing();
	void stoppedDrawing();
	bool isCurrentlyDrawing();
	
	void setLayout(int layout);
	void setViewMode(int m);
	
	void addTextItem();
	void addImageItem(string file);
	void addAudioClipItem();
	void removeItem(int i);
	
	SPoint getScalingVector();
	SPoint getDrawingArea();
	
	SSerial* getSerialConnection();
	
	void plotEverything();
	void cancelDrawing();
	
	//progress window stuff
	void showProgressWindow();
	void closeProgressWindow();
	void setNumPoints(int i);
	void setPointsDone(int i);
	void updateProgressIndicator();
	void setUseProgressIndicator(bool b);
	
	void writeProgressErrorMessage(string message);
	
	void setAudioNeeded(bool b);
	
	void changePointsToLayout(vector<SPoint> &points);
	bool checkPointsAreWithinBoundry(vector<SPoint> &points);
};



#endif

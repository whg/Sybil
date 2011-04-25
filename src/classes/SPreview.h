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
#include "STerm.h"
#include "SConstants.h"
#include "SSerial.h"
#include "SCommand.h"

class SItem;
class SImage;
@class SItemController;
class STerm;
class SCommand;

class SPreview : public ofBaseApp {
	
private:
	
	int idc; //id counter
	int fid; //focused id
	bool isDrawing;
	int ztrans;
	
	STerm* terminal;
	SCommand* commander;
	
public:
	
	~SPreview();

	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
			
	void setFocus(int i);
	int getFocus();
//	void setStartedDrawing(bool b);
//	bool getStartedDrawing();
	
	void startedDrawing();
	void stoppedDrawing();
	
	void setViewMode(int m);
			
	//these are where all the items are stored...
	vector<SItem *> items;
	
	void addTextItem();
	void addImageItem(string file);
	void removeItem(int i);
	
	SSerial* serial;
	
	
	viewModes mode;
	
};



#endif

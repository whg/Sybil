/*
 *  SSerial.h
 *  Sybil
 *
 *  Created by Will Gallia on 18/04/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */


#ifndef _SSERIAL
#define _SSERIAL

#include "ofMain.h"
#include "STypes.h"
#include "SPreview.h"

class SPreview;

class SSerial {
	
private:
	ofSerial serial;
	bool readyToSendNext;
	bool finished;
	
	int pc; //point counter
	
	SPreview* previewPtr;
	
	vector<SPoint> points;
	
public:
	SSerial();
	~SSerial();
	
	void update();
	void sendLine(int x0, int y0, int x1, int y1);
	void sendSingleLine(int x0, int y0, int x1, int y1);
	void sendCollection(vector<SPoint> &points);
	void sendMove(int x, int y);
	
	SPoint getPos();
	
	void checkInput();

	
};




#endif
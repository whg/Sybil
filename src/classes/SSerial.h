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
	bool done;
	bool finished;
	
	int pc; //point counter
	
	SPreview* previewPtr;
	
	vector<SPoint> points;
	
	bool multipleMove;
	
	int counter;
	bool sendNext;
	
	vector<unsigned char> readBytes;
	
public:
	SSerial();
	~SSerial();
	
	void setDone(bool b);
	bool isDone();
	
	void update();
	void sendLine(int x0, int y0, int x1, int y1);
	void sendSingleLine(int x0, int y0, int x1, int y1);
	void sendSingleMove(int x, int y);
	
	void sendMove(int t, int x, int y);
	void sendMoveAbs(int x, int y);
	void sendMoveRel(int x, int y);
	
	void sendMultipleMove(vector<SPoint> &points);
	
	bool sendPen(string command);
	void sendDelayChange(int delay_ms);
	
	SPoint getPos();
	
	void checkInput();
	void flush();
	
	int queryDelayed();
	void sendStart();
	int available();
	
	void sendFinish();
	void sendLastLot(bool isLast);
	
	bool checkOKtoSend();
	bool checkSendMore();
	bool checkSendMore(unsigned char byte);
	
};




#endif
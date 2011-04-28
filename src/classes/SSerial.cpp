/*
 *  SSerial.cpp
 *  Sybil
 *
 *  Created by Will Gallia on 18/04/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

#include "SSerial.h"

//constructor
SSerial::SSerial() {
	
	//connect to serial port
	if(serial.setup("/dev/cu.usbserial-A600eI53", 28800)) {
		printf("serial connected\n");
	}
	
	//init variables
	readyToSendNext = true;
	done = true;
	finished = true;
	pc = 0;
	multipleMove = false;
	
	previewPtr = (SPreview*) ofGetAppPtr();
	
	//just for good measure...
	serial.flush(true, true);
	serial.setVerbose(true);
}

//destructor
SSerial::~SSerial() {

}

void SSerial::update() {
	
	checkInput();
	
	if (!finished) {
	
		if (pc < points.size()) {
			
			if (readyToSendNext) {
				//sendLine(points[pc].x, points[pc].y, points[pc+1].x, points[pc+1].y);
				sendMove(points[pc].x, points[pc].y);
				printf("sent iteration %i of %i\n", pc, (int) points.size()-1);
				pc++;
				readyToSendNext = false;
			}			
		}
		
		else if (done) {
			printf("we have finished\n");
			finished = true;
			previewPtr->stoppedDrawing();
		}		
		
	}
	
}


void SSerial::sendLine(int x0, int y0, int x1, int y1) {

	//convert to 1 byte
	unsigned char x00 = (unsigned char) x0;
	unsigned char x01 = (unsigned char) (x0>>8);
	unsigned char y00 = (unsigned char) y0;
	unsigned char y01 = (unsigned char) (y0>>8);
	
	
	unsigned char x10 = (unsigned char) x1;
	unsigned char x11 = (unsigned char) (x1>>8);
	unsigned char y10 = (unsigned char) y1;
	unsigned char y11 = (unsigned char) (y1>>8);
	
	//write type
	serial.writeByte((unsigned char) 2);
	
	serial.writeByte(x00);
	serial.writeByte(x01);
	serial.writeByte(y00);
	serial.writeByte(y01);
	serial.writeByte(x10);
	serial.writeByte(x11);
	serial.writeByte(y10);
	serial.writeByte(y11);
	
	
	//these are just for printing out...
	int xs0 = ((x01<<8) | x00);
	int ys0 = ((y01<<8) | y00);	
	int xs1 = ((x11<<8) | x10);
	int ys1 = ((y11<<8) | y10);
	
	printf("wrote via serial %i %i %i %i %i \n", 2, xs0, ys0, xs1, ys1);
	
	setDone(false);
	
}

void SSerial::sendMultipleMove(vector<SPoint> &points) {
		
	//reset
	this->points.clear();
	finished = false;
	pc = 0;
	readyToSendNext = true;
	
	this->points = points;
		
}

void SSerial::checkInput() {
	
	//printf("checking input\n");
	
	if (serial.available() != 0) {
		//printf("no bytes available = %i \n", serial.available());
		
		unsigned char recievedByte = serial.readByte();
		printf("recievedByte = %i\n", (unsigned char) recievedByte);
		
		
		switch (recievedByte) {
			case 56:
				printf("in 56 \n");
				readyToSendNext = true;
				break;
				
			case 64:
				printf("recieved a done\n");
				setDone(true);
				return;

				
			default:
				break;
		}
		
		//now flush
		//serial.flush(true, false);
	}
	
	//setDone(false);

}

void SSerial::sendSingleLine(int x0, int y0, int x1, int y1) {
	
	//convert to 1 byte
	unsigned char x00 = (unsigned char) x0;
	unsigned char x01 = (unsigned char) (x0>>8);
	unsigned char y00 = (unsigned char) y0;
	unsigned char y01 = (unsigned char) (y0>>8);
	
	
	unsigned char x10 = (unsigned char) x1;
	unsigned char x11 = (unsigned char) (x1>>8);
	unsigned char y10 = (unsigned char) y1;
	unsigned char y11 = (unsigned char) (y1>>8);
	
	//write type
	serial.writeByte((unsigned char) 1);
	
	serial.writeByte(x00);
	serial.writeByte(x01);
	serial.writeByte(y00);
	serial.writeByte(y01);
	serial.writeByte(x10);
	serial.writeByte(x11);
	serial.writeByte(y10);
	serial.writeByte(y11);
	
	
	//these are just for printing out...
	int xs0 = ((x01<<8) | x00);
	int ys0 = ((y01<<8) | y00);	
	int xs1 = ((x11<<8) | x10);
	int ys1 = ((y11<<8) | y10);
	
	printf("wrote via serial %i %i %i %i %i \n", 1, xs0, ys0, xs1, ys1);
	setDone(false);
}

void SSerial::sendSingleMove(int x, int y) {
	
	//convert to 1 byte
	unsigned char x00 = (unsigned char) x;
	unsigned char x01 = (unsigned char) (x>>8);
	unsigned char y00 = (unsigned char) y;
	unsigned char y01 = (unsigned char) (y>>8);
	
	
	//write type... move
	serial.writeByte((unsigned char) 3);
	
	serial.writeByte(x00);
	serial.writeByte(x01);
	serial.writeByte(y00);
	serial.writeByte(y01);
	
	//write nothing... fill the array
	for (int i = 0; i < 4; i++) {
		serial.writeByte(0);
	}
	
	
	//these are just for printing out...
	int xs0 = ((x01<<8) | x00);
	int ys0 = ((y01<<8) | y00);	
	
	printf("wrote via serial %i %i %i\n", 3, xs0, ys0);
	
	setDone(false);
	
}

void SSerial::sendMove(int x, int y) {
	
	//convert to 1 byte
	unsigned char x00 = (unsigned char) x;
	unsigned char x01 = (unsigned char) (x>>8);
	unsigned char y00 = (unsigned char) y;
	unsigned char y01 = (unsigned char) (y>>8);
	
	
	//write type... move
	serial.writeByte((unsigned char) 4);
	
	serial.writeByte(x00);
	serial.writeByte(x01);
	serial.writeByte(y00);
	serial.writeByte(y01);
	
	//write nothing... fill the array
	for (int i = 0; i < 4; i++) {
		serial.writeByte(0);
	}
	
	
	//these are just for printing out...
	int xs0 = ((x01<<8) | x00);
	int ys0 = ((y01<<8) | y00);	
	
	printf("wrote via serial %i %i %i\n", 4, xs0, ys0);
	
	setDone(false);
	
}

SPoint SSerial::getPos() {
	
	//let's do this now...
	serial.flush(true, true);

	//write type... move
	serial.writeByte((unsigned char) 5);
	
	//write nothing... fill the array
	for (int i = 0; i < 8; i++) {
		serial.writeByte(0);
	}
		
	//wait until all results are there...
	//don't allow yourself to get into an infinite loop
	//wait until you can count to a big number... 
	
	//NB wait for done byte as well...
	long l = 0;
	while (serial.available() != 5 && l < 99999) { 
		l++;
	}
	
	printf("no bytes available = %i \n", serial.available());

	
	if (l != 99999) {
	
		
		//fetch results
		unsigned char results[4];
		serial.readBytes(results, 4);
		
		//combine the 8bit results to two 16bit shorts
		short int x = (results[0] | (results[1]<<8));
		short int y = (results[2] | (results[3]<<8));
		
		return SPoint(x, y);
	}
	
	setDone(false);
	//this is not possible, ie. the get didn't work
	return SPoint(-1, -1);
	
}

bool SSerial::sendPen(string command) {

	if (command == "up") {
		serial.writeByte((unsigned char) 6);
		for (int i = 0; i < 8; i++) {
			serial.writeByte(0);
		}
		printf("sent pen up\n");
		setDone(false);
		return true;
	}
	else if(command == "down") {
		serial.writeByte((unsigned char) 7);
		for (int i = 0; i < 8; i++) {
			serial.writeByte(0);
		}
		printf("sent pen down\n");
		setDone(false);
		return true;
	}
	
	//if none of the above worked return false
	return false;

}

void SSerial::sendDelayChange(int delay_ms) {
	
	serial.writeByte((unsigned char) 0);
	serial.writeByte((unsigned char) delay_ms);
	for (int i = 0; i < 7; i++) {
		serial.writeByte(0);
	}
	setDone(false);
}

void SSerial::flush() {
	serial.flush(true, true);
}

void SSerial::setDone(bool b) {
	done = b;
	printf("set done with %i\n", b);
}

bool SSerial::isDone() {
	return done;
}

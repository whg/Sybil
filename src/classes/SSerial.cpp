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
	if(serial.setup("/dev/cu.usbserial-A600eI53", 9600)) {
		printf("serial connected\n");
	}
	
	//init variables
	readyToSendNext = true;
	finished = true;
	pc = 0;
	
	previewPtr = (SPreview*) ofGetAppPtr();
	
	//just for good measure...
	serial.flush(true, true);
	
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
				printf("sent iteration %i of %i\n", pc, (int) points.size());
				pc++;
				readyToSendNext = false;
			}
			
		}
		else {
			printf("we have finished\n");
			finished = true;
			previewPtr->setStartedDrawing(false);
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
	
}

void SSerial::sendCollection(vector<SPoint> &points) {
		
	//reset
	this->points.clear();
	finished = false;
	pc = 0;
	readyToSendNext = true;
	
	this->points = points;
	
}

void SSerial::checkInput() {
	
	if (serial.available() != 0) {
		//printf("no bytes available = %i \n", serial.available());
		
		unsigned char recievedByte = serial.readByte();
		//printf("recievedByte = %i\n", (unsigned char) recievedByte);
		
		
		switch (recievedByte) {
			case 56:
				printf("in 56 \n");
				readyToSendNext = true;
				break;
			default:
				break;
		}
		
		//now flush
		serial.flush(true, true);
	}

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
	
}

void SSerial::sendMove(int x, int y) {
	
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
	//this could cause an infinite loop... oh no...
	//hopefully all is good on the microcontroller end... let's hope so anyway
	while (serial.available() != 4) { }
	
	printf("no bytes available = %i \n", serial.available());
	
	//fetch results
	unsigned char results[4];
	serial.readBytes(results, 4);
	
	//combine the 8bit results to two 16bit shorts
	short int x = (results[0] | (results[1]<<8));
	short int y = (results[2] | (results[3]<<8));
	
	return SPoint(x, y);
	
}
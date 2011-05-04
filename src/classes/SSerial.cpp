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
	
	counter = 0;
	sendNext = true;
}

//destructor
SSerial::~SSerial() {

}

void SSerial::update() {
	
	readBytes.clear();
	while (serial.available()) {
		readBytes.push_back(serial.readByte());
	}
	
	if (readBytes.size() > 0) {
		printf("readBytes = ");
		for (int i = 0; i < readBytes.size(); i++) {
			printf("%i ", (int) ((unsigned char) readBytes[i]));
		}
		printf("\n");
	}
	
	
	if (checkSendMore()) {
		
		if (counter < points.size()) {
			sendMoveAbs(points[counter].x, points[counter].y);
			counter++;
		}
		printf("sent %i\n", counter);
		
	}
	
//	if (sendNext) {
//		
//		bool finished = false;
//		
//		for (int i = 0; i < 20; i++) {
//			
//			if ((counter+i) > points.size()) {
//				sendFinish();
//				printf("sent finished\n");
//				finished = true;
//				//now exit loop as we have done all points...
//				break;
//			}
//			
//			sendMoveAbs(points[counter+i].x, points[counter+i].y);
//			printf("sent %i\n", counter+i);
//			
//		}
//		
//		
//		
//		//if (!finished) {
//			//this sees if the next lot of points to be sent is the last lot to be sent...
//			bool ll = ((counter + 20) > points.size());
//			sendLastLot(ll);
//			printf("sent last lot: %i\n", ll);
//			
//			sendStart();
//			printf("sent start\n");
//		//}
//		
//		
//		
//		sendNext = false;
//	}
	
//	if (checkSendMore()) {
//		counter+= 10;
//		sendNext = true;
//		
//	}

	
//	while (serial.available()) {
//		char ch = (char) serial.readByte();
//		int in = (int) ch;
//		printf("char = %c, int = %i\n", ch, in);
//		
////		if (checkSendMore((unsigned char) ch)) {
////			counter+= 10;
////			sendNext = true;
////		}
//	}
	
}


int SSerial::queryDelayed() {
	
	serial.writeByte((unsigned char) SERIAL_STX);
	serial.writeByte((unsigned char) COMMAND_CODE_QUERY_DELAYED);
	
	serial.writeByte((unsigned char) SERIAL_ETX);
	
	long l = 0;
	while (serial.available() != 1 && l < 99999) { 
		l++;
	}
	
	if (l != 99999) {		
		//fetch result
		unsigned char in = serial.readByte();
		
		return (int) in;
	}

	return -1;
}

void SSerial::sendStart() {
	
	serial.writeByte((unsigned char) SERIAL_STX);
	serial.writeByte((unsigned char) COMMAND_CODE_EXECUTE_COMMANDS);
	serial.writeByte((unsigned char) SERIAL_ETX);
}

void SSerial::sendFinish() {
	serial.writeByte((unsigned char) SERIAL_STX);
	serial.writeByte((unsigned char) COMMAND_CODE_FINISH);
	serial.writeByte((unsigned char) SERIAL_ETX);
}

void SSerial::sendLastLot(bool isLast) {
	
	serial.writeByte((unsigned char) SERIAL_STX);
	serial.writeByte((unsigned char) COMMAND_CODE_LAST_LOT);

	if (isLast) {
		serial.writeByte((unsigned char) 1);
	} else {
		serial.writeByte((unsigned char) 0);
	}
	
	serial.writeByte((unsigned char) SERIAL_ETX);
	
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

	this->points.clear();
	this->points = points;
	counter = 0;
	sendNext = true;
	serial.flush(false, true);
		
	for (int i = 0; i < points.size(); i++) {
		printf("x = %i, y = %i\n", points[i].x, points[i].y);
	}
	
	sendMoveAbs(points[counter].x, points[counter].y);
	counter++;
	
}

void SSerial::checkInput() {
	
	//printf("checking input\n");
	
	if (serial.available()) {
		//printf("no bytes available = %i \n", serial.available());
		
		unsigned char recievedByte = serial.readByte();
		printf("recievedByte = %i\n", (unsigned char) recievedByte);
		
		
		switch (recievedByte) {
			
			default:
				break;
		}
		
		//now flush
		//serial.flush(true, false);
	}
	
	//setDone(false);

}

bool SSerial::checkOKtoSend() {
	
	for (int i = 0; i < readBytes.size(); i++) {
		if (readBytes[i] == (unsigned char) RX_BUFFER_FULL) {
			return false;
		}
	}
	
	return true;
	
//	if (serial.available()) {
//		if (serial.readByte() == (unsigned char) RX_BUFFER_FULL) {
//			return false;
//		}
//	}-
//	
//	return true;
}

bool SSerial::checkSendMore() {
	
	for (int i = 0; i < readBytes.size(); i++) {
		if (readBytes[i] == (unsigned char) SEND_FOR_NEXT_COMMANDS) {
			return true;
		}
	}
	
	return false;
	
//	if(serial.available()) {
//		if (serial.readByte() == (unsigned char) RX_SEND_NEXT) {
//			return true;
//		}
//	}
//	return false;
}

bool SSerial::checkSendMore(unsigned char byte) {
	if (byte == (unsigned char) RX_SEND_NEXT) {
		return true;
	}
	return false;
}


void SSerial::sendMoveAbs(int x, int y) {
	sendMove(0, x, y);
}

void SSerial::sendMoveRel(int x, int y) {
	sendMove(1, x, y);
}

void SSerial::sendMove(int t, int x, int y) {
	
	//convert to 1 byte
	unsigned char x00 = (unsigned char) x;
	unsigned char x01 = (unsigned char) (x>>8);
	unsigned char y00 = (unsigned char) y;
	unsigned char y01 = (unsigned char) (y>>8);
	
	
	//write type... move
	serial.writeByte((unsigned char) SERIAL_STX);
	
	if (t) {
		serial.writeByte((unsigned char) COMMAND_CODE_MOVE_REL);
	} 
	else {
		serial.writeByte((unsigned char) COMMAND_CODE_MOVE_ABS);
	}
	
	serial.writeByte(x00);
	serial.writeByte(x01);
	serial.writeByte(y00);
	serial.writeByte(y01);
	
	serial.writeByte((unsigned char) SERIAL_ETX);
	
	//these are just for printing out...
	int xs0 = ((x01<<8) | x00);
	int ys0 = ((y01<<8) | y00);	
	
	//printf("wrote via serial %i %i %i\n", 4, xs0, ys0);
	
	//setDone(false);
	
}

SPoint SSerial::getPos() {
	
	//let's do this now...
	serial.flush(true, true);

	serial.writeByte((unsigned char) SERIAL_STX);
	serial.writeByte((unsigned char) COMMAND_CODE_GET_POS);
	serial.writeByte((unsigned char) SERIAL_ETX);
	
		
	//wait until all results are there...
	//don't allow yourself to get into an infinite loop
	//wait until you can count to a big number... 
	
	//NB wait for done byte as well... not
	long l = 0;
	while (serial.available() != 4 && l < 99999) { 
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
		
		serial.writeByte((unsigned char) SERIAL_STX);
		serial.writeByte((unsigned char) COMMAND_CODE_PEN_UP);
		serial.writeByte((unsigned char) SERIAL_ETX);
		
		//sendStart();
		
		printf("sent pen up\n");
		return true;
	}
	else if(command == "down") {
		
		serial.writeByte((unsigned char) SERIAL_STX);
		serial.writeByte((unsigned char) COMMAND_CODE_PEN_DOWN);
		serial.writeByte((unsigned char) SERIAL_ETX);
		
		//sendStart();
		
		printf("sent pen down\n");
		return true;
	}
	
	//if none of the above worked return false
	return false;

}

void SSerial::sendDelayChange(int delay_ms) {
	
	serial.writeByte((unsigned char) SERIAL_STX);
	serial.writeByte((unsigned char) COMMAND_CODE_CHANGE_STEP_DELAY);
	serial.writeByte((unsigned char) delay_ms);
	serial.writeByte((unsigned char) SERIAL_ETX);
}

void SSerial::flush() {
	serial.flush(true, true);
}

int SSerial::available() {
	return serial.available();
}

void SSerial::setDone(bool b) {
	done = b;
}

bool SSerial::isDone() {
	return done;
}

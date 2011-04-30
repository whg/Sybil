/*
 *  SCommand.cpp
 *  Sybil
 *
 *  Created by Will Gallia on 20/04/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

#include "SCommand.h"

//constructor
SCommand::SCommand(SSerial* sc) {
	
	serialConnection = sc;
	previewPtr = (SPreview*) ofGetAppPtr();

	doingFile = false;
	
}

//descructor
SCommand::~SCommand() {

}

/*
 - - - PRIVATE METHODS - - - 
 */

/*
 this method is a little helper, 
 it converts a string to an int but also modifies a
 the string passed by reference if the source does not contain a number
 */

int SCommand::stringToInt(string source, string &comment) {
	
	//convert string to int, convert STL string to const char*
	int r = (short int) atoi(source.c_str());
	
	//this checks to see if a number was not entered
	//atoi() returns 0 if there the given string is not a number
	if (r == 0 && source != "0") {
		comment = source + ": argument is not a number";
	}
		
	return r;
}

// we use this in both circle and poly, so i made a little method for it...
// this is really simple stuff...

void SCommand::createPointsInCircle(int nPoints, int rad, SPoint pos, vector<SPoint> &points) {
	
	int inc = 360/nPoints;
	points.clear();
	SPoint fp;
	
	for (int i = 0; i < 360; i+= inc) {
		short int x = round(cos(ofDegToRad(i))) * rad;
		short int y = round(sin(ofDegToRad(i))) * rad;
		points.push_back(SPoint(x+pos.x, y+pos.y));
		
		if (i == 0) fp = SPoint(x+pos.x, y+pos.y);
	}
	
	//go full circle, push back first point
	points.push_back(fp);
	
}


/*
 
 - - - UTIL METHODS - - -
 
 */

bool SCommand::isDoingFile() {
	return doingFile;
}

void SCommand::setDoingFile(bool b) {
	doingFile = b;
	
	if (b) 	previewPtr->startedDrawing();
	else previewPtr->stoppedDrawing();
}

bool SCommand::isReadyForNext() {
	printf("asked if ready for next\n");
	//return serialConnection->isDone();
	return true;
}

/*

 - - - DRAWING METHODS - - -

*/

string SCommand::line(vector<string> &tokens, vector<char> &options) {
	
	bool rel = false;
	
	SPoint currentPos;
	
	//check for 4 arguments
	if (tokens.size() != 5) {
		return "usage: line [-r] x0 y0 x1 y1";
	} 
	
	//check for only r option
	for (int i = 0; i < options.size(); i++) {
		if (options[i] == 'r') {
			rel = true;
			currentPos = serialConnection->getPos();
		}
		else {
			return "line: illegal option --" + options[i];
		}
		
	}
	
	//get all the ints...
	short int c[4];
	
	for (int i = 1; i < 5; i++) {
		string comment = "";
		//convert
		c[i-1] = stringToInt(tokens[i], comment);
		//if one is bad, then exit loop
		if (comment != "") {
			return "line: " + comment;
		}
	}
	
	//if all is good, now send it...		
	if (rel) {
		c[0]+= currentPos.x;
		c[1]+= currentPos.y;
		c[2]+= currentPos.x;
		c[3]+= currentPos.y;
	}
	
	serialConnection->sendSingleLine(c[0], c[1], c[2], c[3]);
			
	return "";
	
}

string SCommand::rect(vector<string> &tokens, vector<char> &options) {

	bool rel = false; //relative flag
	bool cor = false; //corner flag
	
	SPoint currentPos;
		
	//check for correct arguments and options...
	//check for 4 arguments
	if (tokens.size() != 5) {
		return "usage: rect [-rc] x y w h";
	} 
	
	//check for only r and/or c option
	for (int i = 0; i < options.size(); i++) {
		if (options[i] == 'r') {
			rel = true;
			//now find the current pos of the plotter
			currentPos = serialConnection->getPos();
		}
		else if (options[i] == 'c') {
			cor = true;
		}
		else {
			return "rect: illegal option --" + options[i];
		}
	}
			
	//get all the ints...
	short int c[4];
	
	for (int i = 1; i < 5; i++) {
		string comment = "";
		//convert
		c[i-1] = stringToInt(tokens[i], comment);
		//if one is bad, then exit loop
		if (comment != "") {
			return "rect: " + comment;
		}
	}
	
		
	//set default variables...
	int x = c[0];
	int y = c[1];
	int w = c[2];
	int h = c[3];
	
	//do relative
	if (rel) {
		x+= currentPos.x;
		y+= currentPos.y;
	}
	
	//do corner
	if (cor) {
		x-= w/2;
		y-= h/2;
	}
	
	if (x < 0 || y < 0 || w < 0 || h < 0) {
		return "invalid arguments: check for negative values";
	}
	
	printf("x = %i, y = %i, w = %i, h = %i; r = %i, c = %i\n", x, y, w, h, rel, cor);
	
	//now make the SPoint vector
	vector<SPoint> points;
	points.push_back(SPoint(x, y));
	points.push_back(SPoint(x+w, y));
	points.push_back(SPoint(x+w, y+h));
	points.push_back(SPoint(x, y+h));
	points.push_back(SPoint(x, y));
	
	//now send...
	serialConnection->sendMultipleMove(points);
	printf("sent multiple points...\n");
	previewPtr->startedDrawing();
			
	return "";
	
}

string SCommand::circle(vector<string> &tokens, vector<char> &options) {

	bool rel = false; //relative flag
	bool cor = false; //corner flag
	
	SPoint currentPos;
	
	//check for correct arguments and options...
	//check for 4 arguments
	if (tokens.size() != 4) {
		return "usage: circle [-rc] x y r";
	} 
	
	//check for only r and/or c option
	for (int i = 0; i < options.size(); i++) {
		if (options[i] == 'r') {
			rel = true;
			//now find the current pos of the plotter
			currentPos = serialConnection->getPos();
		}
		else if (options[i] == 'c') {
			cor = true;
		}
		else {
			return "circle: illegal option --" + options[i];
		}
	}
	
	//get all the ints...
	short int c[3];
	
	for (int i = 1; i < 4; i++) {
		string comment = "";
		//convert
		c[i-1] = stringToInt(tokens[i], comment);
		//if one is bad, then exit loop
		if (comment != "") {
			return "circle: " + comment;
		}
	}
	
	
	//set default variables...
	int x = c[0];
	int y = c[1];
	int rad = c[2];
	
	//do relative
	if (rel) {
		x+= currentPos.x;
		y+= currentPos.y;
	}
	
	//do corner
	if (cor) {
		x-= rad;
		y-= rad;
	}
	
	printf("circle with: x = %i, y = %i, rad = %i, r = %i, c = %i\n", x, y, rad, rel, cor);
	
	//now calculate the circle...
	//here we are making a polygon with 360 sides...
	
	vector<SPoint> points = vector<SPoint>();
	createPointsInCircle(360, rad, SPoint(x, y), points);
	
	for (int i = 0; i < points.size(); i++) {
		if (points[i].x < 0 || points[i].y < 0) {
			return "invalid arguments: check for negative values";
		}
	}
	
	//now send...
	serialConnection->sendMultipleMove(points);
	previewPtr->startedDrawing();
	
	return "";
	
}

//this is kinda bad, it's basically exactly the same as circle...
//i want to have two commands... it's a taste thing...

string SCommand::poly(vector<string> &tokens, vector<char> &options) {
	
	bool rel = false; //relative flag
	bool cor = false; //corner flag
	
	SPoint currentPos;
	
	//check for correct arguments and options...
	//check for 4 arguments
	if (tokens.size() != 5) {
		return "usage: poly [-rc] x y nSides r";
	} 
	
	//check for only r and/or c option
	for (int i = 0; i < options.size(); i++) {
		if (options[i] == 'r') {
			rel = true;
			//now find the current pos of the plotter
			currentPos = serialConnection->getPos();
		}
		else if (options[i] == 'c') {
			cor = true;
		}
		else {
			return "poly: illegal option --" + options[i];
		}
	}
	
	//get all the ints...
	short int c[4];
	
	for (int i = 1; i < 5; i++) {
		string comment = "";
		//convert
		c[i-1] = stringToInt(tokens[i], comment);
		//if one is bad, then exit loop
		if (comment != "") {
			return "poly: " + comment;
		}
	}
	
	
	//set default variables...
	int x = c[0];
	int y = c[1];
	int nSides = c[2];
	int rad = c[3];
	
	//do relative
	if (rel) {
		x+= currentPos.x;
		y+= currentPos.y;
	}
	
	//do corner
	if (cor) {
		x-= rad;
		y-= rad;
	}
	
	printf("poly with: x = %i, y = %i, nSides = %i, rad = %i, r = %i, c = %i\n", x, y, nSides, rad, rel, cor);
	
	vector<SPoint> points = vector<SPoint>();
	createPointsInCircle(nSides, rad, SPoint(x, y), points);
	
	//check for negative values
	for (int i = 0; i < points.size(); i++) {
		printf("x = %i, y = %i\n", points[i].x, points[i].y);
		if (points[i].x < 0 || points[i].y < 0) {
			return "invalid arguments: check for negative values";
		}
	}
	
	//now send...
	serialConnection->sendMultipleMove(points);
	previewPtr->startedDrawing();
	
	return "";
	
}

string SCommand::get(vector<string> &tokens, vector<char> &options) {
	
	//check for 1 argument
	if (tokens.size() != 2) {
		return "usage: get pos";
	} 
	
	if (options.size() > 0) {
		return "get: illegal option --" + options[0];
	}
	
	if (tokens[1] == "pos") {
		SPoint p = serialConnection->getPos();
		stringstream x, y;
		x << p.x;
		y << p.y;
		return "Position = (" + x.str() + "," + y.str() + ")";
	}
	else {
		return "get: " + tokens[1] + ": argument not recognised";
	}
	
}

string SCommand::pen(vector<string> &tokens, vector<char> &options) {

	//check for 1 argument
	if (tokens.size() != 2) {
		return "usage: pen down/up";
	} 
	
	//try sending the second argument...
	//if the argument is invalid, then sendPen() will return false...
	if (!serialConnection->sendPen(tokens[1])) {
		return "pen: " + tokens[1] + ": argument not recognised";
	}
	
	return "";
}

string SCommand::delay(vector<string> &tokens, vector<char> &options) {

	//check for 1 argument
	if (tokens.size() != 2) {
		return "usage: delay ms";
	} 
	
	else {
		string comment = "";
		//convert to int
		int delay = stringToInt(tokens[1], comment);
		
		//check for number...
		if (comment != "") {
			return "delay: " + comment;
		} 
		
		else {
			serialConnection->sendDelayChange(delay);
		}

	}

	
	return "";
}

string SCommand::move(vector<string> &tokens, vector<char> &options) {
	
	bool rel = false;
	SPoint currentPos;
	
	//check for 2 arguments
	if (tokens.size() != 3) {
		return "usage: move [-r] x y";
	} 
	
	//check for only r option
	for (int i = 0; i < options.size(); i++) {
		if (options[i] == 'r') {
			rel = true;
			currentPos = serialConnection->getPos();
		}
		else {
			return "move: illegal option --" + options[i];
		}
	}
			
	//get all the ints...
	short int c[2];
	
	for (int i = 1; i < 3; i++) {
		string comment = "";
		//convert
		c[i-1] = stringToInt(tokens[i], comment);
		//if one is bad, then exit loop
		if (comment != "") {
			return "move: " + comment;
		}
	}
	
	if (rel) {
		c[0]+= currentPos.x;
		c[1]+= currentPos.y;
	}
	
	//and send...
	serialConnection->sendMoveAbs(c[0], c[1]);
		
	
	return "";
}

string SCommand::flush(vector<string> &tokens, vector<char> &options) {
	
	if (tokens.size() != 1) {
		return "usage: flush";
	}
	
	serialConnection->flush();
	return "";
}

string SCommand::query(vector<string> &tokens, vector<char> &options) {

	if (tokens.size() == 1) {
		int n = serialConnection->queryDelayed();
		stringstream ss;
		ss << n;
		return "number of commands = " + ss.str();
	}
	
	
	return "didn't work...";
}

string SCommand::start(vector<string> &tokens, vector<char> &options) {
	
	if (tokens.size() == 1) {
		serialConnection->start();
		return "";
	}

	return "error";
}

string SCommand::available(vector<string> &tokens, vector<char> &options) {

	if (tokens.size() == 1) {
		int n = serialConnection->available();
		stringstream ss;
		ss << n;
		return "number of bytes available = " + ss.str();
	}
	
	return "error";
}
	

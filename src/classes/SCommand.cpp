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

	
}

//descructor
SCommand::~SCommand() {

}

/*
 this method is a little helper, 
 it converts a string to an int but also modifies a
 a string passed by reference if the source does not contain a number
 */

int SCommand::stringToInt(string source, string &comment) {
	
	//convert string to int, convert STL string to const char*
	int r = (short int) atoi(source.c_str());
	
	//this checks to see if a number was not entered
	//atoi() returns 0 if there the given string is not a number
	if (r == 0 && source != "0") {
		comment = "line: " + source + ": argument is not a number";
	}
		
	return r;
}

/*

 - - - DRAWING METHODS - - -

*/

string SCommand::line(vector<string> &tokens) {
	
	string comment = "";

	//check for 4 arguments
	if (tokens.size() != 5) {
		comment = "usage: line x0 y0 x1 y1";
	} 
	
	else {
		
		//get all the ints...
		short int c[4];
		
		for (int i = 1; i < 5; i++) {
			//convert
			c[i-1] = stringToInt(tokens[i], comment);
			//if one is bad, then exit loop
			if (comment != "") {
				break;
			}
		}
		
		//if all is good, now send it...
		if (comment == "") {
			serialConnection->sendSingleLine(c[0], c[1], c[2], c[3]);
		}
		
	}
	
	return comment;
}

string SCommand::rect(vector<string> &tokens) {
	
	string comment = "";
	
	//check for 4 arguments
	if (tokens.size() != 5) {
		comment = "usage: rect x y w h";
	} 
	
	else {
		
		//get all the ints...
		short int c[4];
		
		for (int i = 1; i < 5; i++) {
			//convert
			c[i-1] = stringToInt(tokens[i], comment);
			//if one is bad, then exit loop
			if (comment != "") {
				break;
			}
		}
		
		if (comment == "") {
			
			//now make the SPoint vector
			vector<SPoint> points;
			points.push_back(SPoint(c[0], c[1]));
			points.push_back(SPoint(c[0]+c[2], c[1]));
			points.push_back(SPoint(c[0]+c[2], c[1]+c[3]));
			points.push_back(SPoint(c[0], c[1]+c[3]));
			points.push_back(SPoint(c[0], c[1]));
			
			//now send...
			serialConnection->sendCollection(points);
			previewPtr->setStartedDrawing(true);
		}
		
	}
	
	return comment;
	
}

string SCommand::circle(vector<string> &tokens) {
	
	string comment = "";
	
	
	return comment;
	
}


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

string SCommand::line(vector<string> &tokens, vector<char> &options) {
	
	string comment = "";
	bool r = false;
	
	SPoint currentPos = serialConnection->getPos();

	//check for 4 arguments
	if (tokens.size() != 5) {
		comment = "usage: line [-r] (x0 y0) x1 y1";
	} 
	
	//check for only r option
	for (int i = 0; i < options.size(); i++) {
		if (options[i] == 'r') {
			r = true;
		}
		else {
			comment = "line: illegal option --" + options[i];
			break;
		}
		
	}
	
	
	if (comment == "") {
		
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
			
			if (r) {
				c[0]+= currentPos.x;
				c[1]+= currentPos.y;
				c[2]+= currentPos.x;
				c[3]+= currentPos.y;
			}
			
			serialConnection->sendSingleLine(c[0], c[1], c[2], c[3]);
		}
		
	}
	
	return comment;
}

string SCommand::rect(vector<string> &tokens, vector<char> &options) {
	
	string comment = "";
	bool rel = false; //relative flag
	bool cor = false; //corner flag
	
	SPoint currentPos = serialConnection->getPos();
	
	//check for correct arguments and options...
	//check for 4 arguments
	if (tokens.size() != 5) {
		comment = "usage: rect [-rc] x y w h";
	} 
	
	//check for only r and/or c option
	for (int i = 0; i < options.size(); i++) {
		if (options[i] == 'r') {
			rel = true;
		}
		else if (options[i] == 'c') {
			cor = true;
		}
		else {
			comment = "rect: illegal option --" + options[i];
			break; //now exit
		}

	}
	
	if (comment == "") {
		
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
			
			printf("x = %i, y = %i, w = %i, h = %i; r = %i, c = %i\n", x, y, w, h, rel, cor);
			
			//now make the SPoint vector
			vector<SPoint> points;
			points.push_back(SPoint(x, y));
			points.push_back(SPoint(x+w, y));
			points.push_back(SPoint(x+w, y+h));
			points.push_back(SPoint(x, y+h));
			points.push_back(SPoint(x, y));
			
			//now send...
			serialConnection->sendCollection(points);
			previewPtr->setStartedDrawing(true);
		}
		
	}
	
	return comment;
	
}

string SCommand::circle(vector<string> &tokens, vector<char> &options) {
	
	string comment = "";
	
	//check for 1 argument
	if (tokens.size() != 2) {
		comment = "usage: get pos";
	} 
	
	if (options.size() > 0) {
		comment = comment = "rect: illegal option --" + options[0];
	}
	
	if (comment == "") {
		if (tokens[1] == "pos") {
			SPoint p = serialConnection->getPos();
			stringstream x, y;
			x << p.x;
			y << p.y;
			comment = "Position = (" + x.str() + "," + y.str() + ")";
		}
	}
	
	else {
		comment = "get: " + tokens[1] + ": argument not recognised";
	}
	
	return comment;
	
}


string SCommand::get(vector<string> &tokens, vector<char> &options) {

	string comment = "";
	
	//check for 1 argument
	if (tokens.size() != 2) {
		comment = "usage: get pos";
	} 
	
	else if (tokens[1] == "pos") {
		SPoint p = serialConnection->getPos();
		stringstream x, y;
		x << p.x;
		y << p.y;
		comment = "Position = (" + x.str() + "," + y.str() + ")";
	}
	
	else {
		comment = "get: " + tokens[1] + ": argument not recognised";
	}
	
	
	return comment;
}

string SCommand::pen(vector<string> &tokens, vector<char> &options) {
	
	string comment = "";
	
	//check for 1 argument
	if (tokens.size() != 2) {
		comment = "usage: pen down/up";
	} 
	
	//try sending the second argument...
	//if the argument is invalid, then sendPen() will return false...
	if (!serialConnection->sendPen(tokens[1])) {
		comment = "pen: " + tokens[1] + ": argument not recognised";
	}
	
	return comment;
}


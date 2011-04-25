/*
 *  SCommand.h
 *  Sybil
 *
 *  Created by Will Gallia on 20/04/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

#ifndef _SCOMMAND
#define _SCOMMAND

//this class handle the commands that get sent to pedro,
//they can be in drawing or util commands...

#include "SPreview.h"
#include "SSerial.h"

class SSerial;

class SCommand {
	
private:
	
	int stringToInt(string source, string &comment);
	
	SSerial* serialConnection;
	SPreview* previewPtr;
	
	SPoint getPlotterPos();
	
public:
	SCommand(SSerial* sc);
	~SCommand();
	
	//drawing methods
	string line(vector<string> &tokens, vector<char> &options);
	string circle(vector<string> &tokens, vector<char> &options);
	string rect(vector<string> &tokens, vector<char> &options);
	
	string pen(vector<string> &tokens, vector<char> &options);
	
	//util methods
	string get(vector<string> &tokens, vector<char> &options);
	string move(vector<string> &tokens, vector<char> &options);
	
};

#endif
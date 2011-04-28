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
	
	SSerial* serialConnection;
	SPreview* previewPtr;
		
	bool doingFile;
	
	int stringToInt(string source, string &comment);
	SPoint getPlotterPos();
	void createPointsInCircle(int nPoints, int rad, SPoint pos, vector<SPoint> &points);
	
public:
	SCommand(SSerial* sc);
	~SCommand();
	
	void setDoingFile(bool b);
	bool isDoingFile();
	
	bool isReadyForNext();

	//drawing methods
	string line(vector<string> &tokens, vector<char> &options);
	string circle(vector<string> &tokens, vector<char> &options);
	string arc(vector<string> &tokens, vector<char> &options);
	string rect(vector<string> &tokens, vector<char> &options);
	string poly(vector<string> &tokens, vector<char> &options);
	
	string pen(vector<string> &tokens, vector<char> &options);
	
	//util methods
	string get(vector<string> &tokens, vector<char> &options);
	string move(vector<string> &tokens, vector<char> &options);
	string delay(vector<string> &tokens, vector<char> &options);
	string flush(vector<string> &tokens, vector<char> &options);
	
	
};

#endif
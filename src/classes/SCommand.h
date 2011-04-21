/*
 *  SCommand.h
 *  Sybil
 *
 *  Created by Will Gallia on 20/04/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

//this class handle the commands that get sent to pedro,
//they can be in drawing or util commands...

#include "SPreview.h"
#include "SSerial.h"



class SCommand {
	
private:
	
	int stringToInt(string source, string &comment);
	
	SSerial* serialConnection;
	SPreview* previewPtr;
	
public:
	SCommand(SSerial* sc);
	~SCommand();
	
	//drawing methods
	string line(vector<string> &tokens);
	string circle(vector<string> &tokens);
	string rect(vector<string> &tokens);
	
	//util methods
	string get(vector<string> &tokens);
	string move(vector<string> &tokens);
	
};
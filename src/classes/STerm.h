/*
 *  STerm.h
 *  Sybil
 *
 *  Created by Will Gallia on 15/04/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

//this class is a bash copy terminal...
//at the moment it works well with andale mono...

#ifndef _S_TERM
#define _S_TERM

#include "ofMain.h"
#include "STypes.h"
#include "SSerial.h"
#include "SPreview.h"

class SPreview;
class SSerial;

typedef struct {
	int x;
	int y;
	int minx;
	int index;
	string str;
} Prompt;

class STerm {
	
private:
	Prompt prompt;
	
	ofTrueTypeFont font;
	int lineHeight;
	int characterWidth, spaceWidth;
	int stringWidth;
	
	int basicWidth;
	
	int prevCommand;
	string tempCommand;
	
	vector<string> lines;
	vector<string> results;
	
	vector<string> commands;
	void setCommands(vector<string> &c);
	
	int cl; //current line
	
	SSerial* serialConnection;
	SPreview* previewPtr;
	
public:
	STerm(SSerial* sc);
	~STerm();
	
	
	void draw();
	void keyPressed(int key);
	void process(string command);
	void explode(string command, char sep, vector<string> &tokens);
	
};

#endif

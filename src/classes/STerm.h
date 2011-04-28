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
#include "SPreview.h"
#include "SCommand.h"
#include <iostream>
#include <fstream>

class SPreview;
class SCommand;

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
	int screenYPos;
	int noResults;
	
	int prevCommand;
	string tempCommand;
	
	vector<string> lines;
	vector<string> results;
	
	vector<string> availableCommands;
	
	int cl; //current line
	
	SPreview* previewPtr;
	SCommand* commander;
	
	string filesDirectory;
	int flc; //file line counter
	vector<string> fileLines;
	
	void process(string command);
	void explode(string command, char sep, vector<string> &tokens, vector<char> &options);
	string sendCommand(string command);
	void setCommands(vector<string> &c);
	
	string readFile(string path, vector<string> &fileLines);
	string processFile(vector<string> &tokens);
	
public:
	STerm(SCommand* c);
	~STerm();
	
	void draw();
	void update();
	void keyPressed(int key);
	
	bool iterateFile();


	
};

#endif

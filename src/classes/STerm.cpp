/*
 *  STerm.cpp
 *  Sybil
 *
 *  Created by Will Gallia on 15/04/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

#include "STerm.h"


//--------------------------------------------------------------
STerm::STerm(SCommand* c) {

	//set the commander
	commander = c;
	
	previewPtr = (SPreview*) ofGetAppPtr();
	
	//load font
	font.loadFont("/Library/Fonts/Andale Mono.ttf", 12);
	lineHeight = (int) font.getLineHeight();
	characterWidth = (int) font.stringWidth("a") - 3; //this is the same for all... monospace
	spaceWidth = characterWidth-1;
	//printf("characterWidth = %i\n", characterWidth);
	cl = 0;
	screenYPos = 0;
	noResults = 0;
	
	//set default prompt
	prompt.x = 0;
	prompt.y = 4;
	prompt.index = 0;
	prompt.minx = 2;
	prompt.str = "sybil:$ ";
	lines.push_back("");
	results.push_back("");
	stringWidth = characterWidth*8;
	
	basicWidth = stringWidth;
	prevCommand = 0;
	
	filesDirectory = "/Users/WHG/Desktop/";
	flc = 0;
	vector<string> fileLines = vector<string>();

	
	//load the commands...
	setCommands(availableCommands);
	
	
}

STerm::~STerm() {
	
}

//this is a bit of a rubbish way of doing things but this whole thing
//was done very quickly, it would be nice if it read files so new commands
//could be added easier but hey... whatever

void STerm::setCommands(vector<string> &c) {
	c.clear();
	c.push_back("line");
	c.push_back("arc");
	c.push_back("move");
	c.push_back("circle");
	c.push_back("poly");
	c.push_back("rect");
	c.push_back("get");
	c.push_back("delay");
	c.push_back("read");
	c.push_back("pen");
	c.push_back("available");
	c.push_back("start");
	c.push_back("query");
	c.push_back("flush");
	
}

void STerm::update() {
	
	noResults = 0;
	for (int i = 0; i < results.size(); i++) {
		if (results[i] != "") {
			noResults++;
		}
	}
	
	//check to see if we need to move everything up to fit the new line
	if (prompt.y+lineHeight > ofGetHeight() - screenYPos) {
		screenYPos-= lineHeight;
		//screenYPos-(noResults*lineHeight*2);
	}
	
}

void STerm::draw() {
	
	update();
	
	ofFill();
	
	ofPushMatrix();
	ofTranslate(0, screenYPos-3);
	
	//this is where we draw all commands previous and present.
	//not future... yet
	int j = 0;
	for (int i = 0; i < results.size(); i++) {
		if (results[i] == "") {
			ofSetColor(10, 10, 10);
			font.drawString(prompt.str + lines[j], 0, lineHeight*(i+1));
			j++;
		} 
		//draw results/comments
		else {
			ofSetColor(100, 100, 100);
			font.drawString(results[i], 0, lineHeight*(i+1));
			
		}
		
	}	
	
	//this is where we draw the prompt...
	ofPushMatrix();
	ofTranslate(characterWidth*prompt.str.length(), 0);
	ofSetColor(50, 50, 50, 100);
	ofRect(prompt.x+prompt.minx, prompt.y, characterWidth, lineHeight);	
	ofPopMatrix();
	
	ofPopMatrix();
}


/* - - - - - - - - - - - - - - - - - - - 
 
 - - - KEY ACTIONS - - -
 
 this is where all the key presses are interpreted
 i am trying to copy bash, so at the moment,
 we are implementing:
 
 - up and down for previous commands 
 - left and right to move along the line
 - tab to autocomplete
 - backspace to delete characters
 - enter to process command
 
 - - - - - - - - - - - - - - - - - - - */

void STerm::keyPressed(int key) {
	
	//printf("key = %i\n", key);
	//printf("prev command before = %i\n", prevCommand);
	//lines[cl] += (char) key;
	
	string::iterator it = lines[cl].begin();
	
	//int p =  ceil(prompt.x/characterWidth);
	//printf("p = %i\n", p);
	
	//space
	if (key == 32) {
		lines[cl].insert(it+prompt.index, (char) key);
		prompt.x+= (spaceWidth);
		prompt.index++;
	}
	
	// backspace
	else if (key == 127) {
		if (prompt.x > 0) {			
			if (lines[cl].at(prompt.index-1) == ' ') prompt.x -= spaceWidth;
			else prompt.x -= characterWidth;
			lines[cl].erase(it+prompt.index-1);
			prompt.index--;
		}
	}
	
	// left arrow
	else if (key == 356) {
		if (prompt.x > 0) { // don't go too far...
			if (lines[cl].at(prompt.index-1) == ' ') prompt.x -= spaceWidth;
			else prompt.x -= characterWidth;
			prompt.index--;
		}
	}
	
	//  right arrow
	else if (key == 358) {
		if (prompt.index < lines[cl].length()) { // can't go further than line
			if (lines[cl].at(prompt.index) == ' ') prompt.x += spaceWidth;
			else prompt.x += characterWidth;
			prompt.index++;
		}
	}
	
	// up arrow - previous command
	else if (key == 357) {
		//save the current command
		if (prevCommand == 0) {
			tempCommand = lines[cl];
		}
		//fetch previous commands
		if (prevCommand < cl) {
			prevCommand++;
			lines[cl] = lines[cl-prevCommand];
			//now move prompt
			int x = 0;
			for (int i = 0; i < lines[cl].length(); i++) {
				if (lines[cl].at(i) == ' ') x+= spaceWidth;
				else x+= characterWidth;
			}
			prompt.x = x;
			prompt.index = lines[cl].length();
		}
	}
	
	// down arrow
	else if (key == 359) { 
		if (prevCommand > 0) {
			prevCommand--;
			lines[cl] = lines[cl-prevCommand];
		}
		//get the saved command
		if (prevCommand == 0) {
			lines[cl] = tempCommand;
		}
		//now move prompt
		int x = 0;
		for (int i = 0; i < lines[cl].length(); i++) {
			if (lines[cl].at(i) == ' ') x+= spaceWidth;
			else x+= characterWidth;
		}
		prompt.x = x;
		prompt.index = lines[cl].length();
	}
	
	// esc, do nothing
	else if (key == 27) { }
	
	//tab, do autocomplete
	else if (key == 9) {
		for (int i = 0; i < availableCommands.size(); i++) {
			bool show = false;
			for (int j = 0; j < lines[cl].length() && j < availableCommands[i].length(); j++) {
				if (availableCommands[i].at(j) == lines[cl].at(j)) {
					show = true;
				} else {
					show = false;
					break;
				}
			}
			if (show) {
				//change the command
				lines[cl] = availableCommands[i];
        //add a space on to the end of the command... bash style
        lines[cl]+= ' ';
				//move the prompt
				int x = 0;
				for (int i = 0; i < lines[cl].length(); i++) {
					if (lines[cl].at(i) == ' ') x+= spaceWidth;
					else x+= characterWidth;
				}
				prompt.x = x;
				prompt.index = lines[cl].length();
			}
		}
	}
	
	//enter, do things with current line
	else if (key == 13) { 
		//cout << lines[cl] << endl;
		
		//process the command
		process(lines[cl]);
		
		//now do the housework
		cl++;
		prompt.index = 0;
		prompt.x = 0;
		prompt.y+= lineHeight;
		prevCommand = 0;
		
		
	}
	
	//control-c, clear the screen
	else if (key == 3) {
		
		//clear screen
		ofBackground(255, 255, 255);
		
		//reset variables
		lines.clear();
		results.clear();
		cl = 0;
		prompt.x = 0;
		prompt.y = 4;
		prompt.index = 0;
		prompt.minx = 2;
		lines.push_back("");
		results.push_back("");
		stringWidth = characterWidth*8;
		screenYPos = 0;
		
	}
	
	//all other keys...
	//hopefully ofTrueTypeFont can draw them...
	else if (key > 31) {
		lines[cl].insert(it+prompt.index, (char) key);
		prompt.x+= characterWidth;
		prompt.index++;
	}
	
}


/* - - - - - - - - - - - - - - -
 
 - - - PROCESS - - -
 
 this is where we process the commands
 it is here that we check that the arguments are correct
 if they are then commands are sent to serial
 
 - - - - - - - - - - - - - - - */

void STerm::process(string command) {
	
	//don't try and process an empty line
	if (command != "") {
		
		
		string comment = "";
		
		//process first token... 
		// i.e. the command...
		comment = sendCommand(command);
	  
		
		//show the comment if there is one and increment prompt.y
		if (comment != "") {
			results.push_back(comment);
			//need an extra lineHeight added to prompt.y
			prompt.y+= lineHeight;
		}
		
	}
	
	//prepare for next line...
	lines.push_back("");
	results.push_back("");
	
}

//this is done this way so we can optionally use the returned comment...
string STerm::sendCommand(string command) {
	
	//split the line up into tokens
	vector<string> tokens;
	vector<char> options;
	explode(command, ' ', tokens, options);
	
	if (tokens[0] == "line") {
		return commander->line(tokens, options);
	}
	else if (tokens[0] == "rect")	{
		return commander->rect(tokens, options);
	}
	else if (tokens[0] == "move")	{
		return commander->move(tokens, options);
	}
	else if (tokens[0] == "get") {
		return commander->get(tokens, options);
	}
	else if (tokens[0] == "pen") {
		return commander->pen(tokens, options);
	}
	else if (tokens[0] == "circle") {
		return commander->circle(tokens, options);
	}
	else if (tokens[0] == "poly") {
		return commander->poly(tokens, options);
	}
	else if (tokens[0] == "delay") {
		return commander->delay(tokens, options);
	}
	else if(tokens[0] == "flush") {
		return commander->flush(tokens, options);
	}
	else if(tokens[0] == "read") {
		return processFile(tokens);
	}
	
	else if(tokens[0] == "query") {
		return commander->query(tokens, options);
	}
	else if(tokens[0] == "start") {
		return commander->start(tokens, options);
	}
	else if(tokens[0] == "available") {
		return commander->available(tokens, options);
	}
	
	//if doesn't match anything...
	else {
		return tokens[0] +	": command not found";
	}
	
}


//this is a helper method, inspired by PHP's explode

//it takes a string and splits the separate words into tokens,
//extra white space is removed in the process

//in UNIX fashion words starting with a '-' are treated as options...
//we can't have negative values in our plotter so this works.
//consecutive characters after a single hypen are still accepted, in UNIX fashion...

void STerm::explode(string command, char sep, vector<string> &tokens, vector<char> &options) {
	tokens.clear();
	
	
	string t = "";
	for (int i = 0; i < command.length(); i++) {
		if (command[i] != sep) t+= command[i];
		else {
			//don't add things starting with a space..
			//or an empty string...
			if (t[0] != ' ' && t != "") {
				//printf("t is: '%s'\n", t.c_str());
				tokens.push_back(t);
				t = "";
			}
		}
	}
	
	// add the final one...
	// but don't add it if it's a space... or nothing
	if (t != " " && t != "") {
		tokens.push_back(t);
	}
	
	//now do the options...
	//any word starting with a '-' is an option
	
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i].at(0) == '-') {
			//now start at character 1 and add to options to vector
			for (int j = 1; j < tokens[i].length(); j++) {
				options.push_back(tokens[i].at(j));
			}
			
			//now remove the string as it is an option not a valid token
			tokens.erase(tokens.begin()+i);
			//we need decrement i now as we have just erased...
			i--;
		}
	}

	
}



/*
 - - - FILE HANDLING - - -
 */
string STerm::processFile(vector<string> &tokens) {
		
	string comment = "";
	
	if (tokens.size() != 2) {
		return "usage: read file";
	}
		
	else {
		comment = readFile(tokens[1], fileLines);
	}
	
	if (comment == "") {
		//set file line counter to 0
		flc = 0;
		
		//tell the commander we about to iterate through a file
		commander->setDoingFile(true);
		
		printf("sent first iterateFile()\n");
		//start the iteration process...
		iterateFile();
		
	}
	
	return comment;
}

bool STerm::iterateFile() {
	
	if (flc < fileLines.size()) {
		
		if (commander->isReadyForNext()) {
			
			//process the line
			sendCommand(fileLines[flc]);
			//printf("processed %s\n", fileLines[flc].c_str());
			flc++;
			
			//add a dot to the previous result
			//int lr = (int) results.size()-1;
//			results[lr] += ".";
			
			return false;
		}
	}
	
	//this is when we have got through all lines
	else {
		//printf("we have finished iterateFile\n");
		//commander->setDoingFile(false);
		return true;
	}

	
}

string STerm::readFile(string path, vector<string> &fileLines) {

	//set up stream
	ifstream file;
	
	if (path.at(0) == '/') {
		file.open(path.c_str());
	}
	
	//if the path is not absolute look in specified directory
	else {
		string p = filesDirectory + path;
		file.open(p.c_str());
	}
		
	fileLines.clear();
	
	//check to see something is open
	if (file.is_open()) {
		
		while (file.good()) {
			string line;
			getline(file, line);
			fileLines.push_back(line);
		}
		
		//and close...
		file.close();
		
		return "";
	}
	
	else {
		return "could not open file";
	}

	
}

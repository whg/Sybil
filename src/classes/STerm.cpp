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
STerm::STerm() {

	//load font
	font.loadFont("/Library/Fonts/Andale Mono.ttf", 12);
	lineHeight = (int) font.getLineHeight();
	characterWidth = (int) font.stringWidth("a") - 3; //this is the same for all... monospace
	spaceWidth = characterWidth-1;
	printf("characterWidth = %i\n", characterWidth);
	cl = 0;
	
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
	
	//load the commands...
	setCommands(commands);
}

STerm::~STerm() {
	
}


void STerm::draw() {
	
	ofFill();
	
	//this is where we draw all commands previous and present.
	//not future... yet
	int j = 0;
	for (int i = 0; i < results.size(); i++) {
		if (results[i] == "") {
			ofSetColor(10, 10, 10);
			font.drawString(prompt.str + lines[j], 0, lineHeight*(i+1));
			j++;
		} else {
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
}


/* - - - - - - - - - - - - - - - - - - - 
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
	
	printf("key = %i\n", key);
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
	
	// up arrow
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
		for (int i = 0; i < commands.size(); i++) {
			bool show = false;
			for (int j = 0; j < lines[cl].length() && j < commands[i].length(); j++) {
				if (commands[i].at(j) == lines[cl].at(j)) {
					show = true;
				} else {
					show = false;
					break;
				}
			}
			if (show) {
				//change the command
				lines[cl] = commands[i];
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
		cout << lines[cl] << endl;
		
		//process the command
		process(lines[cl]);
		
		//now do the housework
		cl++;
		prompt.index = 0;
		prompt.x = 0;
		prompt.y+= lineHeight;
	}
	
	//all other keys...
	else {
		lines[cl].insert(it+prompt.index, (char) key);
		prompt.x+= characterWidth;
		prompt.index++;
	}
	
}


/* - - - - - - - - - - - - - - -
 
 this is where we process the commands
 
 - - - - - - - - - - - - - - - */

void STerm::process(string command) {
	
	//don't try and process an empty line
	if (command != "") {
		
		//split the line up into tokens
		vector<string> tokens;
		explode(command, ' ', tokens);
		string comment = "";
		
		//process first token... the command...
		
		if (tokens[0] == "take") {
			comment = "you wrote take";
		}
		else if (tokens[0] == "line") {
			if (tokens.size() != 5) {
				comment = "usage: line [] x0 y0 x1 y1";
			} 
			
		}
		else {
			comment = tokens[0] +	": command not found";
		}
		
		//show the comment, if there is one and inc promt.y
		if (comment != "") {
			results.push_back(comment);
			prompt.y+= lineHeight;
		}
		
	}
	
	lines.push_back("");
	results.push_back("");
	
}


//this is a helper method, inspired by PHP's explode

void STerm::explode(string command, char sep, vector<string> &tokens) {
	tokens.clear();
	string t = "";
	for (int i = 0; i < command.length(); i++) {
		if (command[i] != sep) t+= command[i];
		else {
			cout << t.length() << endl;
			//don't things starting with a space..
			if (t[0] != ' ') {
				tokens.push_back(t);
				t = "";
			}
		}
	}
	// add the final one...
	if (t.length() != 1 && t[0] != 0) {
		tokens.push_back(t);
		t = "";
	}
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
	c.push_back("rect");
	
}


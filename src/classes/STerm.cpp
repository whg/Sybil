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
STerm::STerm(SCommand* c, SSerial* sc) {

	//set the commander
	commander = c;
	serialConnection = sc;
	
	previewPtr = (SPreview*) ofGetAppPtr();
	
	//load font
	font.loadFont("/Library/Fonts/Andale Mono.ttf", 12);
	lineHeight = (int) font.getLineHeight();
	characterWidth = (int) font.stringWidth("a") - 3; //this is the same for all... monospace
	spaceWidth = characterWidth-1;
	printf("characterWidth = %i\n", characterWidth);
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
	
	//load the commands...
	setCommands(commands);
	
	
}

STerm::~STerm() {
	
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
		
		//split the line up into tokens
		vector<string> tokens;
		vector<char> options;
		explode(command, ' ', tokens, options);
		string comment = "";
		
		//process first token... 
		// i.e. the command...
		
		if (tokens[0] == "take") {
			comment = "you wrote take";
		}
		
		// - - line - -
		else if (tokens[0] == "line") {
			
						
		}
		
		// - - RECT - -
		
		else if (tokens[0] == "rect") {
			
			commander->rect(tokens, options);
			
//			//check for 4 arguments
//			if (tokens.size() == 1) {
//				//now make the SPoint vector
//				vector<SPoint> points;
//				points.push_back(SPoint(0, 0));
//				points.push_back(SPoint(0, 400));
//				points.push_back(SPoint(400, 400));
//				points.push_back(SPoint(400, 0));
//				points.push_back(SPoint(0, 0));
//				//points.push_back(SPoint(100, 0));
//				
//				//now send...
//				serialConnection->sendCollection(points);
//				previewPtr->setStartedDrawing(true);
//			}
//			else if (tokens.size() != 5) {
//				comment = "usage: rect x y w h";
//			} 
//			
//			
//			else {
//				
//				//same as above
//				short int c[4];
//				for (int i = 1; i < 5; i++) {
//					c[i-1] = (short int) atoi(tokens[i].c_str());
//					if (c[i-1] == 0 && tokens[i] != "0") {
//						comment = "rect: " + tokens[i] + ": argument is not a number";
//						break;
//					}
//				}
//				
//				if (comment == "") {
//					
//					//now make the SPoint vector
//					vector<SPoint> points;
//					points.push_back(SPoint(c[0], c[1]));
//					points.push_back(SPoint(c[0]+c[2], c[1]));
//					points.push_back(SPoint(c[0]+c[2], c[1]+c[3]));
//					points.push_back(SPoint(c[0], c[1]+c[3]));
//					points.push_back(SPoint(c[0], c[1]));
//					
//					//now send...
//					serialConnection->sendCollection(points);
//					previewPtr->setStartedDrawing(true);
//				}
//				
//			}
			
		}
		
		// - - MOVE - -
		// this command moves the pen from its current position to 
		// the specified position
		
		else if (tokens[0] == "move") {
			
			//check for 2 arguments
			if (tokens.size() != 3) {
				comment = "usage: move x y";
			} 
			
			else {
				
				short int c[2];
				for (int i = 1; i < 3; i++) {
					
					c[i-1] = (short int) atoi(tokens[i].c_str());
					if (c[i-1] == 0 && tokens[i] != "0") {
						comment = "line: " + tokens[i] + ": argument is not a number";
						break;
					}
				}
				
				//now send...
				if (comment == "") {
					serialConnection->sendMove(c[0], c[1]);
				}
				
			}
			
		}
		
		// - - - GET - - -
		
		else if (tokens[0] == "get") {
			
			
			comment = commander->get(tokens, options);
			
		}
		
		else if (tokens[0] == "pen") {
				
			comment = commander->pen(tokens, options);
		}
		
		// - - - CIRCLE - - -
		
		else if (tokens[0] == "circle") {
			
			//resolution & radius
			int res, rad;
			
			//check for 1 argument
			//this is for the default resolution of 30
			if (tokens.size() == 2 || tokens.size() == 3) {
				short int c;
				//convert to int					
				c = (short int) atoi(tokens[1].c_str());
				if (c == 0 && tokens[1] != "0") {
					comment = "circle: " + tokens[1] + ": argument is not a number";
				}
				rad = c;
				//set res to default i.e. 30, this will be overridden later if res is specified
				res = 30;
			}
			
			//2 arguments, user specified resolution
			if (tokens.size() == 3) {
				short int c;
				//convert to int					
				c = (short int) atoi(tokens[2].c_str());
				if (c == 0 && tokens[2] != "0") {
					comment = "circle: " + tokens[2] + ": argument is not a number";
				}
				//set resolution
				res = c;
			}
			
			if (tokens.size() != 2 && tokens.size() != 3) {
				comment = "usage: circle r (res)";
			} 

			//calculate and send
			if (comment == "") {
				
				//calc circle
				SPoint fp;
				vector<SPoint> p;
				
				int cinc = 360/res; //circle increment
				
				for (int i = 0; i < 360; i+= cinc) {
					short int x = (sin(ofDegToRad(i))+1) * rad;
					short int y = (cos(ofDegToRad(i))+1) * rad;
					
					p.push_back(SPoint(x, y));
					printf("x = %i y = %i\n", x, y);
					if (i == 0) fp = SPoint(x, y);
				}
				//go full circle, push back first point
				p.push_back(fp);
			
				serialConnection->sendCollection(p);
				previewPtr->startedDrawing();
				
			}

		}
		
		else {
			comment = tokens[0] +	": command not found";
		}
		
		//show the comment if there is one and increment prompt.y
		if (comment != "") {
			results.push_back(comment);
			prompt.y+= lineHeight;
		}
		
	}
	
	lines.push_back("");
	results.push_back("");
	
}


//this is a helper method, inspired by PHP's explode

//it takes a string and splits the separate words into tokens,
//extra white space is removed in the process

//in bash fashion words starting with a '-' are treated as options...
//we can't have negative values in our plotter to this works.

void STerm::explode(string command, char sep, vector<string> &tokens, vector<char> &options) {
	tokens.clear();
	
	
	string t = "";
	for (int i = 0; i < command.length(); i++) {
		if (command[i] != sep) t+= command[i];
		else {
			//don't add things starting with a space..
			//or an empty string...
			if (t[0] != ' ' && t != "") {
				printf("t is: '%s'\n", t.c_str());
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
	
	printf("no of tokens = %i\n", (int) tokens.size());
	for (int i = 0; i < tokens.size(); i++) {
		printf("tokens %i = \"%s\"\n", i, tokens[i].c_str());
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
	printf("again...\n");
	printf("no of tokens = %i\n", (int) tokens.size());
	for (int i = 0; i < tokens.size(); i++) {
		printf("tokens %i = \"%s\"\n", i, tokens[i].c_str());
	}
	
	for (int i = 0; i < options.size(); i++) {
		printf("options %i = '%c'\n", i, options[i]);
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
	c.push_back("get");
	
}


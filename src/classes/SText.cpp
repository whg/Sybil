/*
 *  SText.cpp
 *  Sybil
 *
 *  Created by Will Gallia on 07/03/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

#include "SText.h"
#include "SPreview.h"


SText::SText(int i)
: SItem(i) {
		
	fontName = "Georgia";
	fontSize = 20;
	
	//this loads the font and does a new things such as set the lineHeight
	update();
	
	//this could be a default...
	setText("edit this");
	
	//this is a fix to a bug that i don't quite understand...
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	
	windowController = [[STextController alloc] initWithWindowNibName:@"STextWindow"];
	[windowController setUid: i];
	[windowController setParent:this];
	[windowController showWindow:nil];
	[pool drain];
	
	updateWindow();
	
}

SText::~SText() {
	[windowController release];

	printf("stext deconstructed\n");
	
}


void SText::draw() {
	
	ofPushMatrix();
	ofTranslate(pos.x, pos.y);
		
	if(focus) drawBoundingBox();
		
	
	
	//to place the characters nicely, we have to draw each character...
	//...character by character, one by one 
	//and place each character where wrapLines() says
	//int j = 0;
//	for (int i = 0; i < text.length(); i++) {
//
//		ofPushMatrix();
//		ofTranslate(refPoints[j].x, refPoints[j].y, 0);
//		if (text[i] != ' ') {
//		
//			int cy = ((unsigned char)text[i]) - NUM_CHARACTER_TO_START;
//			ttf.drawCharAsShape(cy, 0, 0);
//			j++;
//		}
//		
//		ofPopMatrix();
//		
//	}
	
	ofBeginShape();
	
	for (int i = 0; i < textPoints.size(); i++) {
		
		ofNoFill();
		ofSetColor(0, 0, 0);
		
		if (textPoints[i].x == PEN_UP_POINT) {
			ofNextContour(true);
		} 
		else if (textPoints[i].x == PEN_DOWN_POINT) {}
		else {
			ofVertex(textPoints[i].x, textPoints[i].y);
			
			//ofNoFill();
			//ofSetColor(50, 100, 200);
			//ofCircle(textPoints[i].x, textPoints[i].y, 1);
		}

		
	}
	
	ofEndShape(true);
	
	ofPopMatrix();

}

void SText::findTextPoints() {
	
	vector<ofPoint> points;
	

	//textPoints.clear();
	
	int n = 0;
	int refn = 0;
	
	//loop through whole text
	while (n < text.length()) {
		
		ofTTFCharacter letter = ttf.getCharacterAsPoints(text[n]);
		
		for (int i = 0; i < letter.contours.size(); i++) {
			
			points.push_back(ofPoint(PEN_UP_POINT, 0));
			
			//move to first position
			points.push_back(ofPoint(letter.contours[i].pts[0] + refPoints[refn]));
			
			points.push_back(ofPoint(PEN_DOWN_POINT, 0));
			
			//add all points 
			for (int j = 1; j < letter.contours[i].pts.size(); j++) {
				points.push_back(ofPoint(letter.contours[i].pts[j] + refPoints[refn]));
			}
			
			//add last point, so we go full circle
			points.push_back(ofPoint(letter.contours[i].pts[0] + refPoints[refn]));
			
			
		}//end contour
	
		refn++;
		
		if (refn != (int) refPoints.size()) {
			points.push_back(ofPoint(PEN_UP_POINT, 0));
			points.push_back(ofPoint(refPoints[refn]));
		}
		
		n++;
		
		//if the next character is a space or a new line then skip it
		//NB refPoints' counter (refn) does not need to be incremented
		if (text[n] == '\n' || text[n] == ' ') {
			n++;
		}
		
	}// end while
	
	//now to get the stuff the right size we must scale everything by
	//an amount related to the window size (that can change)
	
	textPoints.clear();
	for (int i = 0; i < points.size(); i++) {
		textPoints.push_back(SPoint(points[i].x*1, points[i].y*1));
//		textPoints[i]*= SPoint(3, 3);
	}
		
}

void SText::update() {
	
	ttf.loadFont("/Library/Fonts/" + fontName + ".ttf", fontSize, true, true, true);

	lineHeight = ttf.getLineHeight();
	genCharWidth = lineHeight/3;
	
	wrapLines();
	setYDim();
	
	findTextPoints();
	
	printf("n characters = %i\n", ttf.bFullCharacterSet);
}


void SText::setText(string s) {
	text = s;
	wrapLines();
	setYDim();
}

void SText::setFont(string fontname) {
	fontName = fontname;
	update();
	
	//if character set cannot be loaded properly,
	//resort to default, Georgia
	if (!ttf.bLoadedOk) {
		ttf.loadFont("/Library/Fonts/Georgia.ttf", fontSize, true, true, true);
		[windowController fontLoadError];
	}
	else {
		[windowController fontLoaded];
	}

}

void SText::setFontSize(int s) {
	fontSize = s;
	update();
}

void SText::hello() {
	printf("hello from SText\n");
}


//this method wraps lines around a given box: given by the ofPoint: dim
//it wraps a word (i.e. places on the next line) if the first letter of
//the next word is over the x dimension of the box + a generic character width (lineHeight/3)
void SText::wrapLines() {
		
	int lus = 0; //letters until space
	int tll = 0; //temp letter length
	int ls = 0; //last space
	
	//get the reference points
	ttf.getReferencePoints(text, refPoints);
	
	for (int i = 0; i < text.size(); i++) {
		
		if (refPoints[lus].x > (dim.x + genCharWidth)) {
			
			int k = refPoints[ls].x;
			//reset the new lines to spaces
			for (int j = ls; j < refPoints.size(); j++) {
				refPoints[j].x = refPoints[j].x - k;
				refPoints[j].y += lineHeight;
			}
		} //end if				
		
		
		if (text[i] == ' ') {
			ls = lus; //set position of last space
		} 
		else {
			//add a lineHeight to all characters so the origin for each text box is the 
			//top left corner, not the top left corner plus a lineHeight
			refPoints[lus].y += lineHeight;
			lus++; //only increment if the character isn't a space
		}
	}
	
	
	
}
	
void SText::setYDim() {
	if (text == "") {
		dim.y = lineHeight*1.2;
	}
	else {
		dim.y = refPoints.back().y + (lineHeight*0.2); 
	}
}

void SText::updateWindow() {
	[windowController updatePosFields:pos.x:pos.y];
	[windowController updateDimFields:dim.x :dim.y];
	[windowController updateMainTextField:text];
	wrapLines();
	setYDim();
	findTextPoints();
}

void SText::giveAllPoints(vector<SPoint> &points) {

	for (int i = 0; i < textPoints.size(); i++) {
		points.push_back(textPoints[i]);
	}

}
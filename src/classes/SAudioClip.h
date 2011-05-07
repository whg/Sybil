/*
 *  SAudioClip.h
 *  Sybil
 *
 *  Created by Will Gallia on 07/05/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

#ifndef _SAUDIOCLIP
#define _SAUDIOCLIP

#include "GLee.h"
#import <Cocoa/Cocoa.h>
#include "ofMain.h"
#include "STypes.h"
#include "SItem.h"
#import "SAudioClipController.h"

@class SAudioClipController;

class SAudioClip : public SItem {

private:
	vector<float> rawAudio;
	vector<SPoint> points;
	
	SAudioClipController *windowController;
	
public:
	SAudioClip(int i);
	~SAudioClip();
	
	void draw();
	void update();
	void updateWindow();
	
	void audioReceived(float* input);
	void scaleAudio();
	
	void giveAllPoints(vector<SPoint> &points);

};

#endif
/*
 *  SImage.h
 *  Sybil
 *
 *  Created by Will Gallia on 21/03/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _SIMAGE
#define _SIMAGE

@class SImageController;

#include "ofMain.h"
#include "SItem.h"
#import <Cocoa/Cocoa.h>
#include "SImageController.h"



class SImage : public SItem {
	
private:
	ofImage *baseImage;
	SImageController *windowController;
	
public:
	SImage();
	SImage(int i);
	~SImage();
	
	
	
};


#endif
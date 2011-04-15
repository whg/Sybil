//
//  SMenuController.m
//  Sybil
//
//  Created by Will Gallia on 04/04/2011.
//  Copyright 2011 . All rights reserved.
//

#import "SMenuController.h"
//#include "ofMain.h"


@implementation SMenuController

- (id) init {
	
	if (self = [super init]) {
		
		previewPtr = (SPreview*) ofGetAppPtr();
		
	}
	
	return self;
}

- (IBAction) addText: (id) sender {
	previewPtr->addTextItem();
	
}

- (IBAction) addImage: (id) sender {
	previewPtr->addImageItem();
	
}

- (IBAction) changeToPreview: (id) sender {
	previewPtr->setMode(0);
	
}


- (IBAction) changeToTerminal: (id) sender {
	previewPtr->setMode(1);
	
}


@end

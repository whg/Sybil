//
//  SMenuController.m
//  Sybil
//
//  Created by Will Gallia on 04/04/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
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


- (IBAction)showOpenPanel:(id)sender
{
	NSOpenPanel *op = [NSOpenPanel openPanel];
	
	NSLog(@"apparently opened");
	
}

//- (IBAction) addText: (id) sender {
//	previewPtr->addImageItem();
//	
//}

@end

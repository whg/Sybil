//
//  SMenuController.m
//  Sybil
//
//  Created by Will Gallia on 04/04/2011.
//  Copyright 2011 . All rights reserved.
//

#import "SMenuController.h"

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
	
	//open a NSOpenPanel window
	NSOpenPanel *op = [NSOpenPanel openPanel];
	
	//display the window
	int result = [op runModal];
	
	//if ok is pressed load the chosen image
	if (result == NSOKButton) {
		NSURL *u = [op URL];
		NSString *p = [[op URL] path];
		
		previewPtr->addImageItem( [p UTF8String] );
		
		[u release];
		[p release];
	}
	
}

- (IBAction) changeToPreview: (id) sender {
	previewPtr->setViewMode(0);
	[previewMode setState:NSOnState];
	[terminalMode setState:NSOffState];
	
}


- (IBAction) changeToTerminal: (id) sender {
	previewPtr->setViewMode(1);
	[previewMode setState:NSOffState];
	[terminalMode setState:NSOnState];
}


@end

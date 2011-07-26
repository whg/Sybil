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
		
	}
	
}

- (IBAction) addAudioClip: (id) sender {
	previewPtr->addAudioClipItem();	
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

- (IBAction) plotEverything: (id) sender {

	previewPtr->plotEverything();
	
}

- (IBAction) changeLayoutToA4Landscape: (id) sender {
	previewPtr->setLayout(A4LANDSCAPE);
	
	[self resetLayoutMenu];
	[A4Landscape setState:NSOnState];
}

- (IBAction) changeLayoutToA4Portrait: (id) sender {
	previewPtr->setLayout(A4PORTRAIT);
	
	[self resetLayoutMenu];
	[A4Portrait setState:NSOnState];
}

- (IBAction) changeLayoutToA3Landscape: (id) sender {
	previewPtr->setLayout(A3LANDSCAPE);
	
	[self resetLayoutMenu];
	[A3Landscape setState:NSOnState];
}

- (IBAction) changeLayoutToA3Portrait: (id) sender {
	previewPtr->setLayout(A3PORTRAIT);
	
	[self resetLayoutMenu];
	[A3Portrait setState:NSOnState];
}


- (void) resetLayoutMenu {
	[A4Landscape setState:NSOffState];
	[A4Portrait setState:NSOffState];
	[A3Landscape setState:NSOffState];
	[A3Portrait setState:NSOffState];
}



// this doesn't belong to the the menu... (progress window)...
- (IBAction) cancelDrawing: (id) sender {

	previewPtr->cancelDrawing();
	printf("cancel drawing called\n");
}

@end

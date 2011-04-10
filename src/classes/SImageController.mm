//
//  SImageController.m
//  Sybil
//
//  Created by Will Gallia on 04/04/2011.
//  Copyright 2011 . All rights reserved.
//
#include "SImage.h"
#include "SPreview.h"
#import "SImageController.h"


@implementation SImageController

// init...
- (void) loadWindow{
	
	[super loadWindow];
	
}

- (IBAction)openFile:(id)sender {
	NSOpenPanel *op = [NSOpenPanel openPanel];
	
	//display the window
	int result = [op runModal];
	
	//if ok is pressed load the chosen image
	if (result == NSOKButton) {
		NSURL *u = [op URL];
		NSString *p = [[op URL] path];
		itemPtr->loadImage([p UTF8String]);
		[u release];
		[p release];
	}
	//if nothing is selected remove item...
	else {
		previewPtr->removeItem(uid);
	}
	
}

//very simple, allows you to toggle a fixed aspect ratio
- (IBAction) fixAspectRatio: (id) sender {
	
	if ([sender state] == 1) {
		((SImage*)itemPtr)->fixAspectRatio = true;
	} else {
		((SImage*)itemPtr)->fixAspectRatio = false;
	}
}

- (IBAction) showOriginalImage: (id) sender {
	
	NSLog(@"state = %i", [sender state]);
	
}

- (IBAction) removeSelf: (id) sender {
	NSLog(@"remove self from simage controller");
	[self close];
	[super removeSelf:nil];
}

- (void) finalize {
	
	NSLog(@"finalized from SImageController");
	[super finalize];
	
}



@end
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
	
	//this doesn't work!!!! WHY!!!!!????!!!!
	NSArray* types = [NSArray arrayWithObjects:@"jpg", @"JPG", @"PNG", @"png", nil];
	[op setCanChooseFiles:YES];
	[op setCanChooseDirectories:NO];
	[op setAllowsMultipleSelection:NO];
	[op setAllowedFileTypes:types];
	//display the window
	int result = [op runModal];
	
	//if ok is pressed load the chosen image
	if (result == NSOKButton) {
		NSURL *u = [op URL];
		NSString *p = [[op URL] path];
		((SImage*)itemPtr)->loadImage( [p UTF8String] );
		[u release];
		[p release];
		
		[self setMessageLabel:@""];
	}
	//if nothing is selected remove item...
	else {
		previewPtr->removeItem(uid);
	}
		
}

//very simple, allows you to toggle a fixed aspect ratio
- (IBAction) fixAspectRatio: (id) sender {
	
	if ( [sender state] == 1) {
		((SImage*)itemPtr)->setFixAspectRatio(true);
	} else {
		((SImage*)itemPtr)->setFixAspectRatio(false);
	}
	itemPtr->update();
}

- (IBAction) showOriginalImage: (id) sender {
	
	if ( [sender state] == 1) {
		((SImage*)itemPtr)->drawOriginalImage(true);
	} else {
		((SImage*)itemPtr)->drawOriginalImage(false);
	}
	itemPtr->update();
}

- (IBAction) baseThresholdChanged: (id) sender {
	
	((SImage*)itemPtr)->setBaseThreshold( [sender floatValue] );	
	itemPtr->update();
}

- (IBAction) numOfLinesChanged: (id) sender {
	
	//using a very cheap method here... the index + 1... pretty bad form...
	//... feel like i should bind an array to the popup button... but time is running out...
	((SImage*)itemPtr)->setNumberOfLines(((int)[sender indexOfSelectedItem] )+1);
	itemPtr->update();
}

- (IBAction) lineSpacingChanged: (id) sender {

	((SImage*)itemPtr)->setLineSpacing( [sender floatValue] );
	itemPtr->update();
}

- (IBAction) minimumAreaChanged: (id) sender {
	
	((SImage*)itemPtr)->setMinArea( [sender floatValue] );
	itemPtr->update();
}

- (IBAction) enableSmoothingChanged: (id) sender {
	
	if ( [sender state] ) {
		((SImage*)itemPtr)->enableSmoothing(true);
	} else {
		((SImage*)itemPtr)->enableSmoothing(false);
	}
	itemPtr->update();
}

- (IBAction) smoothingRadiusChanged: (id) sender {

	((SImage*)itemPtr)->setSmoothingRadius( [sender intValue] );
	itemPtr->update();
}

- (IBAction) skipPointsChanged: (id) sender {
	//same as numoflines...
	((SImage*)itemPtr)->setSkipPoints(((int)[sender indexOfSelectedItem] )+1);
	itemPtr->update();
}

- (IBAction) styleChanged: (id) sender {
	
	((SImage*)itemPtr)->setStyle([[sender titleOfSelectedItem] UTF8String]);
	itemPtr->update();
}

- (IBAction) styleSliderChanged: (id) sender {

	((SImage*)itemPtr)->setStyleParameter([sender floatValue]);
	itemPtr->update();
}

- (void) updateNumPoints:(int)n {

	[numPoints setIntValue:n];
}

- (void) showStyleSlider:(BOOL)show {

	[styleSlider setEnabled:show];
}

- (void) setMessageLabel:(NSString *)message {

	[messageLabel setStringValue:message];
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
//
//  SAudioClipWindowController.m
//  Sybil
//
//  Created by Will Gallia on 07/05/2011.
//  Copyright 2011 . All rights reserved.
//

#import "SAudioClipController.h"
#include "SPreview.h"

@implementation SAudioClipController


- (void) loadWindow{
	
	[super loadWindow];
	
}

- (IBAction) startPressed: (id) sender {
	
	//make sure the current audio is in focus
	previewPtr->setFocus(uid);
	previewPtr->setAudioNeeded(true);
}

- (IBAction) stopPressed: (id) sender {
	previewPtr->setAudioNeeded(false);
}

- (IBAction) resetPressed: (id) sender {
}


- (IBAction) removeSelf: (id) sender {
	NSLog(@"remove self from saudioclip controller");
	[self close];
	[super removeSelf:nil];
}



@end

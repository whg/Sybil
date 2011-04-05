//
//  SImageController.m
//  Sybil
//
//  Created by Will Gallia on 04/04/2011.
//  Copyright 2011 . All rights reserved.
//

#import "SImageController.h"


@implementation SImageController

- (void) loadWindow{
	
	[super loadWindow];
	
}

- (IBAction)openFile:(id)sender {
	NSOpenPanel *op = [NSOpenPanel openPanel];
	int result = [op runModal];
	if (result == NSOKButton) {
		NSLog(@"ok pressed");
		NSURL *u = [op URL];
		NSString *p = [[op URL] path];
		itemPtr->loadImage([p UTF8String]);
		[u release];
		[p release];
		
	}
	NSLog(@"apparently opened");
	
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

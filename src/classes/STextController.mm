//
//  STextController.m
//  Sybil
//
//  Created by Will Gallia on 07/03/2011.
//  Copyright 2011 . All rights reserved.
//

#include "SItem.h"
#import "STextController.h"


@implementation STextController


- (void) loadWindow{
		
	[super loadWindow];
	
}


- (IBAction) mainTextFieldChanged: (id) sender {
	itemPtr->setText([[sender stringValue] UTF8String]);
}

- (void) updateMainTextField:(string)s {
	mainText.stringValue = [NSString stringWithUTF8String:s.c_str() ];
}

- (IBAction) setFont: (id) sender {
	NSLog(@"set text and value = %@", sender);
}

- (IBAction) removeSelf: (id) sender {
	NSLog(@"remove self from stext controller");
	[self close];
	[super removeSelf:nil];
}

- (void) dealloc {
	[mainText release];
	NSLog(@"released from text controller");
	
	[super dealloc];
}
	


@end

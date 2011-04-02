//
//  STextController.m
//  Sybil
//
//  Created by Will Gallia on 07/03/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "STextController.h"

@implementation STextController


- (void) loadWindow{
	
	[super loadWindow];
	
}

- (void) setParent:(SText *)p {
	textPtr = p;
}

- (IBAction) textFieldChanged: (id) sender {

	textPtr->setText([[sender stringValue] UTF8String]);
}

- (IBAction) setFont: (id) sender {
	NSLog(@"set text and value = %@", sender);
}

- (int) uid {
	return uid;
}

- (void) set_uid: (int) i {
	uid = i;
}

- (void) dealloc {
		
	[textfield release];
	
	[super dealloc];
}

@end

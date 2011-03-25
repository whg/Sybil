//
//  STextController.m
//  Sybil
//
//  Created by Will Gallia on 07/03/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "STextController.h"



@implementation STextController

//
//- (id) init {
//	
//	if(self = [super init]) {
//		//previewPtr = (SPreview*) ofGetAppPtr();
//		[textfield sizeToFit]; //this doesn't work
//	}
//
//	
//	return self;
//}

- (void) loadWindow {

	[super loadWindow];
	
}

- (IBAction) textFieldChanged: (id) sender {
//	NSLog(@"text = %@", [sender stringValue]);
//	printf("sec text = %s\n", [[sender stringValue] UTF8String]);
	
	//previewPtr->setText([[sender stringValue] UTF8String]);
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
	
	[super dealloc];
}

@end

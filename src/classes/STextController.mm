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
		
	previewPtr = (SPreview*) ofGetAppPtr();
	[super loadWindow];
	
}

- (void) setParent:(SText *)p {
	textPtr = p;
}

- (IBAction) mainTextFieldChanged: (id) sender {
	textPtr->setText([[sender stringValue] UTF8String]);
}

- (IBAction) xposChanged: (id) sender {
	textPtr->setPos([sender intValue], -1);
}

- (IBAction) yposChanged: (id) sender {
	textPtr->setPos(-1, [sender intValue]);
}

- (IBAction) widthChanged: (id) sender {
	textPtr->setDim([sender intValue], -1);
}

- (IBAction) heightChanged: (id) sender {
	textPtr->setDim(-1, [sender intValue]);
}

- (void) updatePosFields:(int)x :(int)y {
	
	xpos.intValue = x;
	ypos.intValue = y;
	
}

- (void) updateDimFields:(int)w: (int)h {
	width.intValue = w;
	height.intValue = h;
}

- (void) updateMainTextField:(string)s {
	mainText.stringValue = [NSString stringWithUTF8String:s.c_str() ];
}

- (IBAction) setFont: (id) sender {
	NSLog(@"set text and value = %@", sender);
}

- (int) uid {
	return uid;
}

- (void) setUid:(int) i {
	uid = i;
}

- (void) removeSelf:(id)sender {

	previewPtr->removeItem(uid);

}

- (void) finalize {
	[mainText release];
	[xpos release];
	[ypos release];
	[width release];
	[height release];
	NSLog(@"released from controller");
	
	[super finalize];
}
	


@end

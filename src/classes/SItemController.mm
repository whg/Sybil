//
//  SItemController.m
//  Sybil
//
//  Created by Will Gallia on 04/04/2011.
//  Copyright 2011 . All rights reserved.
//

class SItem;
class SPreview;
@class SItemController;

#include "SItem.h"
#include "SPreview.h"
#import <Cocoa/Cocoa.h>
#import "SItemController.h"


@implementation SItemController

// - - - INIT - - -

- (void) loadWindow{
	
	previewPtr = (SPreview*) ofGetAppPtr();
	[super loadWindow];
	
}

- (void) setParent:(SItem*)p {
	itemPtr = p;
}

// - - - ACTIONS - - -

- (IBAction) xposChanged: (id) sender {
	itemPtr->setPos([sender intValue], -1);
}

- (IBAction) yposChanged: (id) sender {
	itemPtr->setPos(-1, [sender intValue]);
}

- (IBAction) widthChanged: (id) sender {
	itemPtr->setDim([sender intValue], -1);
}

- (IBAction) heightChanged: (id) sender {
	itemPtr->setDim(-1, [sender intValue]);
}

- (void) updatePosFields:(int)x :(int)y {
	
	xpos.intValue = x;
	ypos.intValue = y;
	
}

- (void) updateDimFields:(int)w: (int)h {
	width.intValue = w;
	height.intValue = h;
}

// - - - UID - - -

- (int) uid {
	return uid;
}

- (void) setUid:(int) i {
	uid = i;
}

//- - - REMOVE - - -

- (void) removeSelf:(id)sender {
	
	previewPtr->removeItem(uid);
	
}

- (void) dealloc {
	[window close];
	[xpos release];
	[ypos release];
	[width release];
	[height release];
	NSLog(@"released from item controller");
	
	[super dealloc];
}



@end

//
//  SItemController.h
//  Sybil
//
//  Created by Will Gallia on 04/04/2011.
//  Copyright 2011 . All rights reserved.
//


class SItem;
class SPreview;
@class SItemController;

#include "SItem.h"
//#include "SPreview.h"
#import <Cocoa/Cocoa.h>


@interface SItemController : NSWindowController {
	IBOutlet NSTextField *xpos;
	IBOutlet NSTextField *ypos;
	IBOutlet NSTextField *width, *height;
	NSWindow *window;
	SItem *itemPtr;
	SPreview *previewPtr;
	int uid;
}

- (void) getPreviewPtr;
- (void) setParent: (SItem*) p;

- (void) updatePosFields: (int) x : (int) y;
- (void) updateDimFields: (int) w : (int) h;

- (int) uid;
- (void) setUid: (int) i;

- (IBAction) xposChanged: (id) sender;
- (IBAction) yposChanged: (id) sender;
- (IBAction) widthChanged: (id) sender;
- (IBAction) heightChanged: (id) sender;

- (IBAction) removeSelf: (id) sender;

@end
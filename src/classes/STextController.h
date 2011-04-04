//
//  STextController.h
//  Sybil
//
//  Created by Will Gallia on 07/03/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SText.h"
#include "SPreview.h"
#import <Cocoa/Cocoa.h>


class SText;
class SPreview;

@interface STextController : NSWindowController {
	IBOutlet NSTextField *mainText;
	IBOutlet NSTextField *xpos;
	IBOutlet NSTextField *ypos;
	IBOutlet NSTextField *width, *height;
	NSWindow *window;
	SText *textPtr;
	SPreview *previewPtr;
	int uid;
}

//setters
- (void) setParent: (SText*) p;


- (void) updatePosFields: (int) x : (int) y;
- (void) updateDimFields: (int) w : (int) h;
- (void) updateMainTextField: (string) s;

- (int) uid;
- (void) setUid: (int) i;

- (IBAction) xposChanged: (id) sender;
- (IBAction) yposChanged: (id) sender;
- (IBAction) widthChanged: (id) sender;
- (IBAction) heightChanged: (id) sender;

- (IBAction) mainTextFieldChanged: (id) sender;
- (IBAction) setFont: (id) sender;

- (IBAction) removeSelf: (id) sender;

@end

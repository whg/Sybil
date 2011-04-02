//
//  STextController.h
//  Sybil
//
//  Created by Will Gallia on 07/03/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

//#include "SPreview.h"
#include "SText.h"
#import <Cocoa/Cocoa.h>


class SText;

@interface STextController : NSWindowController {
	IBOutlet NSTextField *textfield;
	SText *textPtr;
//	SPreview *previewPtr;
	int uid;
}

- (void) setParent: (SText*) p;

- (int) uid;
- (void) set_uid: (int) i;

- (IBAction) textFieldChanged: (id) sender;
- (IBAction) setFont: (id) sender;

@end

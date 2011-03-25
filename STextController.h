//
//  STextController.h
//  Sybil
//
//  Created by Will Gallia on 07/03/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SPreview.h"
#import <Cocoa/Cocoa.h>



@interface STextController : NSWindowController {
	//SPreview *previewPtr;
	IBOutlet NSTextField *textfield;
	
	int uid;
}

- (int) uid;
- (void) set_uid: (int) i;

- (IBAction) textFieldChanged: (id) sender;
- (IBAction) setFont: (id) sender;

@end

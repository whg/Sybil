//
//  SAudioClipWindowController.h
//  Sybil
//
//  Created by Will Gallia on 07/05/2011.
//  Copyright 2011 . All rights reserved.
//

#include "SItemController.h"
#include "GLee.h"
#import <Cocoa/Cocoa.h>

@interface SAudioClipController : SItemController {
	NSButton* startButton, *stopButton, *resetButton, *deleteButton;
}
	 
- (IBAction) startPressed: (id) sender;
- (IBAction) stopPressed: (id) sender;
- (IBAction) resetPressed: (id) sender;
- (IBAction) removeSelf: (id) sender;
	 
	 
@end

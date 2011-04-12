//
//  STextController.h
//  Sybil
//
//  Created by Will Gallia on 07/03/2011.
//  Copyright 2011 . All rights reserved.
//


#import "SItemController.h"
#import <Cocoa/Cocoa.h>
#include "SText.h"

@interface STextController : SItemController {
	IBOutlet NSTextField *mainText;
}

- (void) updateMainTextField: (string) s;
- (IBAction) mainTextFieldChanged: (id) sender;
- (IBAction) setFont: (id) sender;


//inherited
- (IBAction) removeSelf: (id) sender;

@end

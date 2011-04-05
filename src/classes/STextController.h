//
//  STextController.h
//  Sybil
//
//  Created by Will Gallia on 07/03/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#import "SItemController.h"
#import <Cocoa/Cocoa.h>


@interface STextController : SItemController {
	IBOutlet NSTextField *mainText;
}

- (void) updateMainTextField: (string) s;
- (IBAction) mainTextFieldChanged: (id) sender;
- (IBAction) setFont: (id) sender;


@end

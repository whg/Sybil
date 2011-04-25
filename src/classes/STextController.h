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

//#include <sys/types.h>
//#include <dirent.h>

@interface STextController : SItemController {
	IBOutlet NSTextField *mainText;
	IBOutlet NSPopUpButton *fontSelection;
	IBOutlet NSTextField *label;
	IBOutlet NSComboBox *fontSizeBox;
	
	NSMutableArray *fontList;
	NSString *defaultFont;
}

- (void) getAvailableFonts;

- (void) updateMainTextField: (string) s;
- (IBAction) mainTextFieldChanged: (id) sender;
- (IBAction) setFont: (id) sender;
- (IBAction) setFontSize: (id) sender;

- (void) fontLoaded;
- (void) fontLoadError;


//inherited
- (IBAction) removeSelf: (id) sender;

@end

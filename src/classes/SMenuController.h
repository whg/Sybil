//
//  SMenuController.h
//  Sybil
//
//  Created by Will Gallia on 04/04/2011.
//  Copyright 2011 . All rights reserved.
//

#include "SPreview.h"
#include "SConstants.h"
#import <Cocoa/Cocoa.h>

class SPreview;


@interface SMenuController : NSObject {
	layoutTypes layout;
	SPreview* previewPtr;
	IBOutlet NSMenuItem* previewMode;
	IBOutlet NSMenuItem* terminalMode;
	IBOutlet NSMenuItem* plotMenu;
	IBOutlet NSMenuItem* A4Landscape;
	IBOutlet NSMenuItem* A4Portrait;
	IBOutlet NSMenuItem* A3Landscape;
	IBOutlet NSMenuItem* A3Portrait;
}

- (IBAction) addText: (id) sender;
- (IBAction) addImage: (id) sender;
- (IBAction) addAudioClip: (id) sender;
- (IBAction) changeToPreview: (id) sender;
- (IBAction) changeToTerminal: (id) sender;
- (IBAction) plotEverything: (id) sender;

- (IBAction) changeLayoutToA4Landscape: (id) sender;
- (IBAction) changeLayoutToA4Portrait: (id) sender;
- (IBAction) changeLayoutToA3Landscape: (id) sender;
- (IBAction) changeLayoutToA3Portrait: (id) sender;

- (void) resetLayoutMenu;

//this is for the progress window, i thought this was the best place to put it
- (IBAction) cancelDrawing: (id) sender;

@end

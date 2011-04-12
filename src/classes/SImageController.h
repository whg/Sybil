//
//  SImageController.h
//  Sybil
//
//  Created by Will Gallia on 04/04/2011.
//  Copyright 2011 . All rights reserved.
//

//#include "SItem.h"
//#include "SPreview.h"
#import "SItemController.h"
#import <Cocoa/Cocoa.h>


@interface SImageController : SItemController {
	
//	NSArray* noLinesSelection;
//	IBOutlet NSArrayController* arrayController;

}


- (IBAction) openFile: (id) sender;
- (IBAction) fixAspectRatio: (id) sender;
- (IBAction) showOriginalImage: (id) sender;
- (IBAction) baseThresholdChanged: (id) sender;
- (IBAction) numOfLinesChanged: (id) sender;
- (IBAction) lineSpacingChanged: (id) sender;
- (IBAction) minimumAreaChanged: (id) sender;
- (IBAction) enableSmoothingChanged: (id) sender;
- (IBAction) smoothingRadiusChanged: (id) sender;



- (IBAction) removeSelf: (id) sender;

@end

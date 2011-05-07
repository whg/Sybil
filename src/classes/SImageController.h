//
//  SImageController.h
//  Sybil
//
//  Created by Will Gallia on 04/04/2011.
//  Copyright 2011 . All rights reserved.
//

#import "SItemController.h"
#import <Cocoa/Cocoa.h>

@interface SImageController : SItemController {
	IBOutlet NSTextField* numPoints;
	IBOutlet NSSlider* styleSlider;
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
- (IBAction) skipPointsChanged: (id) sender;
- (IBAction) styleChanged: (id) sender;
- (IBAction) styleSliderChanged: (id) sender;

- (void) updateNumPoints: (int) n;
- (void) showStyleSlider: (BOOL) show;

- (IBAction) removeSelf: (id) sender;

@end

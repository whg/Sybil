//
//  SMenuController.h
//  Sybil
//
//  Created by Will Gallia on 04/04/2011.
//  Copyright 2011 . All rights reserved.
//

#include "SPreview.h"

#import <Cocoa/Cocoa.h>

class SPreview;


@interface SMenuController : NSObject {
	SPreview* previewPtr;

	
}

- (IBAction) addText: (id) sender;
- (IBAction) addImage: (id) sender;

//- (IBAction)showOpenPanel:(id)sender;


@end

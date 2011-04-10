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
	
	
}

- (IBAction) openFile: (id) sender;
- (IBAction) fixAspectRatio: (id) sender;
- (IBAction) showOrignalImage: (id) sender;

- (IBAction) removeSelf: (id) sender;

@end

//
//  STextController.h
//  Sybil
//
//  Created by Will Gallia on 07/03/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

//#include "GLee.h" //again, stupid hack
#include "SPreview.h"
#import <Cocoa/Cocoa.h>



@interface STextController : NSObject {
	SPreview *previewPtr;
	IBOutlet NSTextField *textfield;
	
}

- (IBAction) textFieldChanged: (id) sender;
@end

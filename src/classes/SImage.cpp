/*
 *  SImage.cpp
 *  Sybil
 *
 *  Created by Will Gallia on 21/03/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "SImage.h"

SImage::SImage(int i)
:SItem(i){
	printf("constructed SImage\n");
	
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	
	windowController = [[SImageController alloc] initWithWindowNibName:@"SImageWindow"];
	[windowController setUid: i];
	[windowController setParent:this];
	[windowController showWindow:nil];
	[pool drain];
	
}

SImage::SImage() {
}


SImage::~SImage() {
	
	printf("desconstructed from SImage\n");
	[windowController close];
}
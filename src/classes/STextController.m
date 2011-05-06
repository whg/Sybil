//
//  STextController.m
//  Sybil
//
//  Created by Will Gallia on 07/03/2011.
//  Copyright 2011 . All rights reserved.
//

#include "SItem.h"
#import "STextController.h"


@implementation STextController

-(void) awakeFromNib {
	
	defaultFont = [NSString stringWithString:@"Georgia"];
	
	fontList = [[NSMutableArray alloc] init];
	[self getAvailableFonts];

	[fontSelection addItemsWithTitles:fontList];
	
	[fontSelection selectItemWithTitle:defaultFont];
	
	//set label to be empty...
	[label setStringValue:@""];
	
	//do the font size box...
	NSMutableArray *sizes = [[NSMutableArray alloc] init];
	
	//NSArray *sizes = [[NSArray alloc] initWithObjects: @"1", @"2", @"3", @"4", nil];
	
	for (int i = 0; i < 11; i++) {
		NSNumber *n = [[NSNumber alloc] initWithInt: (int) pow(2, i) ];
		[sizes addObject:n];
	}
	
	//add items...
	[fontSizeBox addItemsWithObjectValues:sizes];
	
	//now customise fontSizeBox
	[fontSizeBox setNumberOfVisibleItems:10];
	[fontSizeBox setIntercellSpacing:NSMakeSize(3.0, 0.5)]; //this doesn't seem to work properly
}

- (void) loadWindow {
			
	[super loadWindow];
	
}

- (void) getAvailableFonts {
	
	DIR* dirPtr;
	struct dirent *dirp;
		
	//say the directories you want to look in for fonts
	string dir = "/Library/Fonts";

	//try and open directory
	if (dirPtr = opendir(dir.c_str())) {
		
		//read all files in directory
		while ((dirp = readdir(dirPtr)) != NULL) {
			//convert to NSString and add to array
			[fontList addObject:[ NSString stringWithCString:dirp->d_name ]];
		}
		//and close...
		closedir(dirPtr);
	}
	
	NSMutableIndexSet *indexSet;
	indexSet = [[NSMutableIndexSet alloc] init];
	
	//loop through array, 
	//removing files that are not ttf
	//renaming those that are to just name, no extension..
	
	for (int i = 0; i < fontList.count; i++) {
		NSString *element = [fontList objectAtIndex:i];
		NSRange r = [element rangeOfString:@".ttf"];
	
		//if contains .ttf
		if (r.length) {
			//remove .ttf from name
			[fontList replaceObjectAtIndex:i withObject:[element stringByReplacingOccurrencesOfString:@".ttf" withString:@""]];
		}
		//if does not contain .ttf remove from array
		else {
			[indexSet addIndex:i];
		}
		
		//get rid of . and ..
		if (element == @"." || element == @"..") {
			[indexSet addIndex:i];
		}
			 
	}
	
	//now remove all non ttf fonts
	[fontList removeObjectsAtIndexes:indexSet];
	
	//now sort alphabetically
	[fontList sortUsingSelector:@selector(compare:)];
	
}
	 
	 

- (IBAction) mainTextFieldChanged: (id) sender {
	
	((SText*)itemPtr)->setText([[sender stringValue] UTF8String]);
}

- (void) updateMainTextField:(string)s {
	
	mainText.stringValue = [NSString stringWithUTF8String:s.c_str() ];
}

- (IBAction) setFont: (id) sender {

	((SText*)itemPtr)->setFont( [[sender titleOfSelectedItem] UTF8String] );
}

- (IBAction) setFontSize: (id) sender {
	
	((SText*)itemPtr)->setFontSize([sender intValue]);
	
}

// - - - FONT LOADING - - -

- (void) fontLoaded {
	[label setStringValue:@""];
}

- (void) fontLoadError {

	//edit label
	[label setStringValue:@"Could not load font, default loaded"];
	
	//set font to default
	[fontSelection selectItemWithTitle:defaultFont];
	
	NSBeep();
	
}


// - - - REMOVING - - -

- (IBAction) removeSelf: (id) sender {
	NSLog(@"remove self from stext controller");
	[self close];
	[super removeSelf:nil];
}

- (void) dealloc {
	[mainText release];
	NSLog(@"released from text controller");
	
	[super dealloc];
}
	


@end

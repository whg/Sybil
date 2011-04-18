/*
 *  SConstants.h
 *  Sybil
 *
 *  Created by Will Gallia on 17/04/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

#ifndef _SCONSTANTS
#define _SCONSTANTS

#define PREVIEW_WIDTH 800
#define PREVIEW_HEIGHT 600

#define TERMINAL_WIDTH 600
#define TERMINAL_HEIGHT 400


enum viewModes {
	PREVIEW,
	TERMINAL
};

enum cursorTypes {
	NONE,
	MOVE,
	RESIZEX,
	RESIZEY,
	RESIZEBOTH
};




#endif
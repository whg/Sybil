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

#define NORMAL_FRAMERATE 30
#define SERIAL_FRAMERATE 500

#define COMMAND_CODE_PEN_DOWN 0
#define COMMAND_CODE_PEN_UP 1
#define COMMAND_CODE_MOVE_ABS 2
#define COMMAND_CODE_MOVE_REL 3
#define COMMAND_CODE_GET_POS 4
#define COMMAND_CODE_QUERY_DELAYED 5
#define COMMAND_CODE_EXECUTE_DELAYED 6

#define RX_BUFFER_FULL 5

#define SERIAL_DLE 0x10
#define SERIAL_STX 0x02
#define SERIAL_ETX 0x03


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
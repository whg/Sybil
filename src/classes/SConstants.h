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

#define PREVIEW_WIDTH 770
#define PREVIEW_HEIGHT 560

#define TERMINAL_WIDTH 600
#define TERMINAL_HEIGHT 400

#define NORMAL_FRAMERATE 30
#define SERIAL_FRAMERATE 600

#define COMMAND_CODE_PEN_DOWN 0
#define COMMAND_CODE_PEN_UP 1
#define COMMAND_CODE_MOVE_ABS 2
#define COMMAND_CODE_MOVE_REL 3
#define COMMAND_CODE_GET_POS 4
#define COMMAND_CODE_QUERY_DELAYED 5
#define COMMAND_CODE_EXECUTE_COMMANDS 6
#define COMMAND_CODE_CHANGE_STEP_DELAY 7
#define COMMAND_CODE_LAST_LOT 8
#define COMMAND_CODE_FINISH 9
#define COMMAND_CODE_NUM_COMMANDS 10

//these come from the plotter...
#define SEND_FOR_NEXT_COMMANDS 213
#define PLOTTER_FINISHED_DRAWING 182

#define RX_BUFFER_FULL 5
#define RX_SEND_NEXT 7


#define SERIAL_DLE 0x10
#define SERIAL_STX 0x02
#define SERIAL_ETX 0x03

#define PEN_UP_POINT -1
#define PEN_DOWN_POINT -2
#define CHANGE_DELAY_POINT -3


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
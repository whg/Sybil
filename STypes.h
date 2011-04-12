/*
 *  STypes.h
 *  Sybil
 *
 *  Created by Will Gallia on 09/04/2011.
 *  Copyright 2011 . All rights reserved.
 *
 */

#ifndef _STYPES
#define _STYPES

//basically ofPoint but with integers
class SPoint {
public:
	
	~SPoint() {}
	
	int x;
	int y;
	
	SPoint() {
		x = 0;
		y = 0;
	}
	
	SPoint(int _x, int _y) {
		x = _x;
		y = _y;
	}
	
	SPoint(const SPoint &p) {
		x = p.x;
		y = p.y;
	}
	
	void set(int _x, int _y) {
		x = _x;
		y = _y;
	} 
	
	
	
};


#endif
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

#include "ofTypes.h"

//basically ofPoint but with ints, ie. 16bit
//we need this for the microcontroller...
//they are not signed at this point so we can use
//pen up and down commands within an SPoint... 
//positions on the plotter cannot be negative...
class SPoint {
public:
	
	~SPoint() {}
	
	int x;
	int y;
	
	//constructors, quite a few...
	
	SPoint() {
		x = 0;
		y = 0;
	}
	
	SPoint(int _x, int _y) {
		x = (short int) _x;
		y = (short int) _y;
	}
	
	SPoint(float _x, float _y) {
		x = round(_x);
		y = round(_y);
	}
	
	SPoint(ofPoint p) {
		x = round(p.x);
		y = round(p.y);
	}
	
	SPoint(const SPoint &p) {
		x = p.x;
		y = p.y;
	}
	
	//setter
	
	void set(int _x, int _y) {
		x = _x;
		y = _y;
	} 
	
	//operators
	
	// - - - + - - -
	SPoint operator+(const SPoint &p) const {
		return SPoint(x+p.x, y+p.y);
	}
	
	SPoint & operator+=(const SPoint &p) {
		x+= p.x;
		y+= p.y;
		return *this;
	}
	
	
	
	// - - - * - - -
	SPoint operator*(const SPoint &p) const {
		return SPoint(x*p.x, y*p.y);
	}
	
	SPoint & operator*=(const SPoint &p) {
		x*= p.x;
		y*= p.y;
		return *this;
	}
	
	
	
};


#endif
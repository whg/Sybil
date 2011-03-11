#ifndef _SPREVIEW
#define _SPREVIEW

#include "GLee.h"
#import <Cocoa/Cocoa.h>
#include "ofMain.h"
#include "SText.h"

class SPreview : public ofBaseApp{
	

	public:
	
	~SPreview();

	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
			
	void setText(string s);

	
	float oneDecimalPoint(float x);
		
	
	SText *t;
	
	string tt;
	
//	string t;
};

//this is just a little helper, might use it...
inline float SPreview::oneDecimalPoint(float x) {
	x*= 10.0;	
	double ip;
	if (modf(x, &ip) > 0.5) x = ceil(x);
	else x = floor(x);
	x/= 10.0;
	return x;
}


#endif

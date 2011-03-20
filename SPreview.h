#ifndef _SPREVIEW
#define _SPREVIEW

#include "GLee.h"
#import <Cocoa/Cocoa.h>
#include "ofMain.h"
#include "SText.h"

class SText;

class SPreview : public ofBaseApp {
	

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
			
	void setFocus(int i);

	float oneDecimalPoint(float x);
	
	int idc; //id counter
	int fid; //focused id
	vector<SText *> t;
	
	//SText *t;
		
	string tt;
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

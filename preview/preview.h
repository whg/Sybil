#ifndef _PREVIEW
#define _PREVIEW

#include "ofMain.h"

class preview : public ofBaseApp{
	

	public:
	
	~preview();

	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
			
	float oneDecimalPoint(float x);
};

//this is just a little helper, might use it...
inline float preview::oneDecimalPoint(float x) {
	x*= 10.0;	
	double ip;
	if (modf(x, &ip) > 0.5) x = ceil(x);
	else x = floor(x);
	x/= 10.0;
	return x;
}


#endif

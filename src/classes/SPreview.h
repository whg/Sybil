#ifndef _SPREVIEW
#define _SPREVIEW

#include "GLee.h"
#import <Cocoa/Cocoa.h>
#include "ofMain.h"
#include "SItem.h"
#include "SText.h"
#include "SImage.h"

//SPreview* previewPtr;

//forward declare classes...
class SItem;
class SImage;
@class SItemController;

class SPreview : public ofBaseApp {
	
private:
	
	int idc; //id counter
	int fid; //focused id
	
	int ztrans;
	
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
	int getFocus();
	
	void setText(int i, string text);
	
	void hello();

	float oneDecimalPoint(float x);
	
	
	vector<SItem *> items;
	
	void addTextItem();
	void addImageItem();
	
	void removeItem(int i);
	
	
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

#ifndef _SPREVIEW
#define _SPREVIEW

#include "GLee.h"
#import <Cocoa/Cocoa.h>
#include "ofMain.h"
#include "SItem.h"
#include "SText.h"
#include "SImage.h"
#include "STerm.h"

//forward declare classes...
class SItem;
class SImage;
@class SItemController;
class STerm;

class SPreview : public ofBaseApp {
	
private:
	
	int idc; //id counter
	int fid; //focused id
	
	int ztrans;
	
	STerm* terminal;
	
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
	
	void setMode(int m);
			
	//these are where all the items are stored...
	vector<SItem *> items;
	
	void addTextItem();
	void addImageItem();
	
	void removeItem(int i);
	
	
	enum modes {
		PREVIEW,
		TERMINAL
	};
	
	modes mode;
	
};



#endif

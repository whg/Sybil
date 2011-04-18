#include "ofMain.h"
#include "ofAppGlutWindow.h"

#include "SPreview.h"
#include "SConstants.h"

// - + - + - + - + - + - + - + -

int main() {

	ofAppGlutWindow window;
	ofSetupOpenGL(&window, PREVIEW_WIDTH, PREVIEW_HEIGHT, OF_WINDOW);
	ofRunApp(new SPreview());

}

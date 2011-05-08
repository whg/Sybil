#include "ofMain.h"
#include "ofAppGlutWindow.h"

#include "SPreview.h"
#include "SConstants.h"

// - + - + - + - + - + - + - + -

int main() {

	ofAppGlutWindow window;
	ofSetupOpenGL(&window, PREVIEW_A3_LANDSCAPE_WIDTH, PREVIEW_A3_PORTRAIT_HEIGHT, OF_WINDOW);
	ofRunApp(new SPreview());

}

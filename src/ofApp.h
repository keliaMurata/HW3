#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "Bubble.h"

class ofApp : public ofBaseApp
{

	public:
		void setup();
		void update();
		void draw();

		//face tracker 
		ofVideoGrabber camera;
		ofxCv:: ObjectFinder finder;

		//bubbles
		ofLight pointLight;
		ofLight pointLight2; 
		ofMaterial material;

		ofPoint bubbleStart;
		float size; 
		float vel; 

		vector <Bubble> bubbles; 
};

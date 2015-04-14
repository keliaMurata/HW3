/*
	Kelia Murata 
	Face Toy program. Face tracking and 3D objects.  Bubbles rise from the bottom of the screen and float upwards, slidding away from the face and moving around it. 
*/

#include "ofApp.h"
#include "Bubble.h"

using namespace ofxCv;
using namespace cv; 

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(120);
	finder.setup("haarcascade_frontalface_alt2.xml");  //frontal face tracking 
	finder.setPreset(ObjectFinder:: Fast);
	finder.getTracker().setSmoothingRate(.3);
	camera.initGrabber(ofGetWindowSize().x, ofGetWindowSize().y);  //using computers camera

	
	//bubbles
	ofSetSmoothLighting(true);
	//camera 1 
	pointLight.setDiffuseColor( ofColor(160, 200, 250, 100));
	pointLight.setSpecularColor( ofColor(180, 250, 160, 100));
	pointLight.setPosition( 0, ofGetWindowHeight()/3, 500);

	//camera 2 
	pointLight2.setDiffuseColor(ofColor(250,165, 245, 100));
	pointLight2.setSpecularColor(ofColor(255, 100));
	pointLight2.setPosition(ofGetWindowWidth(), ofGetWindowHeight(), 200);

	//bubble shine 
	material.setShininess( 128);
	material.setSpecularColor( ofColor(235, 140, 230, 255));

	//how many sides to the circle 
	ofSetSphereResolution(24);
	
	//create 40 bubbles with random x location and size and store in a bubble vector 
	for( int i = 0; i < 100; i++)
	{
		bubbleStart = ofPoint (ofRandom(0, ofGetWindowWidth()), ofGetWindowHeight());
		size = ofRandom(10, 40);

		bubbles.push_back(Bubble(bubbleStart, size) );
	}
	
}

//--------------------------------------------------------------
void ofApp::update()
{
	//update the camera as the face moves 
	camera.update();
	if(camera.isFrameNew())
	{
		finder.update(camera);
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	camera.draw(0,0);

	//face tracking rectangle 
	for(int i = 0; i < finder.size(); i++) 
	{
		ofRectangle face = finder.getObjectSmoothed(i); 
		
		//check to see if bubble hitting face box 
		
		for( int k = 0; k < bubbles.size(); k++)
		{
			bubbles[k].update(face);
		}
		
		ofPushMatrix(); 
		ofTranslate(face.getPosition());
		//number of faces detected counter 
		ofDrawBitmapStringHighlight(ofToString(finder.getLabel(i)), 0, 0);
		ofLine(ofVec2f(), toOf(finder.getVelocity(i)) * 10);
		ofPopMatrix();
	}
	
	//bubble 
	ofEnableDepthTest(); // cant track face with this on?!?!

	ofEnableLighting();
	pointLight.enable();
	pointLight2.enable();
	material.begin();

	//draw the bubbles in the array 
	for(int b = 0; b < bubbles.size(); b++)
	{
		bubbles[b].draw();
	}
	ofDisableDepthTest();
	
}


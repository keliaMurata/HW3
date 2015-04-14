#ifndef BUBBLE_HEADER
#define BUBBLE_HEADER

#include "ofMain.h"
#include "ofApp.h"

class Bubble
{
    
public:
    
    ofPoint pos;
    ofPoint vel;
    float scale;
    
	//constructor 
    Bubble(ofPoint startPoint, float bubbleSize)
	{
		   pos = startPoint; 
		   scale = bubbleSize; 
		   vel = ofPoint( 0, ofRandom(-2,-.5)); 
    }

	void update(ofRectangle myFace)
	{
		float mid = myFace.x + myFace.width/2;
		
		if( ((pos.y - scale/2) - (myFace.y + myFace.height)) < 10)
		{
			cout << "hit the box" << endl;
			if( (pos.x >= mid) && (pos.x < myFace.x + myFace.width) )
			{
				pos.x = pos.x - (-2);
			}
			if( (pos.x < mid) && (pos.x > myFace.x))
			{
				pos.x = pos.x + (-2); 
			}
			else
			{
				pos += vel;
			}
		}

		/*
		if( (pos.y - scale/2) < myFace.y) //bubble passed top of screen 
		{
			pos.y = myFace.y + myFace.height + scale/2;  //restart at bottom 
			cout << "left screen" << endl; 
		}
		*/
		else
		{
			pos += vel;
		}
	}

	void draw()
	{
		ofDrawSphere(pos.x, pos.y, scale);
	}
};

#endif
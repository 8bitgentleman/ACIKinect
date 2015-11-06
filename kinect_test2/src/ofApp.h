#pragma once

#include "ofMain.h"
#include "ofxKinectCommonBridge.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofxKinectCommonBridge kinect;
		ofShader k4wShader;
		ofPlanePrimitive plane;

		float meshRadius;
		ofMesh mesh;

        int spinX;
        int spinY;
        ofLight light;
    
        float rotX;
        float rotY;
    
        ofEasyCam easyCam;
        ofVideoGrabber vidGrabber;
        int camWidth, camHeight;//puts it into pixel space
        ofPixels    vidPixels;
        ofImage image;
    
        ofColor c;
        float handDist;
		
};

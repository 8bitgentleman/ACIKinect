#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
	camWidth = 320;
    camHeight = 240;
    
    vidGrabber.setVerbose(true);
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(camWidth, camHeight, OF_PIXELS_BGRA);
    
    vidPixels.allocate(camWidth, camHeight, OF_PIXELS_RGB);
    
    light.enable(); //Enabling light source
    mesh.enableColors();

    //set a default color
    c = ofColor(250, 0, 0);

	//kinect stuff
	handDist = 1;
	kinect.initSensor();
	//kinect.initIRStream(640, 480);
	kinect.initColorStream(640, 480, true);
	kinect.initDepthStream(640, 480, true);
	kinect.initSkeletonStream(true);

	//simple start
	kinect.start();
	ofDisableAlphaBlending(); //Kinect alpha channel is default 0;
	ofSetWindowShape(1280, 480);
}

//--------------------------------------------------------------
void ofApp::update(){


	//kinect stuff
	kinect.update();
	if(kinect.isNewSkeleton()) {
        for( int i = 0; i < kinect.getSkeletons().size(); i++) 
        {
                // has a head? probably working ok then :)
            if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD) != kinect.getSkeletons().at(i).end())
            {
                // just get the first one
               //SkeletonBone headBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD)->second;
               //ofVec2f headScrenPosition( headBone.getScreenPosition().x, headBone.getScreenPosition().y);
				SkeletonBone lHand = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HAND_LEFT)->second;
               ofVec2f lHandScrenPosition( lHand.getScreenPosition().x, lHand.getScreenPosition().y);

				SkeletonBone rHand = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HAND_RIGHT)->third;
				ofVec2f rHandScreenPosition( rHand.getScreenPosition().x, rHand.getScreenPosition().y);
				//cerr << headBone;
				 handDist = ofDistSquared(lHand.getScreenPosition().x, lHand.getScreenPosition().y, rHand.getScreenPosition().x, rHand.getScreenPosition().y);
                
                return;
            }
        }
    }
    
    vidGrabber.update();
    float time = ofGetElapsedTimef();         //Get time
    float oldValue3d = ofNoise(meshRadius, time);
    
    
    //Change vertices
    
    for (int i=0; i<mesh.getNumVertices(); i++) {
        //---------------------------------//
        //set mesh color from video (even though it's not working right now)
        //---------------------------------//
        
        // Map i to the width and height of the image ( or video ) so that color can be sampled from the corresponding pixel
        int widthSampleIndex = ofMap(i, 0, mesh.getNumVertices(), 0, vidGrabber.getWidth());
        int heightSampleIndex = ofMap(i, 0, mesh.getNumVertices(), 0, vidGrabber.getHeight());
        
        if(vidGrabber.isFrameNew()){
            vidPixels = vidGrabber.getPixelsRef();
            
            //Grab color from pixel and set vertex color to it
            //c = vidPixels.getColor(widthSampleIndex, heightSampleIndex);
            image.setFromPixels(vidGrabber.getPixelsRef());
            c = image.getColor(widthSampleIndex, heightSampleIndex);
            cerr << ( c )<< endl ;
        }
        mesh.addColor(c);
        
        //---------------------------------//
        //displace vertice here using prelin noise ( After attempting this approach I think I would go with GLSL shaders next time.  While each point follows the noise with this there's no continuity from point to point so it looks random.
        //---------------------------------//
        
        ofVec3f p = mesh.getVertex( i );
        
        //Get Perlin noise value ( not sure which is best
        float value = ofNoise(100*i);
        float value2d = ofNoise(100 * i, time);
        float value3d = ofNoise(100 * i, i, time);
        
        ofVec3f center = mesh.getCentroid();
        float dist = center.distance(p);
        
        //find scale value so that the vertice can be moved
        float scaleValue = (dist*(oldValue3d))/dist;
        float oldValue3d = value3d;
        
        //Change coordinate of vertex in relation to the center of the sphere
        ofVec3f newP = p.scale(scaleValue*(10*handDist));
        //mesh.setVertex(i, newP);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
	vidGrabber.draw(20,20);
    
    easyCam.begin();
    // now draw
    ofPushMatrix();
    //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    //mesh.drawWireframe();
    mesh.drawFaces();
    ofPopMatrix();
    easyCam.end();
	/*
	//kinect stuff
	//kinect.draw(640,0);
	//kinect.drawDepth(0, 0);

	ofPushStyle();
	ofSetColor(255, 0, 0);
	ofSetLineWidth(3.0f);
	auto skeletons = kinect.getSkeletons();
	for(auto & skeleton : skeletons) {
		for(auto & bone : skeleton) {
			switch(bone.second.getTrackingState()) {
			case SkeletonBone::Inferred:
				ofSetColor(0, 0, 255);
				break;
			case SkeletonBone::Tracked:
				ofSetColor(0, 255, 0);
				break;
			case SkeletonBone::NotTracked:
				ofSetColor(255, 0, 0);
				break;
			}

			auto index = bone.second.getStartJoint();
			auto connectedTo = skeleton.find((_NUI_SKELETON_POSITION_INDEX) index);
			if (connectedTo != skeleton.end()) {
				ofLine(connectedTo->second.getScreenPosition(), bone.second.getScreenPosition());
			}

			ofCircle(bone.second.getScreenPosition(), 10.0f);
		}
	}
	ofPopStyle();*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

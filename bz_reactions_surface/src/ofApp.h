#pragma once

#include "ofMain.h"
#include "bzReaction.h"
#include "bzSeed.h"
#include "ofxGui.h"

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void exit();
		
    bzReaction bz;
    
    ofLight pointLight;
    
    ofEasyCam cam;
    
    ofParameter<int> drawingType;
    ofParameter<bool> bDebug;
    ofParameter<int> reactionSpeed;
    ofParameter<bool> bAddSpring;
    ofParameter<bool> bRunSimulation;
    ofParameter<bool> saveMeshes;
    ofParameter<bool> loadFullScreen;
    ofParameterGroup general;
    
    ofParameter<bool> reset;
    ofParameter<int> nSeeds;
    ofParameter<int> minDur; // ms
    ofParameter<int> maxDur;
    ofParameterGroup newReaction;
    
    ofxPanel panel;
    
};

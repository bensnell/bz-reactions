#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"

struct spring {
    
public:
    int px;
    int py;
    unsigned int startTime = 0; // ms
    unsigned int duration;      // ms
    unsigned long lastTimeOn;   // ms
};

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
		
    ofImage img;
    unsigned long nPixels;
    bool bDrawImgA = true;
    
    vector<spring> springs;
    int nSprings = 15;
    int minDuration = 100;
    int maxDuration = 2000;
    
    ofParameter<float> decayStrength;
    ofParameterGroup generalControls;
    
    ofxPanel panel;
    
    bool drawDebug = false;
};

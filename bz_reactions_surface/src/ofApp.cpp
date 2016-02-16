#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    general.setName("General");
    general.add(drawingType.set("Drawing Type", 1, 0, 2));
    general.add(bDebug.set("Debug", true));
    
    panel.setup();
    panel.add(bz.chemistry);
    panel.add(bz.rendering);
    panel.add(general);
    
    panel.loadFromFile("settings.xml");
    
    bz.loadSrf("blob.ply");
    bz.addSeeds(10, 100, 2000);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(120);
    
//    cam.begin();
    
    bz.drawSrf(drawingType);
    
//    cam.end();
    
    
    if (bDebug) {
        ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);
        panel.draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    panel.saveToFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'b') bDebug = !bDebug;
    if (key == 'f') ofToggleFullscreen();

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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

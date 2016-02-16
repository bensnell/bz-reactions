#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    general.setName("General");
    general.add(drawingType.set("Drawing Type", 1, 0, 2));
    general.add(bDebug.set("Debug", true));
    general.add(reactionSpeed.set("Reaction Speed", 2, 1, 10));
    general.add(bAddSpring.set("Add Another Spring", false));
    general.add(reset.set("Reset", false));
    general.add(bRunSimulation.set("Run Simulation", true));
    general.add(saveMeshes.set("Save PLY", false));
    
    panel.setup();
    panel.add(bz.chemistry);
    panel.add(bz.rendering);
    panel.add(general);
    
    panel.loadFromFile("settings.xml");
    
    bz.loadSrf("blob.ply");
    bz.addSeeds(10, 500, 3000);
    
//    ofEnableAlphaBlending();
    ofEnableDepthTest();
    
//    ofSetSmoothLighting(true);
//    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .85) );
//    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));

}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (saveMeshes) {
        bz.saveMeshes();
        saveMeshes = false;
    }
    
    if (reset) {
        bz.reset();
        reset = false;
    }
    
    if (bAddSpring) {
        bz.addSeeds(1);
        bAddSpring = false;
    }
    
    if (bRunSimulation && ofGetFrameNum() % reactionSpeed == 0) {
        bz.updateSeeds();
        bz.react();
        bz.updateMsrf();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(120);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() * 0.25, ofGetHeight()/2);
    bz.drawSrf(drawingType);
    ofPopMatrix();
    
//    ofEnableLighting();
//    pointLight.enable();
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() * 0.75, ofGetHeight()/2);
    bz.drawMsrf(drawingType);
    ofPopMatrix();
    
//    ofDisableLighting();
//    pointLight.draw();
    
    ofDisableDepthTest();
    if (bDebug) {
        panel.draw();
        ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);
    }
    ofEnableDepthTest();
    
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

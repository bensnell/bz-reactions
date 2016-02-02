#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // setup gui
    generalControls.setName("General Controls");
    generalControls.add(decayStrength.set("Decay Strength", 0.9, 0, 1));
    
    panel.setup();
    panel.add(generalControls);

    // initialize the images
    img.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
    
    nPixels = ofGetWidth() * ofGetHeight();
    
    // make all pixels 0
    for (long i = 0; i < nPixels; i++) {
        img.getPixels()[(int)i] = 0;
    }
    
    // initialize image A with a certain number of "springs" that produce a seed every duration
    for (int i = 0; i < nSprings; i++) {

        // add spring to vector
        spring thisSpring;
        thisSpring.px = ofRandom(ofGetWidth());
        thisSpring.py = ofRandom(ofGetHeight());
        thisSpring.duration = ofRandom(minDuration, maxDuration);
        thisSpring.lastTimeOn = 0;
        springs.push_back(thisSpring);
        
        // add spring to imageA
        int index = thisSpring.py * ofGetWidth() + thisSpring.px;
        img.getPixels()[index] = char(255); // make pure white
    }
    img.update();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // update the non-updated image with info from the most recently updated image
    ofPixelsRef pixels = img.getPixels();
    
    // update springs
    unsigned long timeNow = ofGetElapsedTimeMillis();
    for (int i = 0; i < nSprings; i++) {
        // if they turned on more than the duration ago, start a new seed in the same location
        if (timeNow - springs[i].lastTimeOn > springs[i].duration) {
            // reset lastTimeOn
            springs[i].lastTimeOn = timeNow;
            
            // add seed to pixels
            int index = springs[i].py * ofGetWidth() + springs[i].px;
            pixels[index] = char(255);
        }
    }
    
    /*
     Check every pixel against neighbors and apply a simple rule set. Let x = pixel brightness and b = decayStrength.
        1. If x < b && neighbor == 255 Then x = 1
        2. Otherwise, If x < 1, x = x * b
     */
    
    // first, multiply every pixel by decayStrength and save the indices of white pixels
    vector<int> frontIndices;
    for (int i = 0; i < nPixels; i++) {
        if (pixels[i] == 255) {
            frontIndices.push_back(i);
        }
        float thisColor = (float)pixels[i];
        pixels[i] = char(int(thisColor * decayStrength));
    }
    
    // for every pixel that used to be white, make any surrounding pixel white if its brightness is greater than or equal to the threshold
    int threshold = int(255. * decayStrength * decayStrength);
    for (int i = 0, end = frontIndices.size(); i < end; i++) {

        int index = frontIndices[i];
        
        int row = index / ofGetWidth();
        int col = index % ofGetWidth();
        
        bool leftEdge = col == 0;
        bool rightEdge = col == (ofGetWidth() - 1);
        bool topEdge = row == 0;
        bool bottomEdge = row == (ofGetHeight() - 1);

        for (int j = 0; j < 3; j++) { // rows
            
            // if top or bottom edge, continue
            if ((j == 0 && topEdge) || (j == 2 && bottomEdge)) continue;
            
            for (int k = 0; k < 3; k++) {
                if (j == 1 && k == 1) continue; // skip self // make this || it looks cool
                
                // if left or right edge, continue
                if ((k == 0 && leftEdge) || (k == 2 && rightEdge)) continue;
                
                
                // if this neighboring pixel has a brightness less than the threshold, make it white
                int thisIndex = index + (j-1) * ofGetWidth() + (k-1);
                
                if (pixels[thisIndex] < threshold) {
                    
                    pixels[thisIndex] = char(255);
                }
            }
        }
    }
    img.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    img.draw(0, 0);
    
    if (drawDebug) {
        panel.draw();
        ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'b') drawDebug = !drawDebug;

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



//
//
//
//
//        bool bFoundFront = false;
//
//
//        int row = i / ofGetWidth();
//        int col = i % ofGetWidth();
//
//        if (row == 0) { // top pixel
//
//
//
//        }
//
//
//        int nPixelsToCheck =
//
//
//
//
//        //        int itVert = (row != 0) - 2 * (row == ofGetHeight() - 1);
//
//        if (row == 0 || row == (ofGetHeight() - 1))
//
//
//
//
//        int row = -1;
//        int col = -1;
//        while(!bFoundFront) {
//
//            int index =
//            if (pixels[
//
//                ])
//
//
//
//        }
//
//
//
//
//    }
//
//
//
//
//
//
//    for (int i = 0; i < nPixels; i++) {
//        // check all neighbors for 1's
//        bool leftEdge = (i % ofGetWidth()) == 0;
//        bool rightEdge = (i % ofGetWidth()) == (ofGetWidth() - 1);
//        bool topEdge = int(i / ofGetWidth()) == 0;
//        bool bottomEdge = int(i / ofGetWidth()) == (ofGetHeight() - 1);
////        cout << "pixel number" << i << " " << (pixelsRef[i - 1] == 255) << " " << (pixelsRef[i + 1] == 255) << " " << (pixelsRef[i - ofGetWidth()] == 255) << " " << (pixelsRef[i + ofGetWidth()] == 255) << endl;
//
//        // check touching neighbors (not diagonals)
//        bool bTouchingOne = false;
//
////        if ((int)pixelsRef[int(i - 1)] == 255) cout << "left pixel is white" << endl;
////        cout << (int)pixelsRef[i] << endl;
//
//        if (!leftEdge) bTouchingOne |= (pixelsRef[i - 1] == 255);
//        if (!rightEdge) bTouchingOne |= (pixelsRef[i + 1] == 255);
//        if (!topEdge) bTouchingOne |= (pixelsRef[i - ofGetWidth()] == 255);
//        if (!bottomEdge) bTouchingOne |= (pixelsRef[i + ofGetWidth()] == 255);
//
////        if (bTouchingOne) cout << "true!" << endl;
//
//        if (pixelsRef[i] < 255) {
//            if (bTouchingOne) {
//                pixels[i] = 255;
//                continue;
//            }
//            pixels[i] = int((float)pixelsRef[i] * decayStrength);
//        } else {
//            pixels[i] = int((float)pixelsRef[i] * decayStrength);
//        }
//    }
//imgA.update();
//    imgB.update();

//    bDrawImgA = !bDrawImgA;




//// for every front index, check surrounding pixels for pixels which are LESS than (255 * decayStrength) and make them 255
//char threshold = char(255. * decayStrength);
//for (int i = 0, end = frontIndices.size(); i < end; i++) {
//    
//    int thisIndex = frontIndices[i];
//    
//    bool leftEdge = (thisIndex % ofGetWidth()) == 0;
//    bool rightEdge = (thisIndex % ofGetWidth()) == (ofGetWidth() - 1);
//    bool topEdge = int(thisIndex / ofGetWidth()) == 0;
//    bool bottomEdge = int(thisIndex / ofGetWidth()) == (ofGetHeight() - 1);
//    
//    
//    
//    
//    bool bTouchingOne = false;
//    
//    if (!leftEdge) bTouchingOne |= (pixels[thisIndex - 1] >= threshold);
//        if (!rightEdge) bTouchingOne |= (pixels[thisIndex + 1] >= threshold);
//            if (!topEdge) bTouchingOne |= (pixels[thisIndex - ofGetWidth()] >= threshold);
//                if (!bottomEdge) bTouchingOne |= (pixels[thisIndex + ofGetWidth()] >= threshold);
//                    
//                    if (bTouchingOne) {
//                        pixels[frontIndices[i]] = char(255);
//                        cout << "toucing one" << endl;
//                        }
//                        }

//bool moveHorz = true;
//bool moveRight = true;
//bool moveDown = false;
//int nPixelsRead = 0;
//
//while (nPixelsRead < 8) {
//    if (thisIndex / ofGetWidth() == 0) { // skip top pixels
//        nPixelsRead++;
//        continue;
//    } else if (thisIndex
//               }
//               
//               
//               
//               
//               // left pixel
//               
//               // left pixel
//               if ((thisIndex % ofGetWidth()) != 0 && pixels[thisIndex - 1] >= threshold && pixels[thisIndex - 1] < 255) {
//                   if (i == 0) cout << (int)pixels[thisIndex - 1] << endl;
//                   
//                   pixels[thisIndex - 1] = (char)255;
//               }
//               
//               // right pixel
//               if ((thisIndex % ofGetWidth()) != (ofGetWidth() - 1) && pixels[thisIndex + 1] >= threshold && pixels[thisIndex + 1] < 255) {
//                   pixels[thisIndex + 1] = (char)255;
//               }
//               
//               // top pixel
//               if (thisIndex / ofGetWidth() != 0 && pixels[thisIndex - ofGetWidth()] >= threshold && pixels[thisIndex - ofGetWidth()] < 255) {
//                   pixels[thisIndex - ofGetWidth()] = (char)255;
//               }
//               
//               // bottom pixel
//               if (thisIndex / ofGetWidth() != (ofGetHeight() - 1) && pixels[thisIndex + ofGetWidth()] >= threshold && pixels[thisIndex + ofGetWidth()] < 255) {
//                   pixels[thisIndex + ofGetWidth()] = (char)255;
//               }
//               }
//               img.update();
//

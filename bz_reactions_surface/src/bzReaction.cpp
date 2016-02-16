//
//  bzReaction.cpp
//  bz_reactions_surface
//
//  Created by Ben Snell on 2/15/16.
//
//

#include "bzReaction.h"

bzReaction::bzReaction() {
    
    chemistry.setName("Chemistry");
    chemistry.add(decayStrength.set("Decay Strength", 0.8, 0, 1));
    chemistry.add(compoundedDecay.set("Compounded Decay", 1, 0, 1));
    
    rendering.setName("Rendering");
    rendering.add(renderScale.set("Render Scale", 1, 0, 100));
    rendering.add(rotationSpeed.set("Rotation Speed", 10, 0, 100));
    
    srf.setMode(OF_PRIMITIVE_TRIANGLES);
    srf.enableColors();
    srf.enableIndices();
    srf.enableNormals();
    
}

// --------------------------------------------------------------------

void bzReaction::loadSrf(string fileName) {

    srf.load(fileName);
    
    cout << "Surface has been loaded with " << srf.getNumVertices() << " vertices, " << srf.getNumIndices() << " indices, " << srf.getNumNormals() << "normals, and " << srf.getNumColors() << " colors." << endl;
    
    nPts = srf.getNumVertices();
    
    // set all colors to black
    for (int i = 0, nColors = srf.getNumColors(); i < nColors; i++) {
        srf.getColors()[i] = ofFloatColor(0., 1.);
    }
    
    // now construct an index dictionary for this surface (lookup of all connected indices for each index)
    vector<unsigned int> indices;
    for (int i = 0; i < nPts; i++) {
        dict.push_back(indices);
    }
    for (int i = 0, indexVecLength = srf.getIndices().size(); i < indexVecLength; i+= 3) { // for every face
        
        for (int faceVertexNumber = 0; faceVertexNumber < 3; faceVertexNumber++) { // for each vertex of a face (0 to 2)
            
            // index in indices vector
            int indexInIndicesVec = i + faceVertexNumber;
            int vertexIndex = srf.getIndices()[indexInIndicesVec];
            
            // for the other two vertices, check if they're in the dictionary under this vertexIndex. If not, add they index to it
            
            for (int otherFaceVertexNumber = 0; otherFaceVertexNumber < 3; otherFaceVertexNumber++) {
                if (faceVertexNumber == otherFaceVertexNumber) continue;
                
                int otherVertexIndex = srf.getIndices()[i + otherFaceVertexNumber];
                
                // add the other two indices to the dictionary if they don't already exist there
                if (find(dict[vertexIndex].begin(), dict[vertexIndex].end(), otherVertexIndex) == dict[vertexIndex].end()) {
                    dict[vertexIndex].push_back(otherVertexIndex);
                }
            }
        }
    }
    
//    for (int i = 0, end = dict.size(); i < end; i++) {
//        cout << i << " :: ";
//        for (int j = 0, endj = dict[i].size(); j < endj; j++) {
//            cout << dict[i][j] << "\t";
//        }
//        cout << endl;
//    }
    
}

// --------------------------------------------------------------------

void bzReaction::addSeeds(int nSeeds, float _minDuration, float _maxDuration) {

    minDuration = _minDuration;
    maxDuration = _maxDuration;
    
    // add seeds and start reaction
    for (int i = 0; i < nSeeds; i++) {
        bzSeed thisSeed(nPts, minDuration, maxDuration);
        thisSeed.concentrate();
        
        seeds.push_back(thisSeed);
        
        srf.getColors()[thisSeed.index] = ofFloatColor(1., 1.);
    }
    
}

// --------------------------------------------------------------------

void bzReaction::addSeeds(int nSeeds) {
    
    // add seeds and start reaction
    for (int i = 0; i < nSeeds; i++) {
        bzSeed thisSeed(nPts, minDuration, maxDuration);
        thisSeed.concentrate();
        
        seeds.push_back(thisSeed);
        
        srf.getColors()[thisSeed.index] = ofFloatColor(1., 1.);
    }
    
}

// --------------------------------------------------------------------

void bzReaction::drawSrf(int setting) {
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofScale(renderScale, renderScale, renderScale);
    
    srfRot += (ofGetElapsedTimef() - lastTime) * rotationSpeed;
    srfRot = fmod(srfRot, 360.);
    lastTime = ofGetElapsedTimef();
    
    ofRotate(srfRot, 0, 1, 0);

    
    switch (setting) {
        case 0:
            srf.drawVertices();
            break;
        case 1:
            srf.drawWireframe();
            break;
        case 2:
            srf.drawFaces();
            break;
        default:
            srf.drawWireframe();
    }
    
    ofPopMatrix();
    
}

// --------------------------------------------------------------------

void bzReaction::updateSeeds() {

//    if (seeds.size() >= 1) {
//        cout << "there are " << seeds.size() << " seeds and the first has " << seeds[0].expectedConcentration << " expected and " << srf.getColors()[seeds[0].index].r << " actual concentration" << endl;
//    }
    
    // delete seeds whose actual concentration differs from the expected concentration
    float sigma = 0.00001;
    for (int i = seeds.size() - 1; i >= 0; i--) {
        if (abs(seeds[i].expectedConcentration - srf.getColors()[seeds[i].index].r) > sigma) {
            seeds.erase(seeds.begin() + i);
        }
    }
    
    // if seed turned on more than the duration ago, turn it on again (set vertex to high concentration)
    unsigned long timeNow = ofGetElapsedTimeMillis();
    for (int i = 0, nSeeds = seeds.size(); i < nSeeds; i++) {
        
        if (timeNow - seeds[i].lastTimeOn > seeds[i].duration) {
            
            // make concentration high
            srf.getColors()[seeds[i].index] = ofFloatColor(1., 1.);
            
            // reset seed
            seeds[i].concentrate();
            seeds[i].distill(decayStrength);
            
        } else {
            // update expected concentration
            seeds[i].distill(decayStrength);
        }
    }
    
//    cout << seeds.size() << endl;
}

// --------------------------------------------------------------------

void bzReaction::react() {
    
    /*
     Check every pixel against neighbors and apply a simple rule set. Let x = pixel brightness and b = decayStrength.
     1. If x < b && neighbor == 255 Then x = 1
     2. Otherwise, If x < 1, x = x * b
     */
 
    // first, multiply every vertex color by decayStrength and save the indices of pure white vertices
    vector<int> whiteVertices;
    for (int i = 0; i < nPts; i++) {
        if (srf.getColors()[i].r == 1.) whiteVertices.push_back(i);
        srf.getColors()[i] = ofFloatColor(srf.getColors()[i].r * decayStrength, 1.);
    }
    

    // for every vertex that used to be white, make any connecting vertex (via the dictionary) white if its brightness is greater than or equal to the threshold squared.
    float threshold = decayStrength * decayStrength;
    for (int i = 0, end = whiteVertices.size(); i < end; i++) {
        
        // check all neighbors
        for (int j = 0, neib = dict[whiteVertices[i]].size(); j < neib; j++) {
            
            int compareIndex = dict[whiteVertices[i]][j];
            
            if (srf.getColors()[compareIndex].r < threshold * compoundedDecay) {
                // set to white
                srf.getColors()[compareIndex] = ofFloatColor(1., 1.);
            }
        }
    }
    
    
    
}

// --------------------------------------------------------------------

void bzReaction::reset() {
    
    seeds.clear();
    for (int i = 0; i < nPts; i++) {
        srf.getColors()[i] = ofFloatColor(0., 1.);
    }
    addSeeds(10, minDuration, maxDuration);
    
}




















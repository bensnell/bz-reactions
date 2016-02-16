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
    
    rendering.setName("Rendering");
    rendering.add(renderScale.set("Render Scale", 1, 0, 100));
    
    panel.setup();
    panel.add(chemistry);
    panel.add(rendering);
    
    srf.setMode(OF_PRIMITIVE_TRIANGLES);
    srf.enableColors();
    srf.enableIndices();
    srf.enableNormals();
    
}

// --------------------------------------------------------------------
//
//void bzReaction::saveSettings() {
//    
//    panel.saveToFile("settings.xml");
//    
//}

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

void bzReaction::addSeeds(int nSeeds, float minDuration, float maxDuration) {

    // add seeds and start reaction
    for (int i = 0; i < nSeeds; i++) {
        bzSeed thisSeed(nPts, minDuration, maxDuration);
        seeds.push_back(thisSeed);
        
        srf.getColors()[thisSeed.index] = ofFloatColor(1., 1.);
    }
    
}

// --------------------------------------------------------------------

void bzReaction::drawSrf(int setting) {
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofScale(renderScale, renderScale, renderScale);
    
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




















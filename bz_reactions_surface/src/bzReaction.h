//
//  bzReaction.h
//  bz_reactions_surface
//
//  Created by Ben Snell on 2/15/16.
//
//

#ifndef __bz_reactions_surface__bzReaction__
#define __bz_reactions_surface__bzReaction__

#include "ofMain.h"
#include "bzSeed.h"
#include "ofxGui.h"

class bzReaction {
    
public:
    
    bzReaction();
    
    // -----------------------------
    // ---------- SURFACE ----------
    // -----------------------------
    
    // surface on which bz reaction occurs
    ofMesh srf;
    // modified surface
    ofMesh msrf;
    
    // load surface
    void loadSrf(string fileName);
    
    int nPts;
    
    vector< vector<unsigned int> > dict;
    
    // -----------------------------
    // ----------- SEEDS -----------
    // -----------------------------
    
    vector<bzSeed> seeds;
    
    // add a given number of seeds and start the reaction for each
    void addSeeds(int nSeeds, float _minDuration, float _maxDuration);
    
    void addSeeds(int nSeeds);
    
    int minDuration = 500;
    int maxDuration = 3000;
    
    // -----------------------------
    // ---------- REACTION ---------
    // -----------------------------
    
    void updateSeeds();
    
    // progress one step in the reaction
    void react();
    
    void reset();
    
    // -----------------------------
    // -------- MODIFIED FORM ------
    // -----------------------------
    
    void updateMsrf();
    
    void drawMsrf();
    
    void saveMeshes();
    
    // -----------------------------
    // ---------- RENDERING --------
    // -----------------------------
    
    float srfRot; // degrees
    float lastTime = 0; // seconds
    
    // draw surfaces
    void drawSrf(int setting);
    void drawMsrf(int setting);
    
    // -----------------------------
    // ------------ GUI ------------
    // -----------------------------
    
    ofParameter<float> decayStrength;
    ofParameter<float> compoundedDecay;
    ofParameterGroup chemistry;
    
    ofParameter<float> renderScale;
    ofParameter<float> rotationSpeed;
    ofParameter<float> offsetDist;
    ofParameterGroup rendering;
    
};


#endif /* defined(__bz_reactions_surface__bzReaction__) */

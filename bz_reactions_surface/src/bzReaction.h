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
    // eroded surface
    ofMesh esrf;
    
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
    
    void reset(int minDur = -1, int maxDur = -1);
    
    // -----------------------------
    // ------- MODIFIED FORMS ------
    // -----------------------------
    
    void updateMsrf();
    
    float* eroHist; // erosion history
    float minEro;
    float maxEro;
    void updateEsrf();
    
    void saveMeshes();
    
    // -----------------------------
    // ---------- RENDERING --------
    // -----------------------------
    
    float srfRot; // degrees
    float lastTime = 0; // seconds

    // if we're ever drawing something, rotate it
    int lastRotFrame = -1;
    void updateRotation();
    
    // draw surfaces
    void drawSrf(int setting);
    void drawMsrf(int setting);
    void drawEsrf(int setting);
    
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
    
    ofParameter<float> minErosion;
    ofParameter<bool> flipErosion;
    ofParameter<bool> reuseMesh;
    ofParameterGroup erosion;
    
};


#endif /* defined(__bz_reactions_surface__bzReaction__) */

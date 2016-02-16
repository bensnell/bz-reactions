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
    void addSeeds(int nSeeds, float minDuration, float maxDuration);
    
    // -----------------------------
    // ---------- REACTION ---------
    // -----------------------------
    
    
    
    
    // -----------------------------
    // ---------- RENDERING --------
    // -----------------------------
    
    // draw surfaces
    void drawSrf(int setting);
    void drawMsrf();
    
    
    // -----------------------------
    // ------------ GUI ------------
    // -----------------------------
    
    ofParameter<float> decayStrength;
    ofParameterGroup chemistry;
    
    ofParameter<float> renderScale;
    ofParameterGroup rendering;
    
    ofxPanel panel;
    
    void saveSettings();
    
    
};


#endif /* defined(__bz_reactions_surface__bzReaction__) */
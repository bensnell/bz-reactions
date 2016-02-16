//
//  bzSeed.cpp
//  bz_reactions_surface
//
//  Created by Ben Snell on 2/15/16.
//
//

#include "bzSeed.h"

bzSeed::bzSeed(int nTotalPts, float minDuration, float maxDuration) {
    
    index = floor(ofRandom(nTotalPts));
    
    duration = floor(ofRandom(minDuration, maxDuration));
}

// ------------------------------------------------------------------

// call after seed produces a new white spot
void bzSeed::concentrate() {
    
    lastTimeOn = ofGetElapsedTimeMillis();
    
    expectedConcentration = 1;
    
}

// ------------------------------------------------------------------

// call if not turned on
void bzSeed::distill(float decayStrength) {
    
    expectedConcentration *= decayStrength;
}
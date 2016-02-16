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
    
    startTime = 0;
    duration = floor(ofRandom(minDuration, maxDuration));
}

// ------------------------------------------------------------------

void bzSeed::updated() {
    
    lastTimeOn = ofGetElapsedTimeMillis();
    
}
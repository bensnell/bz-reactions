//
//  bzSeed.h
//  bz_reactions_surface
//
//  Created by Ben Snell on 2/15/16.
//
//

#ifndef __bz_reactions_surface__bzSeed__
#define __bz_reactions_surface__bzSeed__

#include "ofMain.h"

class bzSeed {
    
public:
    
    bzSeed(int nTotalPts, float minDuration, float maxDuration);
    
    // index of this seed
    int index;
    
    // ms
    unsigned long startTime;
    unsigned int duration;
    unsigned long lastTimeOn;
    
    // call when seed is updated
    void updated();
    
    
    
    
    
};

#endif /* defined(__bz_reactions_surface__bzSeed__) */

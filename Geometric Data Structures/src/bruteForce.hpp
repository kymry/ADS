//
//  bruteForce.hpp
//  ADS2
//
//  Created by kymry burwell on 5/25/18.
//  Copyright © 2018 kymry burwell. All rights reserved.
//

#ifndef bruteForce_hpp
#define bruteForce_hpp

#include <stdio.h>
#include "Interval Tree.hpp"
#include "SegmentTree.hpp"

// Search for overlapping segments
void bruteForceOverlap(const vector<Interval> *input, vector<Interval> &output, Interval query);

// Search for point queries
void bruteForcePoint(const vector<Interval> *input, vector<Interval> &output, int query);

#endif /* bruteForce_hpp */

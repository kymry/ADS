//
//  bruteForce.cpp
//  ADS2
//
//  Created by kymry burwell on 5/25/18.
//  Copyright © 2018 kymry burwell. All rights reserved.
//

#include "bruteForce.hpp"
#include "Interval Tree.hpp"
#include "SegmentTree.hpp"

// Search for overlapping segments
void bruteForceOverlap(const vector<Interval> *input, vector<Interval> &output, Interval query){
    
    // Perform linear search of intput intervals
    for (auto i : *input){
        if (query.right >= i.left && query.left <= i.right){
            output.push_back(i);
        }
    }
}

// Search for point queries
void bruteForcePoint(const vector<Interval> *input, vector<Interval> &output, int query){

    // Perform linear search of input intervals
    for (auto i : *input){
        if (query >= i.left && query <= i.right){
            output.push_back(i);
        }
    }
}

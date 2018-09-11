//
//  SegmentTree.hpp
//  ADS2
//
//  Created by kymry burwell on 5/23/18.
//  Copyright © 2018 kymry burwell. All rights reserved.
//

#ifndef SegmentTree_hpp
#define SegmentTree_hpp

#include <stdio.h>
#include <vector>
#include "Interval Tree.hpp"
#include <set>

using namespace std;

// Auxilary class to store intervals in a node
class segAux {
public:
    vector<Interval> containedIntervals;
};

// The main node class data structure
class segNode {
public:
    segNode() = default;
    int key = 1000002;
    int B;
    int E;
    set<int> *intervalsInNode = new set<int>;
    segNode *left = nullptr, *right = nullptr;
    segAux *auxilary;
};

// Function to construct segment tree
segNode *constructSegmentTree(const vector<int> &inputArray, int start, int end);

// Function to insert an interval into the segment tree with a return value of the nodes inserted into
vector<segNode> *insertInterval(segNode *v, Interval interval, vector<segNode> *Queue, int position);

// Function to insert an interval into the segment tree without a return value
void insertIntervalNoReturn(segNode *v, Interval interval, int position);

// Function to extract endpoints, sort, and remove duplicates
void extractEndpoints(vector<Interval> *S, vector<int> &toSort);

// Function for finding intervals that contain a point
void searchPointSegment(segNode *v, int q, set<int> &output);

// Function for finding intervals that contain a point
void searchOverlapSegmentDuplicates(segNode *v, Interval* q, vector<Interval> &Output);

// Function for finding overlapping interval
void searchOverlapSegment(segNode *v, int b, int e, set<int> &output, const vector<Interval> *intervalCheck);

#endif /* SegmentTree_hpp */

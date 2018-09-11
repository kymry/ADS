//
//  main.cpp
//  ADS2
//
//  Created by kymry burwell on 5/21/18.
//  Copyright © 2018 kymry burwell. All rights reserved.
//

#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <chrono>
#include "SegmentTree.hpp"
#include "Interval Tree.hpp"
#include "bruteForce.hpp"
#include "binaryIndexedTree.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

    /******************* Segment Tree *******************/
/*
    // Number of intervals in tree and query to perform
    int treeSize = 20;
    
    // Initialize data structures
    vector<Interval> *currentIntervals =  new vector<Interval>;
    vector<int> input = {};
    set<int> output;
    
    // Generate random intervals
    generateIntervals(currentIntervals, treeSize);
        
    // Remove endpoints, sort ascending, and remove duplicates
    extractEndpoints(currentIntervals, input);
    
    // Create segment tree
    segNode *segTreeRoot;
    segTreeRoot = constructSegmentTree(input, 0, (int)input.size()-1);
    
    // Insert intervals into segment tree
    for (int i = 0; i < currentIntervals->size(); i++){
        insertIntervalNoReturn(segTreeRoot, currentIntervals->at(i), i);
    }

    // Query the segment tree for intervals containg a point
    searchPointSegment(segTreeRoot, 5, output);
    cout << "Point 5 overlaps with:" << endl;
    for (auto i : output)
        cout << "[" << currentIntervals->at(i).left << "," << currentIntervals->at(i).right << "]" << " ";
*/
 /******************* Interval Tree *******************/

    // Number of intervals in tree
    int treeSize = 20;
    
    // Vector to hold intervals
    vector<Interval> *S =  new vector<Interval>;
    
    // Generate random intervals
    generateIntervals(S, treeSize);
    
    // Construct interval tree
    vector<Interval> outputOVerlap;
    vector<Interval> outputContain;
    Node *rootNode;
    rootNode = constructIntervalTree(S);

    // Set inteval to be queried
    Interval *intervalQuery = new Interval(1,2);

    // Perform overlap search
    searchOverlap(rootNode, intervalQuery, outputOVerlap);
    cout << "Interval [1,2] overlaps with: " << endl;
    for (auto i : outputOVerlap)
        cout << "[" << i.left << "," << i.right << "]" << " ";
    cout << endl << endl;

    // Perform contain search
    searchContain(rootNode, intervalQuery, outputContain);
    cout << "Interval [1,2] is contained in: " << endl;
    for (auto i : outputContain)
        cout << "[" << i.left << "," << i.right << "]" << " ";

    /******************* Binary Indexed Tree *******************/
/*
    // Generate random integers to populate the starting vector
    vector<int> *BIT = new vector<int>;
    generatePoint(BIT,100);
    
    // Construct the BIT
    constructBIT(*BIT);
    
    // Perform a prefix sum query
    cout << "Sum total of elements [1,10]: " << prefixQueryBIT(*BIT, 10);
    
    // Perform an update
    updateBIT(*BIT, 3, 88);
*/
    return 0;
}

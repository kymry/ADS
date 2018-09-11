//
//  SegmentTree.cpp
//  ADS2
//
//  Created by kymry burwell on 5/23/18.
//  Copyright © 2018 kymry burwell. All rights reserved.
//

#include "SegmentTree.hpp"
#include "Interval Tree.hpp"
#include "math.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


// Main function to construct segment tree
segNode *constructSegmentTree(const vector<int> &inputArray, int start, int end){
    
    // Set interval of node
    segNode *v = new segNode;
    v->B = inputArray[start];
    v->E = inputArray[end];
    
    int mid = floor((start+end)/2);
    v->key = inputArray[mid];
    segAux *w = new segAux;
    v->auxilary = w;
    
    // If node is leaf, return
    if (start+1 == end){
        return v;
    }
    
    // Recursively construct left and right subtrees
    v->left = constructSegmentTree(inputArray, start, mid);
    v->right = constructSegmentTree(inputArray, mid, end);
    
    return v;
}


// Function to insert an interval into the segment tree with a return value of the nodes inserted into
vector<segNode> *insertInterval(segNode *v, Interval interval, vector<segNode> *Queue, int position){
    
    // If the node range is fully contained in the interval to be inserted, add the interval to the node and return
    if (v->B >= interval.left && v->E <= interval.right){
        v->intervalsInNode->insert(position);
        v->auxilary->containedIntervals.push_back(interval);
        Queue->push_back(*v);
        return Queue;
    }
    
    // If left endpoint of interval is smaller than node key, recursively call with left subtree
    if (interval.left < v->key && v->left != nullptr){
        insertInterval(v->left ,interval, Queue, position);
    }
    
    // If right endpoint of interval is greater than node key, recursively call with right subtree
    if (v->key < interval.right && v->right != nullptr){
        insertInterval(v->right ,interval, Queue, position);
    }
    
    return Queue;
}

// Function to insert an interval into the segment tree without a return value
void insertIntervalNoReturn(segNode *v, Interval interval, int position){
    
    // If the node range is fully contained in the interval to be inserted, add the interval to the node and return
    if (v->B >= interval.left && v->E <= interval.right){
        v->intervalsInNode->insert(position);
        v->auxilary->containedIntervals.push_back(interval);
        return;
    }
    
    // If left endpoint of interval is smaller than node key, recursively call with left subtree
    if (interval.left < v->key && v->left != nullptr){
        insertIntervalNoReturn(v->left ,interval, position);
    }
    
    // If right endpoint of interval is greater than node key, recursively call with right subtree
    if (v->key < interval.right && v->right != nullptr){
        insertIntervalNoReturn(v->right ,interval, position);
    }
    
    return;
}


// Function to extract endpoints, sort, and remove duplicates
void extractEndpoints(vector<Interval> *S, vector<int> &toSort){
    
    // Extract endpoints
    for (auto i : *S){
        toSort.push_back(i.left);
        toSort.push_back(i.right);
    }
    
    // Sort and remove duplicates
    sort(toSort.begin(), toSort.end());
    toSort.erase(unique(toSort.begin(), toSort.end()), toSort.end());
}


// Function for finding intervals that contain a point without returning duplicates
void searchPointSegment(segNode *v, int q, set<int> &output){
    
    // If the query cannot be in the subtrees, return
    if (q < v->B || q > v->E){
        return;
    }
    
    // If the query is in the current node's intervals, add to output
    if ((q >= v->B) && (q <= v->E)){
        for (auto i : *v->intervalsInNode){
            output.insert(i);
        }
    }
    
    // If the query might be in the left subtree, continue
    if (q <= v->key && v->left != nullptr){
        searchPointSegment(v->left, q, output);
    }
    
    // If the query might be in the right subtree, continue
    if (q >= v->key && v->right != nullptr){
        searchPointSegment(v->right, q, output);
    } else return;
}

// Function for finding intervals that contain a point with duplicates
void searchPointSegmentDuplicates(segNode *v, int q, vector<Interval> &output){
    
    // If the query cannot be in the subtrees, return
    if (q < v->B || q > v->E){
        return;
    }
    
    // If the query is in the current node's intervals, add to output
    if (q >= v->B && q <= v->E){
        for (auto i : v->auxilary->containedIntervals){
            output.push_back(i);
        }
    }
    
    // If the query might be in the left subtree, continue
    if (q <= v->key && v->left != nullptr){
        searchPointSegmentDuplicates(v->left, q, output);
    }
    
    // If the query might be in the right subtree, continue
    if (q >= v->key && v->right != nullptr){
        searchPointSegmentDuplicates(v->right, q, output);
    } else return;
    
}


// Function for finding overlapping intervals without returning duplicates
void searchOverlapSegment(segNode *v, int b, int e, set<int> &output, const vector<Interval> *intervalCheck){
    
    // If key in query interval, add all intervals at node
    if (b <= v->key && e >= v->key){
        for (auto i : *v->intervalsInNode) output.insert(i);
        if (v->right != nullptr) searchOverlapSegment(v->right, b, e, output, intervalCheck);
        if (v->left != nullptr) searchOverlapSegment(v->left, b, e, output, intervalCheck);
    }
    
    // If right endpoint of query interval to left of key, check current node intervals for overlap and recur left
    else if (e < v->key) {
        for (auto i : *v->intervalsInNode){
            if (b <= intervalCheck->at(i).right && e >= intervalCheck->at(i).left) output.insert(i);
        }
        if (v->left != nullptr) searchOverlapSegment(v->left, b, e, output, intervalCheck);
    }
    
    // If left endpoint of query interval to right of key, check current node intervals for overlap and recur right
    else {
        for (auto i : *v->intervalsInNode){
            if (b <= intervalCheck->at(i).right && e >= intervalCheck->at(i).left) output.insert(i);
        }
        if (v->left != nullptr) searchOverlapSegment(v->right, b, e, output, intervalCheck);
    }
    return;
}


// Function for finding overlapping intervals with duplicates
void searchOverlapSegmentDuplicates(segNode *v, Interval* q, vector<Interval> &Output){
    
    // If query cannot be in subtree, return
    if (q->left > v->E || q->right < v->B)
        return;
    
    // If query must overlap node intervals, add intervals
    if (q->left <= v->E && q->right >= v->B){
        for (auto i : v->auxilary->containedIntervals){
            Output.push_back(i);
        }
    }
    
    // If query might be in both subtrees, continue
    if (q->right >= v->key && q->left <= v->key ){
        if (v->right != nullptr) searchOverlapSegmentDuplicates(v->right, q, Output);
        if (v->left != nullptr) searchOverlapSegmentDuplicates(v->left, q, Output);
    }
    
    // If query might be in right subtree, continue
    else if (q->left > v->key && v->right != nullptr) {
        searchOverlapSegmentDuplicates(v->right, q, Output);
    }
    
    // If query might be in left subtree, continue
    else if (q->right < v->key && v->left != nullptr) {
        searchOverlapSegmentDuplicates(v->left, q, Output);
    } else return;
    
}


















//
//  Interval Tree.cpp
//  ADS2
//
//  Created by kymry burwell on 5/21/18.
//  Copyright © 2018 kymry burwell. All rights reserved.
//

#include "Interval Tree.hpp"
#include "math.h"
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;


// Helper function for sorting intervals acending by left endpoint
bool sortLeftIntervals(const Interval &a,const Interval &b){
    return a.left < b.left;
}


// Helper function for sorting intervals descending by right endpoint
bool sortRightIntervals(const Interval &a,const Interval &b){
    return a.right > b.right;
}

// Function to extract endpoints, sort, and remove duplicates
int extractMedian(vector<Interval> *S){
    
    vector<int> tempVec;
    
    // Extract endpoints
    for (auto i : *S){
        tempVec.push_back(i.left);
        tempVec.push_back(i.right);
    }
    
    // Sort and remove duplicates
    sort(tempVec.begin(), tempVec.end());
    tempVec.erase(unique(tempVec.begin(), tempVec.end()), tempVec.end());
    
    // Return median
    int median = floor(tempVec.size()/2);
    return tempVec[median];
}

// Divides the intervals into three sets: Left, Right, and Mid
int sortIntervals(vector<Interval> *S,vector<Interval> *midSet, vector<Interval> *rightSet, vector<Interval> *leftSet){
    
    // Determine midpoint
    int midPoint = extractMedian(S);
    
    //Divide S into three sets around midPoint
    for (auto i : *S){
        if (i.right < midPoint) leftSet->push_back(i);
        else if (i.left > midPoint) rightSet->push_back(i);
        else midSet->push_back(i);
    }
    return midPoint;
}


// Recursive function that constructs the interval tree
Node *constructIntervalTree(vector<Interval> *S){
    if (S->size() == 0){
        Node *leaf = new Node;
        return leaf;
    }

    // Create vectors to store interval sets
    vector<Interval> *midSet = new vector<Interval>;
    vector<Interval> *rightSet = new vector<Interval>;
    vector<Interval> *leftSet = new vector<Interval>;
    
    int midPoint = sortIntervals(S, midSet, rightSet, leftSet);  // median of endpoints in S
    Node *v = new Node;
    v->key = midPoint;
    v->left = constructIntervalTree(leftSet);
    v->right = constructIntervalTree(rightSet);
    
    // Create auxilary data structure to hold intervals for current node
    Aux *w = new Aux;
    sort(midSet->begin(), midSet->end(), sortLeftIntervals);
    w->leftEndPoints = *midSet;
    sort(midSet->begin(), midSet->end(), sortRightIntervals);
    w->rightEndPoints = *midSet;
    v->auxilary = w;
    
    return v;

}


// Function for finding intervals that overlap with the query interval
void searchOverlap(Node *v, Interval *Query, vector<Interval> &Output){
    
    if (v->key == 100002) return;
    
    // If query contains key
    if (Query->right >= v->key && Query->left <= v->key) {
        for (auto i : v->auxilary->leftEndPoints){
            Output.push_back(i);
        }
        searchOverlap(v->left, Query, Output);
        searchOverlap(v->right, Query, Output);
    }
    
    // If right endpoint of query is less than node key
    if (Query->right < v->key){
        for (auto i : v->auxilary->leftEndPoints){
            if (Query->right >= i.left) Output.push_back(i);
            else break;
        }
        searchOverlap(v->left, Query, Output);
    }
    
    // If left endpoint of query is greater than node key
    if (Query->left > v->key){
        for (auto i : v->auxilary->rightEndPoints){
            if (Query->left <= i.right) Output.push_back(i);
            else break;
        }
        searchOverlap(v->right, Query, Output);
    }
}


// Function for finding intervals that fully contain the query interval
void searchContain(Node *v, Interval *Query, vector<Interval> &Output){
    
    if (v->key == 100002) return;
    
    // If query contains key
    if (Query->right >= v->key && Query->left <= v->key) {
        if ( v->key - Query->left  >  Query->right - v->key){
            for (auto i : v->auxilary->leftEndPoints){
                if (i.left <= Query->left){
                    if (i.right >= Query->right) Output.push_back(i);
                } else break;
            }
        }
        else {
            for (auto i : v->auxilary->rightEndPoints){
                if (i.right >= Query->right){
                    if (i.left <= Query->left) Output.push_back(i);
                } else break;
            }
        }
        searchContain(v->left, Query, Output);
        searchContain(v->right, Query, Output);
    }
    
    // If right endpoint of query is less than node key
    else if (Query->right < v->key){
        for (auto i : v->auxilary->leftEndPoints){
            if (i.left <= Query->left){
                if (i.right >= Query->right) Output.push_back(i);
            } else break;
        }
        searchContain(v->left, Query, Output);
    }
    
    // If left endpoint of query is greater than node key
    else {
        for (auto i : v->auxilary->rightEndPoints){
            if (i.right >= Query->right){
                if (i.left <= Query->left) Output.push_back(i);
            } else break;
        }
        searchContain(v->right, Query, Output);
    }
}

// Function for finding intervals that intersect the query point 
void searchPoint(Node *v, int Query, vector<Interval> &Output){
    
    if (v->key == 100002) return;
    
    // If query contains key
    if (Query == v->key) {
        for (auto i : v->auxilary->leftEndPoints){
            Output.push_back(i);
        }
        searchPoint(v->left, Query, Output);
        searchPoint(v->right, Query, Output);
    }
    
    // If right endpoint of query is less than node key
    if (Query < v->key){
        for (auto i : v->auxilary->leftEndPoints){
            if (Query >= i.left) Output.push_back(i);
            else break;
        }
        searchPoint(v->left, Query, Output);
    }
    
    // If left endpoint of query is greater than node key
    if (Query > v->key){
        for (auto i : v->auxilary->rightEndPoints){
            if (Query <= i.right) Output.push_back(i);
            else break;
        }
        searchPoint(v->right, Query, Output);
    }
}


// Generates random intervals
void generateIntervals(vector<Interval> *S, int treeSize){
    
    // Configure random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 10);
    
    // Generate random numbers and place into intervals
    for (int i = 0; i < treeSize; i++){
        int a = dis(gen), b = dis(gen);
        Interval tempInterval;
        if (a == b){
            tempInterval.left = b;
            tempInterval.right = a+1;
        }
        else if (a > b) {
            tempInterval.left = b;
            tempInterval.right = a;
        }
        else {
            tempInterval.left = a;
            tempInterval.right = b;
        }
        S->push_back(tempInterval);
    }
}

// Generates random points
void generatePoint(vector<int> *S, int querySize){
    
    // Configure random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 10);
    
    // Generate random numbers and place into intervals
    for (int i = 0; i < querySize; i++){
        S->push_back(dis(gen));
    }
}



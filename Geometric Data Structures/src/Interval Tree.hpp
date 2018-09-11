//
//  Interval Tree.hpp
//  ADS2
//
//  Created by kymry burwell on 5/21/18.
//  Copyright © 2018 kymry burwell. All rights reserved.
//

#ifndef Interval_Tree_hpp
#define Interval_Tree_hpp

#include <stdio.h>
#include <vector>

using namespace std;

// Class for intervals
class Interval {
public:
    Interval() = default;
    Interval(int l, int r) : left(l), right(r) {}
    int left;
    int right;
};

// Auxilary class to store intervals in a node
class Aux {
public:
    vector<Interval> leftEndPoints;
    vector<Interval> rightEndPoints;
};


// The main node class data structure
class Node {
public:
    Node() = default;
    int key = 100002;
    int count;
    Node *left, *right;
    Aux *auxilary;
};

// Sorts intervals into three set depending upon nodes key value
int sortIntervals(vector<Interval> *S,vector<Interval> *midSet, vector<Interval> *rightSet, vector<Interval> *leftSet);

// Main function to construct an interval tree
Node *constructIntervalTree(vector<Interval> *S);

// Function for overlapping inteval search queries
void searchOverlap(Node *v, Interval *Query, vector<Interval> &Output);

// Function for point queries
void searchPoint(Node *v, int Query, vector<Interval> &Output);

// Function for containing interval queries
void searchContain(Node *v, Interval *Query, vector<Interval> &Output);

// Helper function to sort intervals by left endpoint
bool sortLeftIntervals(const Interval &a,const Interval &b);

// Helper function to sort intervals by right endpoint
bool sortRightIntervals(const Interval &a,const Interval &b);

// Generates random intervals
void generateIntervals(vector<Interval> *intervals, int treeSize);

// Generates random points
void generatePoint(vector<int> *S, int querySize);

// Function to extract endpoints, sort, and remove duplicates
int extractMedian(vector<Interval> *S);

#endif /* Interval_Tree_hpp */

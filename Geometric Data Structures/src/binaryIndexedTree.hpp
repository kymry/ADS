//
//  binaryIndexedTree.hpp
//  ADS2
//
//  Created by kymry burwell on 6/1/18.
//  Copyright © 2018 kymry burwell. All rights reserved.
//

#ifndef binaryIndexedTree_hpp
#define binaryIndexedTree_hpp

#include <stdio.h>
#include <vector>

using namespace std;

// Construct Binary Indexed Tree
void constructBIT(vector<int> &bit);

// Update element in Binary Indexed Tree
void updateBIT(vector<int> &bit, int index, int append);

// Perform prefix Query
int prefixQueryBIT(vector<int> &bit, int index);
    
// Perform range Query
int rangeQueryBIT(vector<int> &bit, int start, int end);

#endif /* binaryIndexedTree_hpp */

//
//  binaryIndexedTree.cpp
//  ADS2
//
//  Created by kymry burwell on 6/1/18.
//  Copyright © 2018 kymry burwell. All rights reserved.
//

#include "binaryIndexedTree.hpp"
#include <vector>
#include <iostream>

using namespace std;

// Main function to construct Binary Indexed Tree
void constructBIT(vector<int> &bit){
    
    // Append a 0 at the beginning to enable the array to start at index 1
    bit.insert(bit.begin(),0);
    
    // Loop through array and add cumulitive range sums
    for (int index = 1; index <= bit.size(); index++){
        int index2 = index + (index & -index); // add the last bit
        if (index2 < bit.size())
            bit[index2] += bit[index];
    }
    
    /********
     Example procedure of adding the last set bit.
     x = 14  = (00001110)
     -x = -14 = (11110010)
     x & -x = (00000010)
     x+(x & -x) = (00010000)
     ********/
}

// Update element in Binary Indexed Tree
void updateBIT(vector<int> &bit, int index, int append){
    
    // Loop through BIT starting at index adding to correct range sums
    for (; index < bit.size(); index += (index & -index))
        bit[index] += append;
}

// Perform prefix Query
int prefixQueryBIT(vector<int> &bit, int index){
    
    // Loop through array starting at index and continuing to the beginning
    int sum = 0;
    for (; index > 0 ; index -= (index & -index))
        sum += bit[index];
    
    return sum;
}

// Perform range Query
int rangeQueryBIT(vector<int> &bit, int start, int end){
    
    // Utilize the prefix query to provide sum of range
    return prefixQueryBIT(bit, end) - prefixQueryBIT(bit, (start-1));
}










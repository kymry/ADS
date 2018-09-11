//  Created by kymry burwell on 4/1/18.
//  Copyright © 2018 kymry burwell. All rights reserved.

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <list>
#include <random>
#include "splayTree.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    // Set number of elements in tree
    int treeSize = 20000;
    
    // Set number of queries to perform
    int querySize = 10000;
    
    // Set the seed
    srand(133445);
    
    // Set output file destinations
    string filenameSplay = "output file destination for splay tree heights";
    string filenameBST = "output file destination for BST tree heights";
    string filenameSplaySearch = "output file destination for splay tree search unbiased results";
    string filenameBSTSearch = "output file destination for BST tree unbiased height";
    string filenameSplaySearchBias = "output file destination for splay tree biased height";
    string filenameBSTSearchBias = "output file destination for BST tree biased height";
    
    // Create output streams
    ofstream outS(filenameSplay, ofstream::app);
    ofstream outB(filenameBST, ofstream::app);
    ofstream outSearchSBias(filenameSplaySearchBias, ofstream::app);
    ofstream outSearchBBias(filenameBSTSearchBias, ofstream::app);
    ofstream outSearchS(filenameSplaySearch, ofstream::app);
    ofstream outSearchB(filenameBSTSearch, ofstream::app);
    
    // Create initial node key, tree height, and search counter variables
    node *rootS = createNode(1), *rootB = createNode(1);
    vector<int> splaySearchElem, bstSearchElem;
    int height = 0;
    outB << 1 << endl; outS << 1 << endl;
    
    /********** SPLAY TREE **********/
    // Create splay tree with randomized numbers
    for (int i = 0; i <= treeSize; ++i){
        if (i % 10 == 0) {
            rootS = splayInsert(rootS, rand());
            splaySearchElem.push_back(rootS->key);
        } else {
            rootS = splayInsert(rootS, rand());
        }
        height = getHeight(rootS);
        outS << height << endl;
    }
    
    // Query splay tree with bias
    int searchStepsSplay, randNum;
    std::random_device rd; // obtain a random number
    std::mt19937 eng(rand()); // seed the generator
    std::uniform_int_distribution<> distr(0, splaySearchElem.size()); // define the range
    for(int i = 0; i < querySize; ++i) {
        searchStepsSplay = 0;
        randNum = splaySearchElem[distr(eng)];
        if (i % 10 != 0) rootS = findNodeSplay(rootS, randNum , searchStepsSplay);
        else rootS = findNodeSplay(rootS, rand(), searchStepsSplay);
        outSearchSBias << searchStepsSplay << endl;
    }
   
    // Query splay tree without bias
    for (int i = 0; i < querySize; ++i){
        searchStepsSplay = 0;
        rootS = findNodeSplay(rootS, rand(), searchStepsSplay);
        outSearchS << searchStepsSplay << endl;
    }
 
    /********** BST TREE **********/
    srand(133445);
    // Create BST tree with randomized numbers
    for (int i = 0; i <= treeSize; ++i){
        rootB = insert(rootB, rand());
        height = getHeight(rootB);
        outB << height << endl;
    }

    // Query BST tree with bias
    for(int i = 0; i < querySize; ++i) {
        int searchStepsBST = 0;
        randNum = splaySearchElem[distr(eng)];
        if (i % 10 != 0) findNode(rootB, randNum , searchStepsBST);
        else findNode(rootB, rand(), searchStepsBST);
        outSearchBBias << searchStepsBST << endl;
    }
    
    // Query BST tree without bias
    for (int i = 0; i < querySize; ++i){
        int searchStepsBST = 0;
        findNode(rootB, rand(), searchStepsBST);
        outSearchB << searchStepsBST << endl;
    }

    return 0;
}


#ifndef splayTree_hpp
#define splayTree_hpp

#include <stdio.h>
#include <iostream>

// The main node class data structure
class node {
public:
    int key; // Data stored in node
    int count; // Count if there are duplicate keys
    node *head, *tail, *parent;
};

// Inserts a new node with the splay opertion
node* splayInsert(node *nodeCheck, int key);

// Searching for a key
node *findNodeSplay(node *root, int key, int &counter);

// Create new node
node* createNode(int key);

// Insert a new node
node* insert(node *node, int key);

// Find a node with the specified value
node* findNode(node *findMe, int key, int &counter);

// Prints the tree in ascending order (left to right)
void printTree(node *node);

// Get the height of the tree
int getHeight(node *node);

// Left rotation
node* leftRotation(node *x);

// Right rotation
node* rightRotation(node *y);

// The splay operation
node *splay(node *root, int key, int &counter);

#endif /* splayTree_hpp */

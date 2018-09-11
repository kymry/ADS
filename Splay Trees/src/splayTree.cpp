#include "splayTree.hpp"
#include <iostream>

// BST and slay tree primary nod creation
node* createNode(int key){
    node *newNode =  new node;
    newNode->key = key;
    newNode->head = nullptr;
    newNode->tail = nullptr;
    newNode->parent = nullptr;
    return newNode;
}

// Prints the tree in ascending order (left to right)
void printTree(node *node){
    
    if (node == NULL) return;
    if (node->tail != nullptr) {
        printTree(node->tail);
    }
    std::cout << node->key << std::endl;
    if (node->head != nullptr) {
        printTree(node->head);
    }
}

// Returns the current height of the tree
int getHeight(node *node){
    int tSum = 0;
    if (node->tail){
        tSum = getHeight(node->tail);
    }
    
    int hSum = 0;
    if (node->head){
        hSum = getHeight(node->head);
    }
    
    if (hSum > tSum){
        return hSum + 1;
    } else {
        return tSum + 1;
    }
}

// Inserts a new node with the splay opertion (Splay tree)
node* splayInsert(node *nodeCheck, int key){
    
    // temp is needed to pass a fake counter to the splay operation
    int temp;
    
    // Perform the splay opertion first - this uses the top down approach
    nodeCheck = splay(nodeCheck, key, temp);
    
    // If key is duplicate, ignore - This tree ignores duplicate keys
    if (nodeCheck->key == key){
        return nodeCheck;
    }
    
    // Create a temp node to hold the new key
    node *tempNode = createNode(key);
    
    // Make key the new root of the tree
    if (key < nodeCheck->key) {
        tempNode->head = nodeCheck;
        tempNode->tail = nodeCheck->tail;
        nodeCheck->tail = nullptr;
    } else {
        tempNode->tail = nodeCheck;
        tempNode->head = nodeCheck->head;
        nodeCheck->head = nullptr;
    }

    return tempNode;
}

// Inserts a new node without the splay operation (BST)
node* insert(node *nodeCheck, int key){
    
    // Create temporary parent node and new node if needed (parent isn't strictly necessary, but added it for richness)
    node *parentNode;
    node *tempNode;
    
    if(nodeCheck != NULL) parentNode = nodeCheck;
    
    // If there are no more nodes to compare, create new node and insert
    if (nodeCheck == NULL) {
        tempNode = createNode(key);
        tempNode->parent = parentNode;
        return tempNode;
    }
    
    // Recur down the tree to find proper element location
    if (key == nodeCheck->key){
        return nodeCheck;
    }
    else if (key < nodeCheck->key) {
        parentNode = nodeCheck;
        nodeCheck->tail = insert(nodeCheck->tail, key);
    } else {
        parentNode = nodeCheck;
        nodeCheck->head = insert(nodeCheck->head, key);
    }
    
    return nodeCheck;
}

// Searches for a node with the splay operation
node *findNodeSplay(node *root, int key, int &counter) {
    return splay(root, key, counter);
}

// Searches for a node with the specified value without the splay operation (normal BST)
node* findNode(node *findMe, int key, int &counter){
    
    // Counter used in search analysis
    ++counter;
    
    if (findMe == NULL) {
        return findMe;
    }
    if (key > findMe->key) {
        return findNode(findMe->head, key, counter);
    }
    else if (key < findMe->key)
        return findNode(findMe->tail, key, counter);
    else {
        return findMe;
    }
}


// Perform a left rotation
node *rightRotation(node *xNode) {
    node *yNode = xNode->tail;
    yNode->head = xNode;
    xNode->tail = yNode->head;
    return yNode;
}

// Perform a right totation
node *leftRotation(node *xNode) {
    node *yNode = xNode->head;
    xNode->head = yNode->tail;
    yNode->tail = xNode;
    return yNode;
}

// Performs the splay operation
node *splay(node *root, int key, int &counter){
    
    // Counter to count the number of nodes visited
    counter++;
    
    // If the key is found, end the recurion and return the root
    if (root ==  NULL || root->key == key)
        return root;
    
    // Searches the left sub-tree
    if (key < root->key){
        
        // Key isn't found so end search and return root
        if (root->tail == nullptr) {
            return root;
        }
        
        // Counter to count the number of nodes visited
        counter++;
        
        // If the key is in the left sub-sub-tree
        if (key < root->tail->key){
            // Recursively splay the parent and grandparent
            root->tail->tail = splay(root->tail->tail, key, counter);
            // Perform the right rotation (top down approach)
            root = rightRotation(root);
        }
        // If the key is in the right sub-sub-tree
        else if (root->tail->key < key){
            // Recursively splay the tree (parent and grandparent)
            root->tail->head = splay(root->tail->head, key, counter);
            // Perform the left rotation (top down approach)
            if (root->tail->head != nullptr)
                root->tail = leftRotation(root->tail);
        }
        
        // Perform another right rotation if necessary
        return (root->tail == nullptr) ? root : rightRotation(root);
    }
    else { // Search the right sub-tree
        // Key isn't found so end search
        if (root->head == nullptr) {
            return root;
        }
        
        // Counter for the search analysis
        counter++;
        
        // key is in the left sub-sub-tree
        if (key < root->head->key){
            // Recursively splay the tree (parent and grandparent)
            root->head->tail = splay(root->head->tail, key, counter);
            // Perform right rotation if necessary
            if (root->head->tail != nullptr) {
                root->head = rightRotation(root->head);
            }
        }
        // Key is in the right sub-sub-tree
        else if (key > root->head->key) {
            // Recursively splay the tree (parent and grandparent)
            root->head->head = splay(root->head->head, key, counter);
            root = leftRotation(root);
        }
        
        // If necessary, do a second left rotation
        return (root->head == nullptr) ? root : leftRotation(root);
    }
}




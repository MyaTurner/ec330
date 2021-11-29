//
//  Huffman.h
//  ec330_hw6
//

#ifndef Huffman_h
#define Huffman_h


#include <vector>
#include <queue>

using namespace std;

/****** Implementation of Node ******/

class Node {
public:
    string data;
    int freq;
    Node *left, *right;

    // Constructor for char array
    Node(string data, int freq)
    {
        this->data = data;
        this->freq = freq; //Key for min heap priority queue
        Node *left = nullptr;
        Node *right = nullptr;
    }
};

class Huffman{
public:

    vector <Node*> minHeap;
    void buildHuffmanTree(char* input, int* frequency, int size);
    void getCodes(Node* root, char* codes, int index);
    void printCodes();
    void decodeText(const char* fileName);
};

#endif /* Huffman_h */
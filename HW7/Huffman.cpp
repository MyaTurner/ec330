#include <iostream>
#include <vector>
#include "Huffman.h"
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

/*
sources:
https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
*/

//Gets the Huffman codes and characters to be printed out in the printCodes function
void Huffman::getCodes(Node* root, char* codes, int index){

    if(root->left)
    {
        codes[index] = '0';
        getCodes(root->left, codes, index + 1);
    }

    if(root->right)
    {
        codes[index] = '1';
        getCodes(root->right, codes, index + 1);
    }

    //If node is a character, print out the code and character
    if(root->data.size() == 1)
    {
        for (int i = 0; i < index; i++)
           cout << codes[i];

        cout <<  "\t\t  ";
        cout << root->data<<endl;


    }

}
// constructs a Huffman Tree from the input
void Huffman::buildHuffmanTree(char* characters, int* freq, int size) {

    Node *curr;

    // insert all characters into minHeap
    for (int i = 0; i < size; i++) {
        string character(1, characters[i]);
        curr = new Node(character, freq[i]);
        minHeap.push_back(curr);

    }

    // Iterate while size of heap doesn't become 1
    Node *left, *right, *newest;
    int newFreq;
    while (minHeap.size() > 1) {

        // Extract the two smallest freq from minHeap
        left = minHeap.front();
        minHeap.erase(minHeap.begin());

        right = minHeap.front();
        minHeap.erase(minHeap.begin());

        // Create new node w/ sum of 2 frequencies
        newFreq = left->freq + right->freq;

        // data = L data + R data, after the same freq
        newest = new Node(left->data + right->data, newFreq);

        // This new node's children = the two extracted Nodes
        newest->left = left;
        newest->right = right;

        // Add node to the heap, before a bigger frequency
        for(int i = 0; i < minHeap.size(); i++)
        {
            //If find a frequency in min Heap that is greater, place T after that Tree
            if(minHeap.at(i)->freq > newest->freq)
            {
                minHeap.insert(minHeap.begin() + i, newest);
                break;
            }

            //If at the end, insert T to the end
            if(i == minHeap.size() - 1)
            {
                //minHeap.push_back(newest);
                minHeap.insert(minHeap.end(), newest);
                break;
            }

        }

        //If the min Heap is empty, add T to it.
        if(minHeap.size() == 0)
        {
            minHeap.push_back(newest);
        }

    }
}


//prints the Huffman tree in a table format
void Huffman::printCodes(){

    //Beginning of Huffman Table
    cout << "Huffman Code\tCharacter " << endl;
    cout << "--------------------------" << endl;

    Node* root = minHeap.front();
    char codes[100];
    int index = 0;

    //Call the getCodes function
    getCodes(root, codes, index);

}

// print out the plain text version of the file
void Huffman::decodeText(const char* fileName){

    //Opening the file
    ifstream file;
    file.open(fileName);

    //Getting the encoded text
    string text;
    if (file.is_open())
    {
        text = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
    }

    //cout << text <<endl;

    //Start at root of Huffman Tree
    Node *root = minHeap.front();
    Node *curr = minHeap.front();
    string decodedText = "";

    for(int i = 0; i < text.size(); i++)
    {
            if(text[i] == '0')
            {
                curr = curr->left;

                if(curr->data.size() == 1)
                {
                    decodedText += curr->data;
                    curr = root;
                }

            }

            if(text[i] == '1')
            {
                curr = curr->right;

                if(curr->data.size() == 1)
                {
                    decodedText += curr->data;
                    curr = root;
                }

            }


    }
        cout<< "The decoded text is: "<< decodedText <<endl;

    }


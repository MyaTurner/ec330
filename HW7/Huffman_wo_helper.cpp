#include <iostream>
#include <vector>
#include "Huffman.h"
#include <fstream>
#include <algorithm>

using namespace std;

/*
sources:
https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
*/

// constructs a Huffman Tree from the input
void Huffman::buildHuffmanTree(char* characters, int* freq, int size) {

    Node *curr;
    // insert all characters into minHeap
    for (int i = 0; i < size; i++) {
        string character(1, characters[i]);
        curr = new Node(character, freq[i]);
        //cout<<"curr: "<< curr->data << endl;
        minHeap.push_back(curr);

    }

    // Iterate while size of heap doesn't become 1
    Node *left, *right, *newest;
    int newFreq;
    while (minHeap.size() > 1) {

        // Extract the two smallest freq from minHeap
        left = minHeap.front();
        //cout << "T1: " << left->data << endl;
        minHeap.erase(minHeap.begin());

        right = minHeap.front();
        //cout << "T2: " << right->data << endl;
        minHeap.erase(minHeap.begin());

        // Create new node w/ sum of 2 frequencies
        newFreq = left->freq + right->freq;
        //cout << "newFreq: " << newFreq << endl;


        // data = L data + R data, after the same freq
        newest = new Node(left->data + right->data, newFreq);
        //cout << "newest Node data: " << newest->data << endl;

        // This new node's children = the two extracted Nodes
        newest->left = left;
        //cout << "newest Node left: " << newest->left->data << endl;
        newest->right = right;
        //cout << "newest Node right: " << newest->right->data << endl;

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

        //cout << "next step ------" << endl;

    }
}


//prints the Huffman tree in a table format
void Huffman::printCodes(){
    cout << "Huffman Code\tCharacter " << endl;
    cout << "--------------------------" << endl;

    string str = "";

    // find the top of the tree
    Node* root = minHeap.front();
    while(root->right)
    {
        if(root->left->data.size() == 1)
        {
            str += "0";
            cout << str << "\t\t  " << root->left->data <<endl;

            //Removing the 0 because always moving to the right
            str.erase(remove(str.begin(), str.end(), '0'), str.end());
        }

        if(root->right->data.size() == 1)
        {
            str += "1";
            cout << str << "\t\t  " << root->right->data <<endl;
        }

        root = root->right;
        str += "1";

    }
    cout<<endl;
    
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
        //cout <<decodedText<<endl;
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


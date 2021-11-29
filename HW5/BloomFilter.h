//
//  BloomFilter.h
//  BloomFilter
//
//  Created by Tali Moreshet, adapted from Ari Trachtenberg
//

#ifndef BloomFilter_h
#define BloomFilter_h

#include <string>

using namespace std;

//Base Class
class BloomFilter {
public:
    /**
     * Instantiate an empty Bloom filter of length 'len' chars.
     */
     //Constructor
    BloomFilter (int len);
    
    /**
     * Inserts item into the filter
     */
    void insert(string item);
    
    /**
     * Checks whether item is in the filter.
     * Returns true if the item is probably in the filter
     *         false if the item is definitely not in the filter
     */
    bool exists(string item);
    
    /**
     * Returns a string of characters representing the Bloom filter
     */
    string output();

    //Hash Functions
    //char hash_character(string item);

    //int hash_index(string item);
    
protected:
    int length;     /** The length of the Bloom filter, in chars. */
    char *bf;       /** The Bloom filter */
};


#endif /* BloomFilter_h */

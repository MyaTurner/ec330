//
// Mya Turner with collaborator Lesly Alcantara
//
#include <iostream>
#include "BloomFilter.h"
/*source(s): https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed,
 https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function,http://www.partow.net/programming/hashfunctions/#DJBHashFunction,
 http://www.cse.yorku.ca/%7Eoz/hash.html
*/

using namespace std;

    //Hash 1 and 2  correspond to a index that will be placed with a chosen character
    //from Hash 3

    //Hash 1: Fowler-Noll-Vo Has Function
    int hash1(string item, int length)
    {
        unsigned long long int hash = 14695981039346656037;
        unsigned long long int FNV_prime = 1099511628211;

        //For each byte of data, hash by multiply and XORing the byte

        for(int i = 0; i < item.length(); i++)
        {
            hash = hash * FNV_prime;
            hash = hash ^ (int) item[i];
        }
        cout << hash % length;

        return hash % length;

    }

    //Hash 2: djb Hash Function
    int hash2(string item, int length)
    {
        unsigned int hash = 5381;

        for(int i = 0; i < item.length(); i++)
        {
            hash = ((hash << 5) + hash) + (int) item[i];
        }
        cout << hash % length;
        return hash % length;
    }

    //Hash 3: sdbm
    char hash3(string item, int length)
    {
        unsigned int hash = 0;

        for(int i = 0; i < item.length(); i++)
        {
            hash = (int) item[i] + (hash << 6) + (hash << 16) - hash;
        }

        char char_change = (char) hash % (58) + 63;
        cout << char_change;
        return char_change;

    }

    /**
     * Instantiate an empty Bloom filter of length 'len' chars.
     */
    //Constructor
     BloomFilter:: BloomFilter(int len)
    {
        this->length = len;

        //Intializing BloomFilter
        bf = new char[this->length]();
        char *first = bf;
       char *end = first + this->length;
        cout << "Value of end: " << (end - first) <<endl;
        fill(first, end, 'a');

    }

    /**
    * Inserts item into the filter
    */
    void BloomFilter:: insert(string item)
    {
        //Use a hashing function to change string into a fixed length
        // output of characters.

        //Change string to length of this->length character
        // Condensing information

        int index = hash1(item, this->length);
        int index2 = hash2(item, this->length);

        //char char_change = 'b';// hash3(item, this->length);
        unsigned char char_change = hash3(item, this->length);

        //Create new hashed item.  In a regular BloomFilter this would be set to true.
        //In our character BloomFilter we set it to 'b'
        cout << "Before OR—-Int of character at bf " << index << " " <<(int) bf[index] <<endl;
        cout << "Before OR—-Int of character at bf " << index2 << " " <<(int) bf[index2] <<endl;

        bf[index] = (char) ( ((int) char_change | (int) bf[index]) % 128);
        bf[index2] = (char) ( ((int) char_change | (int) bf[index2]) % 128);


        cout << "Int of character at bf " << index << " "<< (int) bf[index]<<endl;
        cout << "Int of character at bf " << index2 << " "<< (int) bf[index2]<<endl;
//        bf[index] =  char_change;
//        bf[index2] = char_change;
    }


    /**
     * Checks whether item is in the filter.
     * Returns true if the item is probably in the filter
     *         false if the item is definitely not in the filter
     */
    bool BloomFilter:: exists(string item)
    {
        //Hash item first
        int index = hash1(item, this->length);
        int index2 = hash2(item, this->length);
       //char char_change = 'b'; //hash3(item, this->length);
        char char_change = hash3(item, this->length);

        /*If the AND result is equal to the BloomFilter at specified index
        return true, else return false */
        bool result1 = ( (char) ( ( (int) char_change & (int) bf[index] ) % 128) == bf[index]) ? true : false;
        bool result2 = ( (char) ( ( (int) char_change & (int) bf[index] ) % 128) == bf[index2]) ? true : false;

        if(result2 == true && result1 == true)
        {
            return true;
        }
        else
        {
            return false;
        }
//
//return result1;
    }

    /**
     * Returns a string of characters representing the Bloom filter
     */
    string BloomFilter:: output()
    {
        string BloomFilter_(bf);

        //Returning the BloomFilter
        return BloomFilter_;
    }

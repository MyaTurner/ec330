#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include "Problem4.h"

//Mya Turner and Lesly Alcantara
/* 
sources:
https://www.geeksforgeeks.org/program-to-check-the-validity-of-a-password/,
https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring,
https://www.techiedelight.com/cpp-implementation-trie-word-structure/,
https://www.tutorialgateway.org/cpp-program-to-convert-string-to-lowercase/
 https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case

*/

using namespace std;

//Trie class used in fourC
class Trie
{
public:
    bool is_word;
    Trie* character[128];
    //ascii => highest value is 127

    // Constructor => no words yet
    Trie()
    {
        this->is_word = false;

        //Intialize each character
        for (int i = 0; i < 128; i++) {
            this->character[i] = nullptr;
        }
    }

    //insert a key into a Trie
    void insert(string key)
    {
        // start from the root node
        Trie* curr = this;
        for (int i = 0; i < key.length(); i++)
        {
            // create a new node if the path doesn't exist
            if (curr->character[key[i]] == nullptr) {
                curr->character[key[i]] = new Trie();
            }

            // go to the next node
            curr = curr->character[key[i]];
        }

        // mark the current node as a word
        curr->is_word = true;
    }

    // search for a key in a Trie
    // only True if the key is found in the Trie
    bool search(string key)
    {
        // return false if Trie is empty
        if (this == nullptr) {
            return false;
        }

        Trie* curr = this;
        for (int i = 0; i < key.length(); i++)
        {
            // go to the next node
            curr = curr->character[key[i]];

            // if reached end of a path in the Trie
            if (curr == nullptr) {
                return false;
            }
        }

        // return true if the current node is a word + reached end
        return curr->is_word;
    }
};


//Finds the length of the longest word in the file
int fourA(){
    int maxLength = 0;
    ifstream file;
    file.open("BigData.txt");
    string word;
    string longestWord = "";
    int currentWordLength = 0;

    while (!file.eof() )
    {
        
        while(file >> word ){
            currentWordLength = word.length();
            if(currentWordLength >= maxLength){
               maxLength = currentWordLength;
               longestWord = word;
             }
        }

    }
    //cout<< longestWord<<endl;
    return maxLength;
}

//Finds the number of valid passwords in file
int fourB(){

    //Reading in file
    ifstream file;
    file.open("BigData.txt");
    string word;
    int password_count = 0;
    bool has_uppercase = false;
    bool has_lowercase = false;
    bool has_digit = false;

    while (!file.eof() )
    {

       while(file >> word ){
           if(word.length() >= 8 && word.length() <= 20)
           {
               /*Password needs to have at least one lowercase letter, one uppercase
                * letter and one digit. */

               //Check if word has a digit
               for(int i = 0; i <= 9; i++)
               {
                   string digit = to_string(i);

                   if (word.find(digit) != -1){
                       has_digit = true;
                       //cout << "hi" <<endl;

                       //Has at least one digit so break out of loop
                       break;
                   }

               }

               //Check if word has an uppercase letter
               for(int i = 65; i <= 90; i++)
               {
                   char letter = (char)i;
                   string uppercase_let(1, letter);

                   if (word.find(uppercase_let) != -1){
                       has_uppercase = true;
                       //cout << "hi" <<endl;

                       //Has at least one uppercase letter so break out of loop
                       break;

                   }
               }

               //Check if word has an lowercase letter
               for(int i = 97; i <= 122; i++)
               {

                   char letter = (char)i;
                   string lowercase_let(1, letter);

                   if (word.find(lowercase_let) != -1){
                       has_lowercase = true;
                       //cout << "hi" <<endl;

                       //Has at least one uppercase letter so break out of loop
                       break;

                   }
               }

               //If all conditions are true, increase valid password count by 1
               if(has_lowercase && has_uppercase && has_digit)
               {
                   password_count++;
               }

               //Set all cases back to false for next word
               has_digit = false;
               has_uppercase = false;
               has_lowercase = false;

            }

        }

    }
    return password_count;
}

/*The number of English words (from the dictionary.txt file) that appear in the file
 * which do not contain some combination of all the characters (lowercase or uppercase) */
// Do not count words that include: red twizzler licorice (r, t, l)
// Search for big word using words in dictionary, in big word
int fourC(){

    int numWords = 0;
    string word;
    Trie* words = new Trie();

    //Creating Trie with dictionary file
    ifstream dictionary;
    dictionary.open("dictionary.txt");
    while (!dictionary.eof() )
    {
        while(dictionary >> word ){

            //Adding each word to the Trie
                words->insert(word);
            }
    }

    //Reading in the file
    ifstream file;
    file.open("BigData.txt");
    bool contains_candy = false;
    bool search_word;

    while (!file.eof() )
        {

            while(file >> word ){

                //Make word lowercase
                transform(word.begin(), word.end(), word.begin(),
                               [](unsigned char c){ return tolower(c); });

                search_word = words->search(word);

                //check if word is in the dictionary.txt file.
                while(search_word){
                    //cout << word << endl;
                    //if word includes r, t or l do not count word
                    for (int i = 0; i < word.length(); i++)
                	{

                        if(word[i] == 'r')
                        {
                            contains_candy = true;
                            break;
                        }
                        else if (word[i] == 't')
                        {
                            contains_candy = true;
                            break;
                        }
                        else if(word[i] == 'l')
                        {
                            contains_candy = true;
                            break;
                        }

  	                }

                    if(!contains_candy) {
                        numWords++;
                    }

                    if(word.length() == 1)
                    {
                       break;
                    }

                    word.resize(word.length() - 1);
                    bool search_word = words->search(word);

                }

                contains_candy = false;

                }
        }

    return numWords;
}
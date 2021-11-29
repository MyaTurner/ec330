//Mya Turner, collaborated with Lesly Alcantara (leslyalc@bu.edu)
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
//resources: http://www.cplusplus.com/forum/beginner/14373/

using namespace std;
//a function that returns the number of occurrences of the specified string in the file
int StringSearch(string filename, string pattern)
{
    //Check if filename or pattern is empty
    if(filename.empty() || pattern.empty())
    {
        cout << "Can not check for occurrences if filename or specified pattern is empty" << endl;
        return 0;
    }

    //Need to remove " " from pattern
    pattern.erase( remove( pattern.begin(), pattern.end(), '\"' ), pattern.end());

    //Checking to see if the pattern occurs in user specified file
    int occurrences = 0;

    //Open file
    ifstream text_file (filename);
    string line;

    if (text_file.is_open())
    {

        /*While the file is good to read, take each line and check to see if the
        pattern exists.  If it does increase occurrences by 1. */

        while (text_file)
        {
            getline(text_file, line);
            while (line.find(pattern, 0) != string:: npos)
            {
                occurrences++;
                line.erase(line.find(pattern, 0), pattern.length());
            }


        }

        //Close file
        text_file.close();
    }
    else
    {
        cout << filename <<" failed to open." << endl;
    }

    //return occurrences
    return occurrences;
}
int main(int argc, char** argv) {

    //Reading in user input for filename and search pattern
    string filename = argv[1];
    string pattern = argv[2];
    int occurrences;

    //Running the StringSearch function
    occurrences = StringSearch(filename, pattern);

    //Print out the number of occurrences
    cout << occurrences << endl;

    return 0;
}


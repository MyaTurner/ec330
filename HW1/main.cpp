#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
   /* string name;
    cout << "Hello, World!" << endl;
    cout << "The man said \"Where are we going?\"" << endl;
    return 0; */

//    int matrix[3][3];
//
//        // asigning values, I suppose this is done allready.
//
//        for(int x=0;x<3;x++)
//        {
//            for(int y=0;y<3;y++)
//            {
//                matrix[x][y]=1;
//            }
//        }
//
//        // showing the matrix on the screen
//
//        for(int x=0;x<3;x++)  // loop 3 times for three lines
//        {
//            for(int y=0;y<3;y++)  // loop for the three elements on the line
//            {
//                cout<<matrix[x][y];  // display the current element out of the array
//            }
//            cout<<endl;  // when the inner loop is done, go to a new line
//        }
//        return 0;  // return 0 to the OS.
    string file_name;

    string filename;
    string pattern;
    string executable;
    int occurrences;

    ifstream text_file (file_name);
    string line;

    //Reading in user input for filename and search pattern
    cin >> executable >> filename;
    //Need to flush buffer here for initial space
    getline(cin, pattern);

    if (text_file.is_open())
    {
        /*While the file is good to read, take each line and check to see if the
        pattern exists.  If it does increase occurrences by 1. */

        while (text_file)
        {
            getline(text_file, line);

            if(line.find(pattern, 0) != string:: npos)
            {
                occurrences++;
            }
        }

        //Close file
        text_file.close();
    }
    else
    {
        cout << filename <<" failed to open." << endl;
    }

}

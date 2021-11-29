//
//Mya Turner, collaborated with Lesly Alcantara (leslyalc@bu.edu)
//
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

// a function that receives a non-negative integer N<= 7 grid of blanks, Xs and Os
void grid(const char* n) {

    int N;
    char* n_char = strdup(n);
    if(!isdigit(*n_char))
    {
       cout << "N must be an integer." << endl;
        return;
    }
    else
    {
        N = atoi(n_char);
    }

    //Making sure N is non-negative and no greater than 7
    if (N > 7 || N < 0) {
        cout << "N must be non-negative and no greater than 7." << endl;
        return;
    }

    //Initialize Values of Grid.
    int grid_size = 10;
    char array[grid_size][grid_size];

    for (int i = 0; i <= grid_size; i++) {
        for (int j = 0; j <= grid_size; j++) {

                array[i][j] = ' ';

        }
    }
//    array[0][0] = 'X';
//    array[1][0] = 'X';


    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {

//            array[0][0] = 'X';
//            array[1][0] = 'X';

            if (i == j && i <= N && j <= N) {
                array[i][j] = 'X';
                array[i + 1][j] = 'X';
               //cout << i << j << endl;
            }

        }
    }
   // array[1][0] = ' ';

    //if N is even place an O at (N+1, N+1)
    if( N % 2 == 0)
    {
        array[N + 1][N+ 1] = 'O';
    }
    else
    {
        //if N is odd place an O at (N, N+2) and (N+2, N+2) (in coordinate plane)
        array[N][N + 2] = 'O';
        array[N + 2][N+ 2] = 'O';
    }


    //Printing grid
    for (int i = grid_size - 1; i >= 0; i--) {
        for (int j = 0; j < grid_size; j++) {

            cout << array[i][j];
            //cout << i << j << endl;
        }
    cout << endl;

    }
    cout << endl;
}



int main(int argc, char** argv) {

    //Making sure N is an integer

    //Running grid function
    grid(argv[1]);

    return 0;
}


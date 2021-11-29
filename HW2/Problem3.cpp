//
// Mya Turner (mjturner@bu.edu), collaborated with Lesly Alcantara (leslyalc@bu.edu)
//

#include "Problem3.h"
#include <iostream>
#include <string>

using namespace std;

void MaxDecSeq (int *nums, int len)
{
    //If the len is zero, the array is empty and can not compute maximal decreasing sequence
    if (len == 0)
    {
        cout << "Length must be greater than zero.";
        return;
    }

    //If the len is 1, the maximal decreasing sequence is the array itself
    if (len == 1)
    {
            cout << nums[0];
            return;
    }

    //Need to print maximal decreasing sequence
    int *current_element = nums; //pointer to the first element
    int *next_element = nums + 1; //pointer to second element in nums
    string last_in_seq;
    //string s;

    for (int i = 0; i < len; i++)
    {
        if (next_element == nums + len) //if the next_element variable is out of bounds
        {
            break;
        }

        //If the current element is greater than the next element print and save the next element
        if (*current_element > *next_element)
        {
            cout << *current_element << " ";
            last_in_seq = to_string(*next_element);
            //current_element++;
        }

        current_element = next_element++;

    }
    if (last_in_seq.empty())  //if the current element is never greater than the next element print the first element
    {
        cout << nums[0];
    }
    else
    {
        cout << stoi(last_in_seq); //Print the least number in the decreasing sequence
    }

    return;
}




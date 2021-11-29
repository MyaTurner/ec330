//
//  main.cpp
//  ec330_hw2
//

#include "Problem3.h"

using namespace std;

int main() {
    
    int nums[] = {1, 5, 7, 3, 2, 4};
    //int nums[] = {2, 23, 3, 10, 1, 4, 7};
    //int nums[] = {1, 2};
    int length = sizeof(nums)/sizeof(nums[0]);
    
    MaxDecSeq(nums, length);
    return 0;
}

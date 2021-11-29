//
//  main.cpp
//  BloomFilter
//
//  Created by Tali Moreshet
//

#include <iostream>
#include "BloomFilter.h"

using namespace std;

int main(){
    string my_str = "HEYYYOOOOYASSGOOONO";
    
    /* Try different sizes here */
    BloomFilter my_filter(70);
    
    cout << "My empty filter looks like: " << my_filter.output() << endl;
    
    my_filter.insert(my_str);
    cout << "Inserting " << my_str << endl;
    cout << "My filter now looks like: " << my_filter.output() << endl;
    
    cout << "Is " << my_str << " in my filter? ";
    if (my_filter.exists(my_str)) cout << "\t\tYes." << endl;
    else cout << "\t\tNo." << endl;
    
    string fake_str = "bab";
    cout << "Is " << fake_str << " in my filter? ";
    if (my_filter.exists(fake_str)) cout << "\t\tYes." << endl;
    else cout << "\t\tNo." << endl;
}

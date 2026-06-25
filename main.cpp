#include "include/HashMap.h"
#include "include/LinkedList.h"
#include <bits/stdc++.h>
using namespace std;

class student {

    public:
    bool operator==(const student& other)const{
        return this==&other;
    }

};

int main(){
    
    DynamicArray<int>s;
    HashMap<DynamicArray<int>,string>map;

    map.insert(s,"Hello");
    cout<<map.get(s);

}
#include<string>
#pragma once
using namespace std;
// item class
class Item {
public:
    string name;// item name
    string description;// item description

    Item(string n = "", string d = "") {// constructor that initializes them to empty strings
        name = n;
        description = d;
    }
};
#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class Room {
public:
    string name; // Name of the room
    string description; // Description of the room
    unordered_map<string, Room*> neighbors; // Map to store neighboring rooms
    bool hasWaterBucket = false; // Flag to check if the player has the water bucket
    bool catFed = false; // Flag to check if the cat has been fed


    Room(string n, string d);
    void addNeighbor(string direction, Room* neighbor);
    Room* getNeighbor(string direction);
    void describe();
};


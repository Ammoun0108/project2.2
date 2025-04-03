#ifndef ROOM_H  // Preprocessor directive to avoid multiple inclusions of the header file.
#define ROOM_H

#include <iostream>  
#include <string>    
#include <unordered_map>  

using namespace std;

// Declaration of the 'room' class.
class room {
public:
    string name;  // The name of the room.
    string description;  // The description of the room.
    unordered_map<string, room*> neighbors;  // A map to store neighboring rooms in different directions.
    string specialItem;  // A special item found in the room (if any).
    bool isLocked;  // Indicates if the room is locked.
    void (*specialAction)();  // Pointer to a special action function associated with the room (if any).

    // Constructor for initializing the room.
    room(string name, string description, string specialItem = "", bool isLocked = false, void (*specialAction)() = nullptr);

    // Adds a neighboring room in a given direction.
    void addNeighbor(string direction, room* neighbor);

    // Retrieves the neighboring room in a given direction.
    room* getNeighbor(const string& direction);

    // Displays the room's name and description.
    void describe();

    // Handles the interaction with the room (take or give item).
    void interact(const string& input);

    // Function to take an item from the room.
    void takeItem(const string& item);

    // Function to give an item to the room.
    void giveItem(const string& item);
};

// External variables indicating whether the player has certain items.
extern bool hasKey;
extern bool hasWaterBucket;

// Functions for specific actions in the game.
void moveToRoom(room*& currentRoom, room* nextRoom);
void answerRiddle();
void giveWaterToCat();
void blackCatCurse();
void mysteriousChamberAction();

#endif  // End of the header guard.

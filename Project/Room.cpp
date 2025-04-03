#include "room.h"  // Includes the room header file to define the room class and functions.

bool hasKey = false;  // Initial state of whether the player has the key (false initially).
bool hasWaterBucket = false;  // Initial state of whether the player has the water bucket (false initially).

// Constructor to initialize the room.
room::room(string name, string description, string specialItem, bool isLocked, void (*specialAction)())
    : name(name), description(description), specialItem(specialItem), isLocked(isLocked), specialAction(specialAction) {}

// Adds a neighboring room in a specific direction.
void room::addNeighbor(string direction, room* neighbor) {
    neighbors[direction] = neighbor;
}

// Retrieves the neighboring room for a given direction.
room* room::getNeighbor(const string& direction) {
    return neighbors.count(direction) ? neighbors[direction] : nullptr;
}

// Describes the room by displaying its name and description.
void room::describe() {
    cout << name << ": " << description << endl;
}

// Handles interaction in the room based on the input.
void room::interact(const string& input) {
    if (input.rfind("take ", 0) == 0) {
        takeItem(input.substr(5));  // Calls takeItem if input starts with "take ".
    }
    else if (input.rfind("give ", 0) == 0) {
        giveItem(input.substr(5));  // Calls giveItem if input starts with "give ".
    }
    else {
        cout << "Invalid action!" << endl;  // If the input is invalid.
    }
}

// Function for taking an item from the room (water bucket in this case).
void room::takeItem(const string& item) {
    if (item == "water bucket" && name == "Lake") {  // Only take the water bucket if in the "Lake" room.
        if (!hasWaterBucket) {
            cout << "You take the water bucket. You might use it somewhere." << endl;
            hasWaterBucket = true;  // Player now has the water bucket.
        }
        else {
            cout << "The water bucket is already taken." << endl;  // If the player already has it.
        }
    }
    else {
        cout << "There's no such item to take here." << endl;  // If the item isn't available in the room.
    }
}

// Function for giving an item to the room (water in this case).
void room::giveItem(const string& item) {
    if (item == "water" && name == "North Room") {  // Give water to the cat in the "North Room".
        giveWaterToCat();
    }
    else {
        cout << "You can't give that item here." << endl;  // If giving item isn't allowed here.
    }
}

// Function to move the player to another room.
void moveToRoom(room*& currentRoom, room* nextRoom) {
    if (!nextRoom) {
        cout << "You can't go that way." << endl;  // If the next room doesn't exist.
        return;
    }
    if (nextRoom->isLocked && !hasKey) {  // If the room is locked and the player doesn't have the key.
        cout << "The treasure room is locked! You need a key." << endl;
        return;
    }
    currentRoom = nextRoom;  // Moves to the next room.
    currentRoom->describe();  // Displays the description of the new room.
    if (currentRoom->specialAction) {
        currentRoom->specialAction();  // Performs any special action associated with the room.
    }
}

// Function to solve the riddle in the treasure room.
void answerRiddle() {
    cout << "What is the capital of Egypt? ";
    string answer1;
    getline(cin, answer1);
    cout << "Who was the most famous Egyptian queen? ";
    string answer2;
    getline(cin, answer2);
    if (answer1 == "Cairo" && answer2 == "Cleopatra") {  // Check if both answers are correct.
        cout << "Correct! The treasure is yours! You win!" << endl;
    }
    else {
        cout << "Wrong answers! The room collapses! You are dead!" << endl;  // Incorrect answers lead to failure.
    }
    exit(0);  // End the game if the riddle is answered incorrectly.
}

// Function to give water to the cat in the "North Room".
void giveWaterToCat() {
    if (hasWaterBucket) {  // Only give water if the player has the water bucket.
        cout << "You give water to the thirsty cat. The cat is grateful and gives you a key!" << endl;
        hasKey = true;  // Player receives the key from the cat.
    }
    else {
        cout << "The cat looks thirsty. Maybe you should bring it something?. Dou you have it though? " << endl;
    }
}

// Function for the curse of the black cat.
void blackCatCurse() {
    if (hasKey) {
        cout << "A black cat appears and casts a spell on you! You feel the key slipping from your hands... It's gone!" << endl;
        hasKey = false;  // The key is taken away by the curse.
    }
    else {
        cout << "The black cat stares at you, but nothing happens." << endl;
    }
}

// Function for the mysterious chamber action.
void mysteriousChamberAction() {
    cout << "A soft humming fills the air, but nothing seems dangerous... yet." << endl;
}

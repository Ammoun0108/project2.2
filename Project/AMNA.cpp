// Written by Amna Ben Abdelkader:
// This project is an interactive text-based adventure game set inside an Egyptian pyramid. 
//The player explores various rooms, solving riddles, interacting with items and characters (such as a cat), and unlocking doors to progress. 
// The objective is to reach the treasure room by overcoming challenges, including taking and giving items, answering a riddle, and navigating through locked doors. 


#include "room.h"  // Includes the room header file to use the room class and its functions.

int main() {
    // Welcome the player
    cout << "Welcome to the Pyramid Adventure!" << endl;

    // Ask for the player's name
    cout << "What is your name? ";
    string playerName;
    getline(cin, playerName);

    // Greet the player by their name
    cout << "Hello, " << playerName << "! Get ready for your adventure." << endl;
    // Room initialization with names and descriptions.
    room outside("Outside the Pyramid", "A vast desert with a lake to the right. The pyramid entrance is ahead.");
    room lake("Lake", "A calm lake with a water bucket next to it.");
    room mainRoom("Main Room", "The central chamber of the pyramid with three doors: left, right, and north.");
    room closeEndRoom("Closed-End Room", "A dead-end with no exit.");
    room snakeRoom("Snake Room", "A room full of snakes! You can't go further. Sorry, you are dead.");
    room northRoom("North Room", "A chamber with four doors and a thirsty cat next to a mummy case.");
    room treasureRoom("Treasure Room", "An Egyptian dwarf guards the final challenge.", "riddle", true, answerRiddle);
    room blackCatRoom("Black Cat Room", "A dark chamber with a black cat sitting on a pedestal. It watches you with glowing eyes.", "", false, blackCatCurse);
    room mysteriousChamber("Mysterious Chamber", "An eerie room with glowing hieroglyphs and an unknown presence.", "", false, mysteriousChamberAction);

    // Adding neighbors to rooms (creating the structure of the pyramid).
    outside.addNeighbor("right", &lake);
    outside.addNeighbor("north", &mainRoom);
    lake.addNeighbor("left", &outside);
    mainRoom.addNeighbor("right", &closeEndRoom);
    closeEndRoom.addNeighbor("left", &mainRoom);
    mainRoom.addNeighbor("left", &snakeRoom);
    mainRoom.addNeighbor("north", &northRoom);
    mainRoom.addNeighbor("south", &outside);
    northRoom.addNeighbor("south", &mainRoom);
    northRoom.addNeighbor("north", &treasureRoom);
    northRoom.addNeighbor("right", &blackCatRoom);
    northRoom.addNeighbor("left", &mysteriousChamber);

    blackCatRoom.addNeighbor("left", &northRoom);
    mysteriousChamber.addNeighbor("right", &northRoom);

    room* currentRoom = &outside;  // Starting room is "Outside the Pyramid."
    currentRoom->describe();  // Describe the starting room.

    string input;
    while (true) {  // Main game loop.
        cout << "\nWhat do you want to do? (go [direction], take [item], give [item], quit): ";
        getline(cin, input);  // Get the player's input.

        if (input.rfind("go ", 0) == 0) {  // If the player wants to move.
            moveToRoom(currentRoom, currentRoom->getNeighbor(input.substr(3)));
        }
        else if (input == "quit") {  // If the player wants to quit.
            cout << "Thanks for playing!" << endl;
            break;  // Exit the game.
        }
        else {
            currentRoom->interact(input);  // If it's an item interaction, handle it.
        }
    }

    return 0;  // End of the program.
}


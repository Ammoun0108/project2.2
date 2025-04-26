

// Written by Amna Ben Abdelkader
// Interactive text-based adventure game set inside an Egyptian pyramid.
// The player explores rooms, picks up and uses items, solves riddles, and interacts with characters.
// The objective is to unlock the treasure room and win the game.

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Item.cpp"
#include "Player.cpp"
#include "Room.cpp"

using namespace std;

// Special action when interacting with the cat in the North Room
void catAction(Player* player) {
    cout << "A  black cat sits in front of you near the north door!" << endl;
    if (player->hasItem("water bucket")) {
        cout << "The cat glances at your water bucket and meows softly. Maybe it wants you to leave it here..." << endl;
    }
    else {
        if (!player->hasItem("key"))
        cout << "The cat looks thirsty. Maybe it wants water." << endl;
    }
}

// Special action for the treasure room: the player must answer riddles and have the correct items
void winRoomAction(Player* player) {
    if (!player->hasItem("key")) {
        cout << "The door is locked. You need a key to enter." << endl;
        return;
    }

    cout << "A small dwarf blocks your path." << endl;
    cout << "Dwarf: First, answer my riddles." << endl;

    cout << "Dwarf: What is the capital of Egypt? ";
    string answer1;
    getline(cin, answer1);

    cout << "Dwarf: Who was the most famous Egyptian queen? ";
    string answer2;
    getline(cin, answer2);

    if (answer1 != "Cairo" || answer2 != "Cleopatra") {
        cout << "Dwarf: Wrong answers! You shall not pass!" << endl;
        return;
    }

    cout << "Dwarf: Hmm... impressive. Now let's see if you are truly worthy." << endl;

    if (player->hasItem("coin") && player->hasItem("torch")) {
        cout << "The dwarf nods and steps aside. You enter the treasure room." << endl;
        cout << "Congratulations, you win!" << endl;
        exit(0);
    }
    else {
        cout << "Dwarf: You lack the items I seek. Come back with a coin and a torch." << endl;
    }
}

// Handle all player commands like moving, picking up, dropping, interacting
void handleCommand(const string& input, Room*& currentRoom, Player& player) {
    static bool catGaveKey = false; // Tracks if the cat already gave the key

    if (input == "quit") {
        cout << "Thanks for playing!" << endl;
        exit(0);
    }
    else if (input == "inventory") {
        player.viewInventory();
    }
    else if (input == "help") {
        player.listCommands();
    }
    else if (input.rfind("go ", 0) == 0) { // Movement command
        string dir = input.substr(3);
        if (currentRoom->neighbors.count(dir)) {
            currentRoom = currentRoom->neighbors[dir];
            currentRoom->describe(&player); // Describe the new room after moving
            if (currentRoom->specialAction)
                currentRoom->specialAction(&player);
        
        }
        else {
            cout << "You can't go that way." << endl;
        }
    }
    else if (input.rfind("take ", 0) == 0) { // Pick up an item
        currentRoom->takeItem(&player, input.substr(5));
    }
    else if (input.rfind("drop ", 0) == 0) { // Drop an item
        string itemName = input.substr(5);
        currentRoom->dropItem(&player, itemName);

        // Special case: if the player drops the water bucket in North Room
        if (!catGaveKey && currentRoom->name == "North Room" && itemName == "water bucket") {
            cout << "The cat finds the water bucket you left. It drinks eagerly and drops a key in front of you!" << endl;
            player.addItem(Item("key", "A key to unlock the treasure room."));
            catGaveKey = true;
        }
    }
    else if (input == "interact") { // Special room action
        if (currentRoom->specialAction) {
            currentRoom->specialAction(&player);
        }
        else {
            cout << "There is nothing special here." << endl;
        }
    }
    else {
        cout << "Unknown command. Type 'help' to see available commands." << endl;
    }
}

int main() {
    // Greet player and get their name
    cout << "Welcome to the Pyramid Adventure!\nWhat's your name? ";
    string name;
    getline(cin, name);
    Player player(name);
    cout << "Hi " << name << "!\nGet ready for a trip to Egypt." << endl;

    // Create all rooms
    Room outside("Outside", "You stand before an ancient pyramid. There is a lake to your right.");
    Room lake("Lake", "A quiet lake.");
    Room main("Main Room", "You are in the main hall. Multiple paths branch off.");
    Room torchRoom("Vast Room", "It leads nowhere.");
    Room closeEndRoom("Closed-End Room", "A corridor that leads nowhere.");
    Room snakeRoom("Snake Room", "The floor is covered in snake bones. You feel uneasy.");
    Room northRoom("North Room", "A chamber with a tomb next to a big door north.");
    northRoom.isLocked = true;
    Room creatureRoom("Mummy Room", "A dark room. A Mummy stares silently.");
    Room mysteriousChamber("Mysterious Chamber", "Glowing symbols on the wall pulse faintly.");
    Room treasureRoom("Treasure Room", "A guarded door stands before you. A dwarf watches.");

    // Add items to rooms
    lake.addItem(Item("water bucket", "A wooden bucket that can hold water."));
    torchRoom.addItem(Item("torch", "An unlit torch. Might be useful."));
    torchRoom.addItem(Item("knife", " A golden knife with diamonds on it"));
    main.addItem(Item("coin", "An ancient Egyptian coin."));

    // Set special actions for specific rooms
    northRoom.specialAction = catAction;
    treasureRoom.specialAction = winRoomAction;
    creatureRoom.specialAction = [](Player* player) {
        if (player->hasItem("key")) {
            cout << "The mummy hisses. Your key vanishes! You need to quit and start again :(" << endl;
            player->dropItem("key");
            
        }
        else {
            cout << "The mummy just watches you..." << endl;
        }
        };
    mysteriousChamber.specialAction = [](Player* player) {
        cout << "The walls glow faintly. Something about this place feels important..." << endl;
        };

    // Connect rooms together
    outside.addNeighbor("north", &main);
    outside.addNeighbor("right", &lake);
    lake.addNeighbor("left", &outside);

    main.addNeighbor("south", &outside);
    main.addNeighbor("north", &northRoom);
    main.addNeighbor("left", &torchRoom);
    main.addNeighbor("right", &snakeRoom);
    snakeRoom.addNeighbor("left", &main);
    torchRoom.addNeighbor("right", &main);
    northRoom.addNeighbor("south", &main);
    northRoom.addNeighbor("north", &treasureRoom);
    northRoom.addNeighbor("right", &creatureRoom);
    northRoom.addNeighbor("left", &mysteriousChamber);
    creatureRoom.addNeighbor("left", &northRoom);
    mysteriousChamber.addNeighbor("right", &northRoom);
    treasureRoom.addNeighbor("south", &northRoom);

    // Start game at the outside of the pyramid
    Room* currentRoom = &outside;

    // Describe the starting room
    cout << endl;
    currentRoom->describe(&player);

    // Main game loop
    string input;
    while (true) {
        cout << "\nWhat do you want to do? (type 'help' for options): ";
        getline(cin, input);
        handleCommand(input, currentRoom, player);
    }

    return 0;
}


#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class Room {
public:
    string name;
    string description;
    unordered_map<string, Room*> neighbors;
    bool hasWaterBucket = false;
    bool catFed = false;

    Room(string n, string d) : name(n), description(d) {}

    void addNeighbor(string direction, Room* neighbor) {
        neighbors[direction] = neighbor;
    }

    Room* getNeighbor(string direction) {
        if (neighbors.find(direction) != neighbors.end())
            return neighbors[direction];
        else {
            cout << "You can't go that way!" << endl;
            return nullptr;
        }
    }

    void describe() {
        cout << "\nYou are in " << name << ". " << description << "\n";
    }
};

int main() {
    string input, direction;
    bool hasKey = false;

    // Creating Room objects
    Room outside("Outside the Pyramid", "A vast desert with a lake to the right. The pyramid entrance is ahead.");
    Room lake("Lake", "A calm lake with a water bucket next to it.");
    Room mainRoom("Main Room", "The central chamber of the pyramid with three doors: left (snakes), right (dead-end), and north.");
    Room closeEndRoom("Closed-End Room", "A dead-end with no exit.");
    Room snakeRoom("Snake Room", "A room full of snakes! You can't go further.");
    Room northRoom("North Room", "A chamber with four doors and a thirsty cat next to a mummy case.");
    Room leftRoom("Left Room", "A mysterious chamber leading to a deeper part of the pyramid.");
    Room wrongDoor1("Wrong Door 1", "An ancient black creature emerges! You must run back!");
    Room wrongDoor2("Wrong Door 2", "The pyramid starts crumbling! You rush back just in time.");
    Room treasureRoom("Treasure Room", "An Egyptian dwarf guards the final challenge.");

    // Setting up room neighbors
    outside.addNeighbor("right", &lake);
    outside.addNeighbor("front", &mainRoom);

    lake.addNeighbor("left", &outside);

    mainRoom.addNeighbor("right", &closeEndRoom);
    mainRoom.addNeighbor("left", &snakeRoom);
    mainRoom.addNeighbor("north", &northRoom);
    mainRoom.addNeighbor("south", &outside);

    northRoom.addNeighbor("south", &mainRoom);
    northRoom.addNeighbor("left", &wrongDoor1);
    northRoom.addNeighbor("right", &wrongDoor2);
    northRoom.addNeighbor("front", &leftRoom);

    leftRoom.addNeighbor("front", &treasureRoom);

    // Starting position
    Room* currentRoom = &outside;
    currentRoom->describe();

    while (true) {
        cout << "\nWhat do you want to do? (move [direction], take bucket, give water, open case, answer dwarf, quit): ";
        getline(cin, input);

        if (input.substr(0, 5) == "move ") {
            direction = input.substr(5);
            Room* nextRoom = currentRoom->getNeighbor(direction);
            if (nextRoom != nullptr) {
                currentRoom = nextRoom;
                currentRoom->describe();
            }
        }
        else if (input == "take bucket" && currentRoom == &lake) {
            lake.hasWaterBucket = true;
            cout << "You picked up the water bucket." << endl;
        }
        else if (input == "give water" && currentRoom == &northRoom && lake.hasWaterBucket) {
            northRoom.catFed = true;
            cout << "You gave water to the cat. The cat gives you a key!" << endl;
            hasKey = true;
        }
        else if (input == "open case" && currentRoom == &northRoom && hasKey) {
            cout << "You unlocked the mummy case! Inside is a hidden passage forward." << endl;
            northRoom.addNeighbor("front", &leftRoom);
        }
        else if (input == "answer dwarf" && currentRoom == &treasureRoom) {
            string answer1, answer2;
            cout << "What is the capital of Egypt? ";
            cin >> answer1;
            cout << "Who was the most famous Egyptian queen? ";
            cin >> answer2;
            if (answer1 == "Cairo" && answer2 == "Cleopatra") {
                cout << "Correct! The treasure is yours! You win!" << endl;
                break;
            }
            else {
                cout << "Wrong answers! The dwarf kicks you out!" << endl;
                currentRoom = &northRoom;
            }
        }
        else if (input == "quit") {
            cout << "Thanks for playing!" << endl;
            break;
        }
        else {
            cout << "Invalid command." << endl;
        }
    }
    return 0;
}


#include "Item.cpp" // Include the Item class definition
#include "Player.cpp" // Include the Player class definition

#pragma once // Prevent multiple inclusions of this file

// Room class represents a location inside the pyramid
class Room {
public:
    string name; // Name of the room
    string description; // Description of the room
    unordered_map<string, Room*> neighbors; // Directions mapped to neighboring rooms
    unordered_map<string, Item> items; // Items present in the room, mapped by item name
    bool isLocked = false; // Flag to indicate if the room is locked

    // Pointer to a special action function that takes a Player pointer as parameter
    void (*specialAction)(Player* player) = nullptr;

    // Constructor to initialize room name and description
    Room(string n, string d) : name(n), description(d) {}

    // Add a neighboring room in a specific direction
    void addNeighbor(string dir, Room* room) {
        neighbors[dir] = room;
    }

    // Add an item to the room's item map
    void addItem(const Item& item) {
        items[item.name] = item;
    }

    // Describe the room to the player: print the name, description, and list items
    void describe(Player* player) {
        cout << name << ": " << description << endl;
        if (!items.empty()) {
            cout << "Items here:" << endl;
            for (auto& pair : items) {
                cout << "- " << pair.second.name << ": " << pair.second.description << endl;
            }
        }
    }

    // Let the player take an item from the room
    void takeItem(Player* player, const string& itemName) {
        bool response;
        if (items.count(itemName)) {
            response = player->addItem(items[itemName]); // Attempt to add item to player's inventory
            if (response == 1) // Only remove from room if successfully added
                items.erase(itemName);
        }
        else {
            cout << "No such item here." << endl;
        }
    }

    // Let the player drop an item into the room
    void dropItem(Player* player, const string& itemName) {
        if (player->hasItem(itemName)) {
            items[itemName] = player->inventory[itemName]; // Add the item to room
            player->dropItem(itemName); // Remove item from player's inventory
        }
        else {
            cout << "You don't have that item." << endl;
        }
    }
};

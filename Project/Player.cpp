#pragma once // Prevents multiple inclusion of this file

#include <iostream>  
#include <string>    
#include <unordered_map>  
#include "Item.cpp"   // Include the Item class definition

using namespace std;

// Player class stores the player's name and inventory
class Player {
public:
    string name; // Player's name
    unordered_map<string, Item> inventory; // Player's inventory: maps item names to Item objects

    // Constructor to initialize player name
    Player(string n) : name(n) {}

    // Adds an item to the player's inventory
    bool addItem(const Item& item) {
        if (inventory.size() < 3) { // Limit: no more than three items at a time to make the game more fun
            inventory[item.name] = item; // Add the item by its name
            cout << "You picked up: " << item.name << endl;
            return 1; // Successfully added
        }
        else {
            cout << "You cannot pick up four things at a time. You might want to drop something." << endl;
            return 0; // Failed to add (inventory full)
        }
    }

    // Drops an item from the player's inventory
    void dropItem(const string& itemName) {
        if (inventory.count(itemName)) {
            
            cout << "You dropped: " << inventory[itemName].name << endl;
            inventory.erase(itemName); // Remove the item
         
        }
       
        else {
            cout << "You don't have that item." << endl;
        }
    }

    // Displays the contents of the player's inventory
    void viewInventory() {
        if (inventory.empty()) {
            cout << "Your inventory is empty." << endl;
        }
        else {
            cout << "Your inventory contains:" << endl;
            for (auto& pair : inventory) {
                cout << "- " << pair.second.name << ": " << pair.second.description << endl;
            }
        }
    }

    // Checks if the player has a specific item
    bool hasItem(const string& itemName) {
        return inventory.count(itemName);
    }

    // Lists all available commands the player can use
    void listCommands() {
        cout << "Available commands:" << endl;
        cout << "- go [direction] (e.g., go north)" << endl;
        cout << "- take [item]" << endl;
        cout << "- drop [item]" << endl;
        cout << "- inventory" << endl;
        cout << "- help" << endl;
        cout << "- quit" << endl;
    }
};

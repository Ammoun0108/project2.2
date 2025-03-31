
#include "Room.h"

Room::Room(string n, string d) : name(n), description(d) {}

void Room::addNeighbor(string direction, Room* neighbor) {
    neighbors[direction] = neighbor;
}

Room* Room::getNeighbor(string direction) {
    if (neighbors.find(direction) != neighbors.end()) {
        return neighbors[direction];
    }
    cout << "You can't go that way!" << endl;
    return nullptr;
}

void Room::describe() {
    cout << "\nYou are in " << name << ". " << description << "\n";
}

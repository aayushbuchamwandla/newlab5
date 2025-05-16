#include <iostream>
#include "card.h"
#include "BST.h"  // Assuming your BST header is correctly implemented

void playGame(BST& Bob, BST& Alice) {
    // Assuming some iterator 'it' for the deck, for example:
    for (auto it = deck.begin(); it != deck.end(); ++it) { 
        // Using the const-correct methods
        if (Bob.contains(it->getRank())) {
            Bob.remove(it->getRank());
        }
        if (Alice.contains(it->getRank())) {
            Alice.remove(it->getRank());
        }
    }
}

int main() {
    // Example setup for BST objects and game logic
    BST Bob, Alice;
    playGame(Bob, Alice);
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"

using namespace std;

void playGame(BST& Alice, BST& Bob) {
    bool found = false;

    // Main game loop: Match Alice's and Bob's cards
    while (true) {
        found = false;

        // Alice's turn: Try to find matching card in Bob's deck
        for (auto it = Alice.begin(); it != Alice.end(); ++it) {
            if (Bob.contains(it->getRank())) {
                cout << "Alice picked matching card " << *it << endl;
                Bob.remove(it->getRank());
                Alice.remove(it->getRank());
                found = true;
                break;
            }
        }

        if (!found) break;

        found = false;

        // Bob's turn: Try to find matching card in Alice's deck (in reverse order)
        for (auto it = Bob.rbegin(); it != Bob.rend(); ++it) {
            if (Alice.contains(it->getRank())) {
                cout << "Bob picked matching card " << *it << endl;
                Alice.remove(it->getRank());
                Bob.remove(it->getRank());
                found = true;
                break;
            }
        }

        if (!found) break;
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argv[1]);
    ifstream cardFile2(argv[2]);
    string line;

    if (cardFile1.fail() || cardFile2.fail()) {
        cout << "Could not open file " << argv[2];
        return 1;
    }

    BST Alice;
    BST Bob;

    // Read Alice's cards
    while (getline(cardFile1, line) && (line.length() > 0)) {
        char suit = line[0];
        string rank = line.substr(2);
        Alice.insert(Card(suit, rank));
    }
    cardFile1.close();

    // Read Bob's cards
    while (getline(cardFile2, line) && (line.length() > 0)) {
        char suit = line[0];
        string rank = line.substr(2);
        Bob.insert(Card(suit, rank));
    }
    cardFile2.close();

    // Play the game
    playGame(Alice, Bob);

    // Print final card lists
    cout << "Alice's cards:" << endl;
    Alice.printDeck();

    cout << "Bob's cards:" << endl;
    Bob.printDeck();

    return 0;
}

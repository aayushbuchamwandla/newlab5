// main.cpp
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream aliceFile(argv[1]);
    ifstream bobFile(argv[2]);
    string line;

    if (aliceFile.fail() || bobFile.fail()) {
        cout << "Could not open one or both of the input files." << endl;
        return 1;
    }

    BST aliceDeck, bobDeck;

    // Read Alice's cards
    while (getline(aliceFile, line) && !line.empty()) {
        char suit = line[0];
        string rank = line.substr(2);
        aliceDeck.insert(Card(suit, rank));
    }
    aliceFile.close();

    // Read Bob's cards
    while (getline(bobFile, line) && !line.empty()) {
        char suit = line[0];
        string rank = line.substr(2);
        bobDeck.insert(Card(suit, rank));
    }
    bobFile.close();

    // Play the game
    playGame(aliceDeck, bobDeck);

    // Print final hands
    cout << "Alice's cards:" << endl;
    aliceDeck.printDeck();

    cout << "Bob's cards:" << endl;
    bobDeck.printDeck();

    return 0;
}
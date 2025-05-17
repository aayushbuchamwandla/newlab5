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


   ifstream cardFile1(argv[1]);
   ifstream cardFile2(argv[2]);
   string line;


   if (cardFile1.fail() || cardFile2.fail()) {
       cout << "Could not open one of the files." << endl;
       return 1;
   }


   BST Alice;
   BST Bob;


   // Load Alice's cards
   while (getline(cardFile1, line) && !line.empty()) {
       char suit = line[0];
       string rank = line.substr(2);
       Alice.insert(Card(suit, rank));
   }
   cardFile1.close();


   // Load Bob's cards
   while (getline(cardFile2, line) && !line.empty()) {
       char suit = line[0];
       string rank = line.substr(2);
       Bob.insert(Card(suit, rank));
   }
   cardFile2.close();


   while (true) {
       bool found = false;


       // Alice picks matching card
       int aliceRemoveRank = -1;
       for (BST::Iterator it = Alice.begin(); it != Alice.end(); ++it) {
           int rank = (*it).getRank();
           if (Bob.contains(rank)) {
               cout << "Alice picked matching card " << *it << endl;
               aliceRemoveRank = rank;
               found = true;
               break;
           }
       }
       if (aliceRemoveRank != -1) {
           Alice.remove(aliceRemoveRank);
           Bob.remove(aliceRemoveRank);
       }
       if (!found) break;


       found = false;


       // Bob picks matching card from highest down
       int bobRemoveRank = -1;
       for (BST::ReverseIterator rit = Bob.rbegin(); rit != Bob.rend(); --rit) {
           int rank = (*rit).getRank();
           if (Alice.contains(rank)) {
               cout << "Bob picked matching card " << *rit << endl;
               bobRemoveRank = rank;
               found = true;
               break;
           }
       }
       if (bobRemoveRank != -1) {
           Bob.remove(bobRemoveRank);
           Alice.remove(bobRemoveRank);
       }
       if (!found) break;
   }


   cout << "Alice's remaining cards: ";
   Alice.printDeck();


   cout << "Bob's remaining cards: ";
   Bob.printDeck();


   return 0;
}



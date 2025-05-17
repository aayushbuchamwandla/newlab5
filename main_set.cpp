#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"


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


   set<Card> Alice;
   set<Card> Bob;


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


       // Alice picks matching card: from smallest to largest
       for (auto it = Alice.begin(); it != Alice.end(); ++it) {
           // Find matching card by rank in Bob
           int rank = it->getRank();


           // Bob search by rank, need to find any card in Bob with that rank
           auto bobIt = find_if(Bob.begin(), Bob.end(), [rank](const Card& c) {
               return c.getRank() == rank;
           });


           if (bobIt != Bob.end()) {
               cout << "Alice picked matching card " << *it << endl;
               Bob.erase(bobIt);
               Alice.erase(it);
               found = true;
               break;
           }
       }


       if (!found) break;


       found = false;


       // Bob picks matching card: from largest to smallest
       for (auto rit = Bob.rbegin(); rit != Bob.rend(); ++rit) {
           int rank = rit->getRank();


           auto aliceIt = find_if(Alice.begin(), Alice.end(), [rank](const Card& c) {
               return c.getRank() == rank;
           });


           if (aliceIt != Alice.end()) {
               cout << "Bob picked matching card " << *rit << endl;
               Alice.erase(aliceIt);
               // Erase by reverse iterator requires trick:
               // convert reverse iterator to normal iterator:
               Bob.erase(next(rit).base());
               found = true;
               break;
           }
       }
       if (!found) break;
   }


   cout << "Alice's remaining cards: ";
   for (const Card& c : Alice)
       cout << c << " ";
   cout << endl;


   cout << "Bob's remaining cards: ";
   for (const Card& c : Bob)
       cout << c << " ";
   cout << endl;


   return 0;
}

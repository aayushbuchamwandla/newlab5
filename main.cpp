// This file should implement the game using a custom implementation of a BST (that is based on your implementation from lab02)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
//Do not include set in this file


using namespace std;


int main(int argv, char** argc){
 if(argv < 3){
   cout << "Please provide 2 file names" << endl;
   return 1;
 }
  ifstream cardFile1 (argc[1]);
 ifstream cardFile2 (argc[2]);
 string line;


 if (cardFile1.fail() || cardFile2.fail() ){
   cout << "Could not open file " << argc[2];
   return 1;
 }


 BST Alice;
 BST Bob;


 while (getline (cardFile1, line) && (line.length() > 0)){
   char suit = line[0];
   string rank = line.substr(2);
   Alice.insert(Card(suit,rank));
 }
 cardFile1.close();




 while (getline (cardFile2, line) && (line.length() > 0)){
   char suit = line[0];
   string rank = line.substr(2);
   Bob.insert(Card(suit,rank));
 }
 cardFile2.close();
 //   playGame(Alice,Bob);


 cout<<"Alice's cards: "<<endl;
 Alice.printDeck();


 cout<<"Bob's cards: "<<endl;
 Bob.printDeck();
  return 0;
}

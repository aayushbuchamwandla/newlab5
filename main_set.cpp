// main_set.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"


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


    set<Card> Alice;
    set<Card> Bob;


    //Read each file
    while (getline (cardFile1, line) && (line.length() > 0)){
        char suit = line[0];
        string rank = line.substr(2);
        Card c(suit,rank);
        Alice.insert(c);
    }
    cardFile1.close();




    while (getline (cardFile2, line) && (line.length() > 0)){
        char suit = line[0];
        string rank = line.substr(2);
        Card c(suit,rank);
        Bob.insert(c);
    }
    cardFile2.close();
     while (true) {
        bool found = false;


        for (const auto& A: Alice) {
            if (Bob.count(A)) {
                cout<<"Alice picked matching card "<<A<<endl;
                Bob.erase(A);
                Alice.erase(A);
                found = true;
                break;
            }
        }
        if (found == false) {
            break;
        }


        found = false;


        auto i = Bob.rbegin();
        while (i != Bob.rend()) {
            if (Alice.count(*i)) {
                cout<<"Bob picked matching card "<<*i<<endl;
                found = true;
                Alice.erase(*i);
                Bob.erase(*i);
                break;
            }
            ++i;
        }
        if (found == false) {
            break;
        }
    }


    cout<<"Alice's cards: "<<endl;
    for (const auto& card: Alice) {
        cout<<card<<endl;
    }


    cout<<"Bob's cards: "<<endl;
    for (const auto& card: Bob) {
        cout<<card<<endl;
    }


    return 0;
}
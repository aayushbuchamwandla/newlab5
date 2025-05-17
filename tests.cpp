// tests.cpp
#include "card_list.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

void test_card_comparison() {
    Card c1('c', "a");
    Card c2('d', "a");
    Card c3('c', "2");
    Card c4('h', "k");

    assert(c1 < c2);
    assert(c1 < c3);
    assert(c2 < c4);
    assert(c3 < c4);
    assert(!(c1 == c2));
    assert(c1 == Card('c', "a"));
    assert(c4 > c1);

    cout << "Card comparison tests passed!" << endl;
}

void test_bst_insert() {
    BST tree;
    Card c1('c', "a");
    Card c2('d', "2");
    Card c3('h', "k");

    tree.insert(c1);
    assert(tree.contains(c1));
    tree.insert(c2);
    assert(tree.contains(c2));
    tree.insert(c3);
    assert(tree.contains(c3));
    tree.insert(c1); // Inserting duplicate
    assert(tree.contains(c1));

    cout << "BST insert tests passed!" << endl;
}

void test_bst_remove() {
    BST tree;
    Card c1('c', "a");
    Card c2('d', "2");
    Card c3('h', "k");
    Card c4('s', "3");

    // Removing from empty tree
    assert(!tree.remove(c1));

    tree.insert(c1);
    tree.insert(c2);
    tree.insert(c3);
    tree.insert(c4);

    // Removing a leaf node
    assert(tree.remove(c4));
    assert(!tree.contains(c4));
    assert(tree.contains(c1));
    assert(tree.contains(c2));
    assert(tree.contains(c3));

    // Removing a node with only left child (not explicitly added in this test case, but generally handled)

    // Removing a node with only right child (not explicitly added in this test case, but generally handled)

    // Removing a node with two children
    assert(tree.remove(c2));
    assert(!tree.contains(c2));
    assert(tree.contains(c1));
    assert(tree.contains(c3));

    // Removing the root
    assert(tree.remove(c1));
    assert(!tree.contains(c1));
    assert(tree.contains(c3));

    assert(tree.remove(c3));
    assert(!tree.contains(c3));
    assert(tree.isEmpty());

    // Removing a non-existent card from an empty tree
    assert(!tree.remove(c1));

    cout << "BST remove tests passed!" << endl;
}

void test_bst_contains() {
    BST tree;
    Card c1('c', "a");
    Card c2('d', "2");

    assert(!tree.contains(c1));
    tree.insert(c1);
    assert(tree.contains(c1));
    assert(!tree.contains(c2));
    tree.insert(c2);
    assert(tree.contains(c2));

    cout << "BST contains tests passed!" << endl;
}

void test_bst_printDeck() {
    BST tree;
    stringstream ss;
    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    tree.printDeck();
    assert(ss.str() == "\n");
    ss.str("");

    tree.insert(Card('d', "2"));
    tree.insert(Card('c', "a"));
    tree.insert(Card('h', "k"));
    tree.printDeck();
    assert(ss.str() == "c a\nd 2\nh k\n");

    cout.rdbuf(oldCout);
    cout << "BST printDeck tests passed!" << endl;
}

void test_bst_getSuccessorNode() {
    BST tree;
    Card c1('c', "3");
    Card c2('d', "5");
    Card c3('h', "7");
    tree.insert(c2);
    tree.insert(c1);
    tree.insert(c3);

    BST::Node* node1 = tree.getNodeFor(c1);
    BST::Node* node2 = tree.getNodeFor(c2);
    BST::Node* node3 = tree.getNodeFor(c3);

    assert(tree.getSuccessorNodeInternal(node1)->card == c2);
    assert(tree.getSuccessorNodeInternal(node2)->card == c3);
    assert(tree.getSuccessorNodeInternal(node3) == nullptr);
    assert(tree.getSuccessorNodeInternal(nullptr) == nullptr);

    cout << "BST getSuccessorNode tests passed!" << endl;
}

void test_bst_getPredecessorNode() {
    BST tree;
    Card c1('c', "3");
    Card c2('d', "5");
    Card c3('h', "7");
    tree.insert(c2);
    tree.insert(c1);
    tree.insert(c3);

    BST::Node* node1 = tree.getNodeFor(c1);
    BST::Node* node2 = tree.getNodeFor(c2);
    BST::Node* node3 = tree.getNodeFor(c3);

    assert(tree.getPredecessorNodeInternal(node3)->card == c2);
    assert(tree.getPredecessorNodeInternal(node2)->card == c1);
    assert(tree.getPredecessorNodeInternal(node1) == nullptr);
    assert(tree.getPredecessorNodeInternal(nullptr) == nullptr);

    cout << "BST getPredecessorNode tests passed!" << endl;
}

void test_iterator_empty() {
    BST tree;
    assert(tree.begin() == tree.end());
    assert(tree.rbegin() == tree.rend());
    cout << "Iterator on empty tree tests passed!" << endl;
}

void test_iterator_single() {
    BST tree;
    tree.insert(Card('c', "a"));
    BST::Iterator it = tree.begin();
    assert(it != tree.end());
    assert(*it == Card('c', "a"));
    ++it;
    assert(it == tree.end());
    BST::Iterator rit = tree.rbegin();
    assert(rit != tree.rend());
    assert(*rit == Card('c', "a"));
    --rit;
    assert(rit == tree.rend());
    cout << "Iterator on single node tree tests passed!" << endl;
}

void test_iterator_multiple() {
    BST tree;
    tree.insert(Card('d', "2"));
    tree.insert(Card('c', "a"));
    tree.insert(Card('h', "k"));

    vector<Card> forward;
    for (BST::Iterator it = tree.begin(); it != tree.end(); ++it) {
        forward.push_back(*it);
    }
    assert(forward.size() == 3);
    assert(forward[0] == Card('c', "a"));
    assert(forward[1] == Card('d', "2"));
    assert(forward[2] == Card('h', "k"));

    vector<Card> reverse;
    for (BST::Iterator it = tree.rbegin(); it != tree.rend(); --it) {
        reverse.push_back(*it);
    }
    assert(reverse.size() == 3);
    assert(reverse[0] == Card('h', "k"));
    assert(reverse[1] == Card('d', "2"));
    assert(reverse[2] == Card('c', "a"));

    cout << "Iterator on multiple nodes tree tests passed!" << endl;
}

void test_iterator_increment_past_end() {
    BST tree;
    tree.insert(Card('c', "a"));
    BST::Iterator it = tree.begin();
    ++it;
    assert(it == tree.end());
    ++it; // Should not crash
    assert(it == tree.end());
    cout << "Iterator increment past end tests passed!" << endl;
}

void test_iterator_decrement_past_rend() {
    BST tree;
    tree.insert(Card('c', "a"));
    BST::Iterator rit = tree.rbegin();
    --rit;
    assert(rit == tree.rend());
    --rit; // Should not crash
    assert(rit == tree.rend());
    cout << "Iterator decrement past rend tests passed!" << endl;
}

void test_iterator_comparison_ops() {
    BST tree;
    tree.insert(Card('c', "a"));
    BST::Iterator it1 = tree.begin();
    BST::Iterator it2 = tree.begin();
    BST::Iterator it_end = tree.end();

    assert(it1 == it2);
    assert(!(it1 != it2));
    assert(it1 != it_end);
    assert(!(it1 == it_end));

    cout << "Iterator comparison operators tests passed!" << endl;
}

void test_playGame_common() {
    BST alice, bob;
    alice.insert(Card('c', "3"));
    alice.insert(Card('d', "a"));
    bob.insert(Card('d', "a"));
    bob.insert(Card('c', "3"));

    stringstream ss;
    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    playGame(alice, bob);

    cout.rdbuf(oldCout);
    string output = ss.str();
    assert(output.find("Alice picked matching card c 3") != string::npos);
    assert(output.find("Bob picked matching card d a") != string::npos);

    assert(!alice.contains(Card('c', "3")));
    assert(!alice.contains(Card('d', "a")));
    assert(!bob.contains(Card('c', "3")));
    assert(!bob.contains(Card('d', "a")));

    cout << "playGame with common cards test passed!" << endl;
}

void test_playGame_no_common() {
    BST alice, bob;
    alice.insert(Card('c', "a"));
    bob.insert(Card('d', "2"));

    stringstream ss;
    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    playGame(alice, bob);

    cout.rdbuf(oldCout);
    assert(ss.str().empty());
    assert(alice.contains(Card('c', "a")));
    assert(bob.contains(Card('d', "2")));

    cout << "playGame with no common cards test passed!" << endl;
}

void test_playGame_one_empty() {
    BST alice, bob;
    alice.insert(Card('c', "a"));

    stringstream ss;
    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    playGame(alice, bob);

    cout.rdbuf(oldCout);
    assert(ss.str().empty());
    assert(alice.contains(Card('c', "a")));
    assert(bob.isEmpty());

    cout << "playGame with one empty hand test passed!" << endl;
}

int main() {
    test_card_comparison();
    test_bst_insert();
    test_bst_remove();
    test_bst_contains();
    test_bst_printDeck();
    test_bst_getSuccessorNode();
    test_bst_getPredecessorNode();
    test_iterator_empty();
    test_iterator_single();
    test_iterator_multiple();
    test_iterator_increment_past_end();
    test_iterator_decrement_past_rend();
    test_iterator_comparison_ops();
    test_playGame_common();
    test_playGame_no_common();
    test_playGame_one_empty();

    cout << "All tests completed!" << endl;

    return 0;
}
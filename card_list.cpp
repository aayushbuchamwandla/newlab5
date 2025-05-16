#include "card_list.h"
#include <iostream>
using namespace std;

BST::~BST() {
    clear(root);
}

void BST::clear(Node* n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

void BST::insert(const Card& card) {
    if (root == nullptr) {
        root = new Node(card);
    } else {
        insert(root, card);
    }
}

void BST::insert(Node* n, const Card& card) {
    if (n->card < card) {
        if (n->right == nullptr) {
            n->right = new Node(card);
            n->right->parent = n;
        } else {
            insert(n->right, card);
        }
    } else if (n->card > card) {
        if (n->left == nullptr) {
            n->left = new Node(card);
            n->left->parent = n;
        } else {
            insert(n->left, card);
        }
    }
}

bool BST::contains(int rank) {
    return getNodeFor(rank, root) != nullptr;
}

BST::Node* BST::getNodeFor(int rank, Node* n) const {
    if (!n) return nullptr;
    if (n->card.getRank() > rank) return getNodeFor(rank, n->left);
    else if (n->card.getRank() < rank) return getNodeFor(rank, n->right);
    else return n;
}

bool BST::remove(int rank) {
    Node* n = getNodeFor(rank, root);
    if (n == nullptr) return false;

    if (n->left == nullptr && n->right == nullptr) {
        if (n == root) root = nullptr;
        else if (n->parent->left == n) n->parent->left = nullptr;
        else n->parent->right = nullptr;
        delete n;
    } else if (n->left == nullptr || n->right == nullptr) {
        Node* child = (n->left != nullptr) ? n->left : n->right;
        if (n == root) root = child;
        else if (n->parent->left == n) n->parent->left = child;
        else n->parent->right = child;
        child->parent = n->parent;
        delete n;
    } else {
        Node* successor = getSuccessorNode(rank);
        n->card = successor->card;
        remove(successor->card.getRank());
    }

    return true;
}

BST::Node* BST::getSuccessorNode(int rank) const {
    Node* n = getNodeFor(rank, root);
    if (n->right != nullptr) {
        n = n->right;
        while (n->left != nullptr) {
            n = n->left;
        }
    } else {
        Node* parent = n->parent;
        while (parent != nullptr && parent->right == n) {
            n = parent;
            parent = parent->parent;
        }
        n = parent;
    }
    return n;
}

BST::Node* BST::getMinNode() const {
    Node* n = root;
    while (n && n->left != nullptr) {
        n = n->left;
    }
    return n;
}

BST::Node* BST::getMaxNode() const {
    Node* n = root;
    while (n && n->right != nullptr) {
        n = n->right;
    }
    return n;
}

void BST::printDeck() const {
    printInOrder(root);
    cout << endl;
}

void BST::printInOrder(Node* n) const {
    if (n == nullptr) return;
    printInOrder(n->left);
    cout << n->card << endl;
    printInOrder(n->right);
}

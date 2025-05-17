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
    insert(root, card, nullptr);
}

void BST::insert(Node*& node, const Card& card, Node* parent) {
    if (!node) {
        node = new Node(card, parent);
    } else if (card < node->card) {
        insert(node->left, card, node);
    } else if (card > node->card) {
        insert(node->right, card, node);
    }
}

bool BST::contains(const Card& card) const {
    return getNodeFor(card, root) != nullptr;
}

BST::Node* BST::getNodeFor(const Card& card, Node* n) const {
    if (!n) return nullptr;
    if (n->card == card) return n;
    if (card < n->card) return getNodeFor(card, n->left);
    return getNodeFor(card, n->right);
}

bool BST::remove(const Card& card) {
    return remove(root, card);
}

bool BST::remove(Node*& node, const Card& card) {
    if (!node) return false;

    if (card < node->card) {
        return remove(node->left, card);
    } else if (card > node->card) {
        return remove(node->right, card);
    } else {
        // Node found
        if (!node->left && !node->right) {
            // No children
            delete node;
            node = nullptr;
        } else if (!node->left) {
            // Only right child
            Node* temp = node;
            node = node->right;
            if (node) node->parent = temp->parent;
            delete temp;
        } else if (!node->right) {
            // Only left child
            Node* temp = node;
            node = node->left;
            if (node) node->parent = temp->parent;
            delete temp;
        } else {
            // Two children
            Node* successor = getSuccessorNodeInternal(node);
            node->card = successor->card;
            remove(node->right, successor->card);
        }
        return true;
    }
}

BST::Node* BST::getSuccessorNodeInternal(Node* n) const {
    if (!n) return nullptr;
    if (n->right) return getMinNode(n->right);

    Node* parent = n->parent;
    while (parent && n == parent->right) {
        n = parent;
        parent = parent->parent;
    }
    return parent;
}

BST::Node* BST::getPredecessorNodeInternal(Node* n) const {
    if (!n) return nullptr;
    if (n->left) return getMaxNode(n->left);

    Node* parent = n->parent;
    while (parent && n == parent->left) {
        n = parent;
        parent = parent->parent;
    }
    return parent;
}

BST::Node* BST::getMinNode(Node* n) const {
    if (!n) return nullptr;
    while (n->left) n = n->left;
    return n;
}

BST::Node* BST::getMaxNode(Node* n) const {
    if (!n) return nullptr;
    while (n->right) n = n->right;
    return n;
}

void BST::printDeck() const {
    printInOrder(root);
    cout << endl;
}

void BST::printInOrder(Node* n) const {
    if (!n) return;
    printInOrder(n->left);
    cout << n->card << endl;
    printInOrder(n->right);
}

// Iterator Implementation
// BST::Iterator::Iterator(Node* ptr, const BST* bst) : current(ptr), tree(bst) {}

BST::Iterator& BST::Iterator::operator++() {
    if (current) {
        current = inorderSuccessor(current);
    }
    return *this;
}

BST::Iterator BST::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

BST::Iterator& BST::Iterator::operator--() {
    if (current) {
        current = reverseInorderSuccessor(current);
    }
    return *this;
}

BST::Iterator BST::Iterator::operator--(int) {
    Iterator temp = *this;
    --(*this);
    return temp;
}

BST::Node* BST::Iterator::inorderSuccessor(Node* node) const {
    if (!node) return nullptr;
    if (node->right) return tree->getMinNode(node->right);
    Node* parent = node->parent;
    while (parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

BST::Node* BST::Iterator::reverseInorderSuccessor(Node* node) const {
    if (!node) return nullptr;
    if (node->left) return tree->getMaxNode(node->left);
    Node* parent = node->parent;
    while (parent && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

BST::Iterator BST::begin() const {
    return Iterator(getMinNode(root), this);
}

BST::Iterator BST::end() const {
    return Iterator(nullptr, this);
}

BST::Iterator BST::rbegin() const {
    return Iterator(getMaxNode(root), this);
}

BST::Iterator BST::rend() const {
    return Iterator(nullptr, this);
}

// playGame function implementation
void playGame(BST& alice, BST& bob) {
    bool gameOver = false;

    while (!gameOver) {
        bool aliceMatch = false;
        for (BST::Iterator it = alice.begin(); it != alice.end(); ++it) {
            if (bob.contains(*it)) {
                cout << "Alice picked matching card " << *it << endl;
                bob.remove(*it);
                alice.remove(*it);
                aliceMatch = true;
                break;
            }
        }

        if (!aliceMatch) {
            gameOver = true;
            continue;
        }

        bool bobMatch = false;
        for (BST::Iterator it = bob.rbegin(); it != bob.rend(); --it) {
            if (alice.contains(*it)) {
                cout << "Bob picked matching card " << *it << endl;
                alice.remove(*it);
                bob.remove(*it);
                bobMatch = true;
                break;
            }
        }

        if (!bobMatch) {
            gameOver = true;
        }
    }
}
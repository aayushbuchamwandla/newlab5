#include "BST.h"
#include <iostream>
#include <string>

// Private helper methods for BST
void BST::insert(Node*& node, const Card& card) {
    if (node == nullptr) {
        node = new Node(card);
    } else if (card.getRank() < node->card.getRank()) {
        insert(node->left, card);
    } else if (card.getRank() > node->card.getRank()) {
        insert(node->right, card);
    }
}

bool BST::contains(Node* node, const std::string& rank) const {
    if (node == nullptr) return false;
    if (node->card.getRank() == rank) return true;
    if (rank < node->card.getRank()) return contains(node->left, rank);
    return contains(node->right, rank);
}

void BST::remove(Node*& node, const std::string& rank) {
    if (node == nullptr) return;

    if (rank < node->card.getRank()) {
        remove(node->left, rank);
    } else if (rank > node->card.getRank()) {
        remove(node->right, rank);
    } else {
        // Node found, perform deletion
        if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            // Node has two children: find the inorder successor
            Node* temp = node->right;
            while (temp && temp->left) {
                temp = temp->left;
            }
            node->card = temp->card;
            remove(node->right, temp->card.getRank());
        }
    }
}

void BST::inorder(Node* node) const {
    if (node != nullptr) {
        inorder(node->left);
        std::cout << node->card << std::endl;
        inorder(node->right);
    }
}

// Public methods for BST
void BST::insert(const Card& card) {
    insert(root, card);
}

bool BST::contains(const std::string& rank) const {
    return contains(root, rank);
}

void BST::remove(const std::string& rank) {
    remove(root, rank);
}

void BST::printInOrder() const {
    inorder(root);
}

BST::~BST() {
    // Destructor code to delete all nodes in the tree (optional)
}

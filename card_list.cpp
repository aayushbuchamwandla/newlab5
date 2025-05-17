#include "card_list.h"
#include <iostream>
#include <functional>


using namespace std;


BST::~BST() {
   // Delete all nodes - post order traversal
   std::function<void(Node*)> deleteAll = [&](Node* node) {
       if (!node) return;
       deleteAll(node->left);
       deleteAll(node->right);
       delete node;
   };
   deleteAll(root);
   root = nullptr;
}


BST::Node* BST::insert(Node* node, const Card& card) {
   if (!node) return new Node(card);


   if (card.getRank() < node->data.getRank())
       node->left = insert(node->left, card);
   else if (card.getRank() > node->data.getRank())
       node->right = insert(node->right, card);
   else {
       // duplicate rank, do nothing (no duplicates)
   }
   return node;
}


void BST::insert(const Card& card) {
   root = insert(root, card);
}


BST::Node* BST::findMin(Node* node) const {
   while (node && node->left)
       node = node->left;
   return node;
}


BST::Node* BST::findMax(Node* node) const {
   while (node && node->right)
       node = node->right;
   return node;
}


BST::Node* BST::remove(Node* node, int rank, bool& removed) {
   if (!node) return nullptr;
   if (rank < node->data.getRank()) {
       node->left = remove(node->left, rank, removed);
   } else if (rank > node->data.getRank()) {
       node->right = remove(node->right, rank, removed);
   } else {
       // Found node to remove
       removed = true;
       if (!node->left) {
           Node* rightNode = node->right;
           delete node;
           return rightNode;
       } else if (!node->right) {
           Node* leftNode = node->left;
           delete node;
           return leftNode;
       } else {
           // two children: replace with min in right subtree
           Node* minRight = findMin(node->right);
           node->data = minRight->data;
           node->right = remove(node->right, minRight->data.getRank(), removed);
       }
   }
   return node;
}


bool BST::remove(int rank) {
   bool removed = false;
   root = remove(root, rank, removed);
   return removed;
}


bool BST::contains(Node* node, int rank) const {
   if (!node) return false;
   if (rank < node->data.getRank()) return contains(node->left, rank);
   else if (rank > node->data.getRank()) return contains(node->right, rank);
   else return true;
}


bool BST::contains(int rank) const {
   return contains(root, rank);
}


void BST::printDeck(Node* node) const {
   if (!node) return;
   printDeck(node->left);
   cout << node->data << " ";
   printDeck(node->right);
}


void BST::printDeck() const {
   printDeck(root);
   cout << endl;
}


int BST::count(Node* node) const {
   if (!node) return 0;
   return 1 + count(node->left) + count(node->right);
}


int BST::count() const {
   return count(root);
}


// BST Iterator Implementation


void BST::Iterator::pushLeft(Node* node) {
   while (node) {
       stack.push(node);
       node = node->left;
   }
}


BST::Iterator::Iterator(Node* root) {
   pushLeft(root);
}


BST::Iterator& BST::Iterator::operator++() {
   if (stack.empty()) return *this;


   Node* node = stack.top();
   stack.pop();


   if (node->right)
       pushLeft(node->right);


   return *this;
}


bool BST::Iterator::operator!=(const Iterator& other) const {
   if (stack.empty() && other.stack.empty())
       return false;
   if (stack.empty() || other.stack.empty())
       return true;
   return stack.top() != other.stack.top();
}


const Card& BST::Iterator::operator*() const {
   return stack.top()->data;
}


BST::Iterator BST::begin() const {
   return Iterator(root);
}


BST::Iterator BST::end() const {
   return Iterator(nullptr);
}


// BST Reverse Iterator Implementation


void BST::ReverseIterator::pushRight(Node* node) {
   while (node) {
       stack.push(node);
       node = node->right;
   }
}


BST::ReverseIterator::ReverseIterator(Node* root) {
   pushRight(root);
}


BST::ReverseIterator& BST::ReverseIterator::operator--() {
   if (stack.empty()) return *this;


   Node* node = stack.top();
   stack.pop();


   if (node->left)
       pushRight(node->left);


   return *this;
}


bool BST::ReverseIterator::operator!=(const ReverseIterator& other) const {
   if (stack.empty() && other.stack.empty())
       return false;
   if (stack.empty() || other.stack.empty())
       return true;
   return stack.top() != other.stack.top();
}


const Card& BST::ReverseIterator::operator*() const {
   return stack.top()->data;
}


BST::ReverseIterator BST::rbegin() const {
   return ReverseIterator(root);
}


BST::ReverseIterator BST::rend() const {
   return ReverseIterator(nullptr);
}

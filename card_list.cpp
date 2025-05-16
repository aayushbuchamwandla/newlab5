#include "card_list.h"


#include <iostream>
using std::cout;


//         void insert(Node *node, const Card& card);
//         void printInOrder(Node *node);
//         Node* getNodeFor(int rank, Node *n);
//         Node *getSuccessorNode(int rank);
//         Node *getPredecessorNode(int rank);
//         void clear(Node *n);


// constructor sets up empty tree
BST::BST() {
   root = nullptr;
}


// destructor deletes all nodes
BST::~BST() {
   clear(root);
}


// recursive helper for destructor
void BST::clear(Node *n) {
   if (!n) return;
   clear(n->left);
   clear(n->right);
   delete n;
}


// insert value in tree; return false if duplicate
void BST::insert(const Card& card) {
   if (root == nullptr) {
       Node *created = new Node(card);
       root = created;
   }
   else {
       insert(root, card);
   }
}


// recursive helper for insert (assumes n is never 0)
void BST::insert(Node *n, const Card& card) {
   if (n->card>card) {
       if (n->left == nullptr) {
           Node *created = new Node(card);
           n->left = created;
           created->parent = n;
       }
       else {
           return insert(n->left, card);
       }
   }
   else if (n->card<card) {
       if (n->right == nullptr) {
           Node *created = new Node(card);
           n->right = created;
           created->parent = n;
       }
       else {
           return insert(n->right, card);
       }
   }
   else {
       return;
   }
}


// print tree data in-order, with helper
void BST::printDeck() const {
   for (Iterator i = begin(); i != end(); ++i) {
       cout<<*i<<" ";
   }
}


void BST::printInOrder(Node *n) const {
   if (!n) return;
   printInOrder(n->left);
   cout<<n->card<<" ";
   printInOrder(n->right);
}


// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
BST::Node* BST::getNodeFor(int rank, Node* n) const {
   if (!n) return nullptr;
   if (n->card.getRank()>rank) {
       return getNodeFor(rank,n->left);
   }
   else if (n->card.getRank()<rank) {
       return getNodeFor(rank,n->right);
   }
   else {
       return n;
   }
}


// returns the Node containing the predecessor of the given value
BST::Node* BST::getPredecessorNode(int rank) const {
   Node *hold = getNodeFor(rank,root);
   if (hold->left!=nullptr) {
       Node *temp = hold->left;
       while (temp->right != nullptr) {
           temp = temp->right;
       }
       return temp;
   }
   else {
       Node *temp = hold;
       while (temp->parent != nullptr && temp->parent->left == temp) {
           temp = temp->parent;
       }
       return temp->parent;
   }
}


// returns the predecessor value of the given value or 0 if there is none
int BST::getPredecessor(int rank) {
   Node *hold = getPredecessorNode(rank);
   if (hold==nullptr) {
       return 0;
   }
   return hold->card.getRank();
}


// returns the Node containing the successor of the given value
BST::Node* BST::getSuccessorNode(int rank) const{
   Node *hold = getNodeFor(rank, root);


   if (hold==nullptr) {
       return nullptr;
   }


   if (hold->right != nullptr) {
       Node *temp = hold->right;
       while (temp->left != nullptr) {
           temp = temp->left;
       }
       return temp;
   }
   Node *temp = hold;
   while (temp->parent!=nullptr && temp->parent->right == temp) {
       temp = temp->parent;
   }
   return temp->parent;
}


// returns the successor value of the given value or 0 if there is none
int BST::getSuccessor(int rank) {
   Node *hold = getSuccessorNode(rank);
   if (hold==nullptr) {
       return 0;
   }
   return hold->card.getRank();
}


// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool BST::remove(int rank){
   Node *hold = getNodeFor(rank,root);
   if (hold==nullptr) {
       return false;
   }


   if (hold->left == nullptr && hold->right == nullptr) {
       if (hold == root) {
           root = nullptr;
       }
       else {
           if (hold->parent->left == hold) {
               hold->parent->left = nullptr;
           }
           else {
               hold->parent->right = nullptr;
           }
       }
       delete hold;
       return true;
   }
   else if ((hold->left == nullptr && hold->right != nullptr) || (hold->left != nullptr && hold->right == nullptr)) {
       if (hold==root) {
           if (hold->right != nullptr) {
               root = hold->right;
               root->parent = nullptr;
           }
           else {
               root = hold->left;
               root->parent = nullptr;
           }
       }
       else {
           if (hold->parent != nullptr) {
               if (hold->parent->left == hold) {
                   if (hold->left != nullptr) {
                       hold->parent->left = hold->left;
                       hold->left->parent = hold->parent;
                   }
                   else {
                       hold->parent->left = hold->right;
                       hold->right->parent = hold->parent;
                   }
               }
               else {
                   if (hold->right != nullptr) {
                       hold->parent->right = hold->right;
                       hold->right->parent = hold->parent;
                   }
                   else {
                       hold->parent->right = hold->left;
                       hold->left->parent = hold->parent;
                   }
               }
           }
       }
       delete hold;
       return true;
   }
   else {
       Node *successor = getSuccessorNode(rank);
       hold->card = successor->card;
       Node *newOne = successor->right;


       if (successor->parent->left == successor) {
           successor->parent->left = newOne;
       }
       else {
           successor->parent->right = newOne;
       }
       if (newOne != nullptr) {
           newOne->parent = successor->parent;
       }
       delete successor;
       return true;
   }


   return false;
}


bool BST::contains(int rank) const {
   return getNodeFor(rank, root) != nullptr;
}



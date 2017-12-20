#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "Node.h"


class BinarySearchTree
{
    public:
        BinarySearchTree();
        BinarySearchTree(Node*);
        BinarySearchTree(BinarySearchTree*);
        ~BinarySearchTree();

        void setRoot(Node* r) {root = r;};
        Node* getRoot() {return root;};

        void insertNode(Node*, Node*);
        bool searchTree(Node*, Node*);
        void copyTree(Node*, Node*);
        void deleteTree(Node*);
        void printTree(ostream&, Node*);
        int getSize(Node*);

    protected:

    private:
        Node *root;
};

#endif // BINARYSEARCHTREE_H

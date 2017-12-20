#include "BinarySearchTree.h"

//default constructor that sets root to nullptr.
BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}

//overloaded constructor that takes in a Node pointer and assigns root to point to it.
BinarySearchTree::BinarySearchTree(Node* otherRoot)
{
    root = otherRoot;
}

//copy constructor that calls copy tree to recursively copy the tree.
BinarySearchTree::BinarySearchTree(BinarySearchTree* otherTree)
{
    copyTree(this->root, otherTree->getRoot());
}

//destructor that calls deleteTree to recursively delete the tree.
BinarySearchTree::~BinarySearchTree()
{
    deleteTree(root);
}

//insertion that sets root equal to the node if the root is nullptr.  If not then it recursively goes down the left side of
//the tree if the exponent is smaller or the right side if the exponent is bigger.  If the exponents are the same the coefficients
//are added together.  If left or right is null then it sets the current left or right to the node passed in.
void BinarySearchTree::insertNode(Node *node, Node *current)
{
    if(!root)
        root = node;
    else
    {
        while(current)
        {
            if(current->getExponent() == node->getExponent())
            {
                current->setNumerator(current->getNumerator() + node->getNumerator());
                return;
            }else if(current->getExponent() < node->getExponent())
            {
                if(current->left) {
                    insertNode(node, current->left);
                    return; }
                else {
                    current->left = node;
                    return; }
            }
            else if(current->getExponent() > node->getExponent())
            {
                if(current->right) {
                    insertNode(node, current->right);
                    return; }
                else {
                    current->right = node;
                    return; }
            }
        }
    }
}

bool BinarySearchTree::searchTree(Node *current, Node *item)
{
    if(root)
    {
        if(current->getExponent() == item->getExponent() && current->getNumerator() == item->getNumerator() && current->getDenom() == item->getDenom())
            return true;
        if(item->getExponent() < current->getExponent())
            searchTree(current->left, item);
        if(item->getExponent() > current->getExponent())
            searchTree(current->right, item);
    }
    return false;
}

//recursively copies tree, if root is null it sets other tree to null.  If not then it creates a new node and uses the copy
//constructor the node class and then puts that node into the tree.
void BinarySearchTree::copyTree(Node* copiedTreeRoot, Node* otherTreeRoot)
{
    if(!otherTreeRoot)
        copiedTreeRoot = nullptr;
    else
    {
        copiedTreeRoot = new Node(*otherTreeRoot);
        copyTree(copiedTreeRoot->left, otherTreeRoot->left);
        copyTree(copiedTreeRoot->right, otherTreeRoot->right);
    }
}

//recursively deletes the tree by going through postorder traversal and deleting the leaves.
void BinarySearchTree::deleteTree(Node* treeRoot)
{
    if(!treeRoot)
    {
        deleteTree(treeRoot->left);
        deleteTree(treeRoot->right);
        delete treeRoot;
        treeRoot = nullptr;
    }
}

//overloaded operator that outputs the tree with in order traversal
void BinarySearchTree::printTree(ostream& outFile, Node *treeRoot)
{
    static int i = 0;
    if(treeRoot)
    {
        printTree(outFile, treeRoot->left);
        i++;
        if(treeRoot->getCoefficient() != 1 && treeRoot->getCoefficient() != -1 && treeRoot->getExponent() != 0 && treeRoot->getExponent() != 1)
        {
            if(treeRoot->getDenom() != 1)
                outFile << "(" << treeRoot->getNumerator() << "/" << treeRoot->getDenom() << ")" <<  "x^" << treeRoot->getExponent();
            else
                outFile << treeRoot->getNumerator() << "x^" << treeRoot->getExponent();
        }
        else if(treeRoot->getCoefficient() != 1 && treeRoot->getExponent() != 0 && treeRoot->getExponent() == 1)
        {
            if(treeRoot->getDenom() != 1)
                outFile << "(" << treeRoot->getNumerator() << "/" << treeRoot->getDenom() << ")" << "x";
            else
                outFile << treeRoot->getNumerator() << "x";
        }
        else if(treeRoot->getCoefficient() == 1 && treeRoot->getExponent() != 0 && treeRoot->getExponent() != 1)
            outFile << "x^" << treeRoot->getExponent();
        else if(treeRoot->getCoefficient() == 1 && treeRoot->getExponent() == 1)
            outFile << "x";
        else if(treeRoot->getCoefficient() == -1 && treeRoot->getExponent() != 0)
            outFile << "-x^" << treeRoot->getExponent();
        else if(treeRoot->getCoefficient() != 0 && treeRoot->getExponent() == 0)
            outFile << treeRoot->getNumerator() << "/" << treeRoot->getDenom();
        if(i != getSize(root))
            outFile << " + ";
        printTree(outFile, treeRoot->right);
    }
    if(i == getSize(root))
        i = 0;
}

//recursively goes through the tree and counts the number of nodes in the tree
int BinarySearchTree::getSize(Node *current)
{
    if(!current)
        return 0;
    else
        return (getSize(current->left) + getSize(current->right) + 1);
}

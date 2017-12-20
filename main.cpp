/*Project 4 - Binary Search Tree
Sam Speece - sds160130
CS 2336.004
October 30, 2016*/

#include "Node.h"
#include "BinarySearchTree.h"
#include <sstream>
#include <stdlib.h>
#include <cmath>

using namespace std;

void getIntegrals(string, BinarySearchTree*);
string fixString(string);
void integrateTree(Node*);
double findDefiniteIntegral(Node*, double, double, int);
void simplifyFraction(Node*);

int main()
{
    //open files and instantiate objects
    ifstream inFile("integrals4.txt");
    ofstream outFile("answers.txt");
    string integral, line;
    BinarySearchTree *tree;

    if(inFile.is_open())
    {
        while(!inFile.eof())
        {
            tree = new BinarySearchTree;
            inFile >> integral;
            getline(inFile, line);
            line = fixString(line);
            getIntegrals(line, tree);
            integrateTree(tree->getRoot());
            if(integral.size() == 1)
            {
                tree->printTree(outFile, tree->getRoot());
                outFile << " + C\n";
            }
            else if(integral.size() > 1)
            {
                int i = 0;
                while(integral[i] != '|')
                    i++;

                tree->printTree(outFile, tree->getRoot());
                outFile << fixed << showpoint << setprecision(3);
                outFile << ", " << integral << " = " << findDefiniteIntegral(tree->getRoot(), atof(integral.substr(0, i).c_str()), atof(integral.substr(i + 1).c_str()), tree->getSize(tree->getRoot())) << "\n";
            }
        }
    }

    inFile.close();
    outFile.close();

    delete tree;

    return 0;
}

//takes in the line from the file (not including the integral) and then separates out all the terms out to be only one space
//between all terms and condenses terms together.
string fixString(string line)
{
    unsigned int lineSize = line.size();
    string temp;
    unsigned int i = 0;
    while(i != lineSize)
    {
        if(isspace(line[i]))
            line = line.substr(0, i) + line.substr(i + 1);
        if(line[i] == '+')
            line[i] = ' ';
        if(line[i] == '-' && line[i - 1] != '^')
        {
            temp = line.substr(0, i) + " -" + fixString(line.substr(i + 1));
        }
        if(line[i] == 'd' && line[i + 1] == 'x')
        {
            line = line.substr(0, i);
            if(temp != "")
                line = temp;
            return line;
        }
        i++;
    }

    return line;
}

//assumes that fixString separated out and condensed terms.  Uses a string stream of the fixed line and takes number before x
//as coefficient and number after ^ as exponent.  If there is no x coefficient is whole term and exponent is assumed to 0.  Then
//creates node and inserts into BinarySearchTree object.
void getIntegrals(string line, BinarySearchTree *tree)
{
    int numerator, denom, exponent;
    unsigned int i = 0;
    string term;
    stringstream ss(line);

    while(getline(ss, term, ' '))
    {
        while(term[i] != 'x' && i < term.size())
            i++;

        if(i == 0)
        {
            numerator = 1;
            denom = 1;
            if(term[i + 1] == '^')
                exponent = atoi(term.substr(i + 2).c_str());
            else
                exponent = 1;
        }else if(i == term.size())
        {
            numerator = atoi(term.c_str());
            denom = 1;
            exponent = 0;
        }else if(i > 0 && i < term.size())
        {
            numerator = atoi(term.substr(0, i).c_str());
            denom = 1;
            if(term[i + 1] == '^')
                exponent = atoi(term.substr(i + 2).c_str());
            else
                exponent = 1;
        }

        if(numerator != 0)
        {
            Node *node = new Node(exponent, numerator, denom);
            tree->insertNode(node, tree->getRoot());
        }
    }
}

//recursively goes through the tree and integrates each individual node and simplifies the fraction
void integrateTree(Node *root)
{
    if(root)
    {
        root->setExponent(root->getExponent() + 1);
        root->setDenom(root->getDenom() * root->getExponent());
        simplifyFraction(root);
        integrateTree(root->left);
        integrateTree(root->right);
    }
}

//recursively goes through the tree and keeps a count of the first area and second area, then once recursion is over it returns the
//calculated area and resets area1 and area2
double findDefiniteIntegral(Node *root, double a, double b, int treeSize)
{
    static double area1 = 0, area2 = 0, i = 0, area = 0;

    if(root)
    {
        area1 += ((root->getNumerator()*1.0)/(root->getDenom()*1.0)) * pow(b, (root->getExponent()*1.0));
        area2 += ((root->getNumerator()*1.0)/(root->getDenom()*1.0)) * pow(a, (root->getExponent()*1.0));
        i++;
        findDefiniteIntegral(root->left, a, b, treeSize);
        findDefiniteIntegral(root->right, a, b, treeSize);
    }
    if(i == treeSize)
    {
        area = area1 - area2;
        area1 = 0;
        area2 = 0;
        i = 0;
    }
    return area;
}

//simple modulus simplification algorithm that finds reminder while not 0 and reduces the fraction
void simplifyFraction(Node* node)
{
    int a = node->getNumerator(), b = node->getDenom();

    while(b != 0)
    {
       int r = a % b;
       a = b;
       b = r;
    }

    node->setNumerator(node->getNumerator()/a);
    node->setDenom(node->getDenom()/a);
}

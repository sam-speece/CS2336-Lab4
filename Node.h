#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Node
{
    public:
        Node();
        Node(int, int, int);
        Node(Node&);
        ~Node();

        void setExponent(int e) {exponent = e;};
        int getExponent() {return exponent;};
        double getCoefficient() {return (numerator*1.0)/(denom*1.0);};
        void setNumerator(int n) {numerator = n;};
        int getNumerator() {return numerator;};
        void setDenom(int d) {denom = d;};
        int getDenom() {return denom;};

        Node *left;
        Node *right;

    protected:

    private:
        int exponent, numerator, denom;
};

#endif // NODE_H

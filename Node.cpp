#include "Node.h"

//default constructor
Node::Node()
{
    exponent = 0;
    numerator = 0;
    denom = 0;
    left = nullptr;
    right = nullptr;
}

//overloaded constructor
Node::Node(int exp, int n, int d)
{
    exponent = exp;
    numerator = n;
    denom = d;
    left = nullptr;
    right = nullptr;
}

//copy constructor
Node::Node(Node& node)
{
    exponent = node.getExponent();
    numerator = node.getNumerator();
    denom = node.getDenom();
}

//destructor
Node::~Node()
{
    left = nullptr;
    right = nullptr;
}

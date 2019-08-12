#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <stdexcept>
#include <string>

using std::string;
using std::pair;
using std::make_pair;
using std::cout;
using std::cerr;
using std::endl;
using std::logic_error;
using std::cin;
using std::runtime_error;

template <typename T, typename G>
class Node
{
public:
    inline Node(const T& key, const G& item, Node* parent=NULL): _parent(parent), _left
            (NULL), _right(NULL){};

    inline Node* getLeftChild () const {return _left;}

    inline Node* getRightChild () const {return _right;}

    inline const T& getKey() const {return _key;}

    inline const G& getItem() const {return _item;}

    inline void setLeft(Node* node) {_left=node;}

    inline void setRight(Node* node) {_right=node;}


private:
    Node* _parent;
    Node* _left;
    Node* _right;
    const T _key;
    G _item;
};

#endif
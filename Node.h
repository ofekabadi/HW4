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


//Template class Node: creates an object within the binary tree, the node has a key which
// defines it's order in the tree and stores a value.
template <typename T, typename G>
class Node
{
public:

    //constructor
    inline Node(const T& key, const G& item, Node* parent=NULL): _key(key), _item(item),
    _parent (parent), _left(NULL), _right(NULL){};

    //returns pointer to node's left child
    inline Node* getLeftChild () const {return _left;}

    //returns pointer to node's right child
    inline Node* getRightChild () const {return _right;}

    //returns pointer to node's parent
    inline Node* getParent () const {return _parent;}

    //returns node's key
    inline const T& getKey() const {return _key;}

    //returns node's item
    inline const G& getItem() const {return _item;}

    //sets left child's node
    inline void setLeft(Node* node) {_left=node;}

    //sets right child's node
    inline void setRight(Node* node) {_right=node;}

    //Destructor
    ~Node(){}



private:
    Node* _parent;
    Node* _left;
    Node* _right;
    const T _key;
    G _item;
};

#endif
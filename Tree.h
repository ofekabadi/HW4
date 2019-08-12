#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include "Node.h"

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
class Tree{
public:
    inline Tree(): _size(0) {}

    bool isEmpty() const;

    size_t size() const;

    Node<T,G>* search (const T& key) const;

    void insert(const T& key,const G& item);

    void deleteLeaf(const T& key);

    void inOrderTraversal() const;

private:
    Node<T,G>*_root;

    size_t _size;


    Node<T,G>* _searcher (Node<T,G>* currNode, const T& key) const;

    void _traverser(Node<T,G>* currNode) const;

    void _inserter(const T& key,const G& item);

    };

#endif
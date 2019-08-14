#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include "Node.h"
#include "Tree.cpp"


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
    inline Tree(): _size(0), _root(NULL){}

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

    inline void _error(const string& err){throw runtime_error(err);}

};





template <typename T, typename G>
void Tree<T,G>::insert(const T& key, const G& item){
    try
    {
        if(_searcher(_root, key)!=NULL)       //if key already exists
        {
            _error("Key not unique");
        }
        if(_root==NULL)         //if tree is empty
        {
            _root= new Node<T,G>(key, item, NULL); //needs to be deleted
            return;
        }
        else
        {
            _inserter(key, item);
        }
        return;
    }

    catch (runtime_error &error)
    {
        cerr << error.what() << endl;
        cout<<"Key not unique"<<endl;            //literals
        return;
    }
}

template <typename T, typename G>
void Tree<T,G>::_inserter(const T& key, const G& item){
    Node<T,G>* y =_root;
    Node<T,G>* x =NULL;
    while (y!=NULL)
    {
        x=y;
        {
            if(key < y->getKey())
            {
                y = y->getLeftChild();
            }
            else if(key > y->getKey())
            {
                y = y->getRightChild();
            }
        }
    }

    Node<T,G>* newNode = new Node<T,G>(key, item, x);
    if (key<x->getKey())
    {
        x->setLeft(newNode);
    }
    else
    {
        x->setRight(newNode);
    }

    return;
}



template <typename T, typename G>
Node<T,G>* Tree<T,G>::search (const T& key) const{
    try {
        Node<T,G>* result = _searcher(_root, key);
        if(result==NULL)
        {
            cout<<"NULL"<<endl;
        }
        cout<<"found: "<<result->getItem()<<endl;   //literals
        return result;
    }
    catch(runtime_error &error)
    {
        cerr << error.what() << endl;
        cout<<"Key was not found"<<endl;    //literals
        return;
    }
}



template <typename T, typename G>
Node<T,G>* Tree<T,G>::_searcher (Node<T,G>* currNode, const T& key) const{
    if(currNode==NULL)
    {
        return NULL;
    }
    if(currNode->getKey()==key)
    {
        return currNode;
    }
    else if(currNode->getLeftChild()!=NULL)
    {
        _searcher(currNode->getLeftChild(), key);
    }
    else if(currNode->getRightChild()!=NULL)
    {
        _searcher(currNode->getRightChild(), key);
    }
    return NULL;
}



template <typename T, typename G>
void Tree<T,G>::inOrderTraversal() const{
    cout<<"Binary search tree content:"<<endl;      //literals
    if (_root==NULL)
    {
        return;
    }
    _traverser(_root);
    return;
}


template <typename T, typename G>
void Tree<T,G>::_traverser(Node<T,G>* currNode) const{
    if (currNode->getLeftChild()!=NULL)  //might be a code duplication...
    {
        _traverser(currNode->getLeftChild());
    }
    cout<<"Key: "<<currNode->getKey()<<" data: "<<currNode->getItem()<<endl;  //literals
    if (currNode->getRightChild()!=NULL)
    {
        _traverser(currNode->getRightChild());
    }
    return;
}



#endif
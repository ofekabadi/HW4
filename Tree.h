#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
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
using std::vector;



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

    void quit();

private:
    Node<T,G>*_root;

    size_t _size;



    Node<T,G>* _searcher (Node<T,G>* currNode, const T& key) const;

    void _inserter(const T& key,const G& item);

    void _deleter(Node<T,G>* targetedLeaf, const T& key);

    void _traverser(Node<T,G>* currNode) const;

    void _quitter(Node<T,G>* currNode);

    inline void _error(const string& err){throw (runtime_error(err));}

};



template <typename T, typename G>
size_t Tree<T,G>::size() const{
    cout<<"Tree size: "<<_size<<endl;       //LITERALS
    return _size;
}

template <typename T, typename G>
bool Tree<T,G>::isEmpty() const {
    if(_size)
    {
        cout<<"The tree is not empty"<<endl;  //LITERALS
        return false;
    }
    else
    {
        cout<<"The tree is empty"<<endl;        //LITERALS
        return true;
    }
}



template <typename T, typename G>
void Tree<T,G>::insert(const T& key, const G& item){
    try
    {
        if(_root==NULL)         //if tree is empty
        {
            _root = new Node<T,G>(key, item, NULL) ;
            _size++;
            return;
        }
        if(_searcher(_root, key)!=NULL)       //if key already exists
        {
            _error("Key not unique");       //LITERALS
        }

        else
        {
            _inserter(key, item);
            _size++;
        }
        return;
    }

    catch (runtime_error &error)
    {
        cerr << error.what() << endl;
        return;
    }
}

template <typename T, typename G>
void Tree<T,G>::_inserter(const T& key, const G& item){
    Node<T,G>* y =_root;             //NEEDS INFORMATIVE NAMES FOR  x, y
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
}



template <typename T, typename G>
Node<T,G>* Tree<T,G>::search (const T& key) const{
    try {
        Node<T,G>* result = _searcher(_root, key);
        if(result==NULL)
        {
            throw (runtime_error ("Key was not found"));   //LITERALS
           // _error("Key was not found");  NOT WORKING
        }
        cout<<"found: "<<result->getItem()<<endl;   //LITERALS
        return result;
    }
    catch(runtime_error &error)
    {
        cerr << error.what() << endl;
        return NULL;
    }
}



template <typename T, typename G>
Node<T,G>* Tree<T,G>::_searcher (Node<T,G>* currNode, const T& key) const{

    if(currNode->getKey()==key)
    {
        return currNode;
    }
    else if(key < currNode->getKey() && currNode->getLeftChild()!=NULL)
    {
        _searcher(currNode->getLeftChild(), key);
    }
    else if(key > currNode->getKey() && currNode->getRightChild()!=NULL)
    {
        _searcher(currNode->getRightChild(), key);
    }
}



template <typename T, typename G>
void Tree<T,G>::inOrderTraversal() const{
    cout<<"Binary search tree content:"<<endl;      //LITERALS
    if (_root==NULL)
    {
        return;
    }
    _traverser(_root);
    return;
}


template <typename T, typename G>
void Tree<T,G>::_traverser(Node<T,G>* currNode) const{
    if (currNode->getLeftChild()!=NULL)
    {
        _traverser(currNode->getLeftChild());
    }
    cout<<"Key: "<<currNode->getKey()<<" data: "<<currNode->getItem()<<endl;  //LITERALS
    if (currNode->getRightChild()!=NULL)
    {
        _traverser(currNode->getRightChild());
    }
    return;
}


template <typename T, typename G>
void Tree<T,G>::deleteLeaf(const T& key)//IT'S WORKING, BUT THERE IS A PROBLEM
// WITH DELETING THE TREE ALL THE WAY UP TO THE _ROOT, SINCE THE ROOT IS NOT DELETABLE
//  OR REASSIGNABLE (TO NULL)... MAYBE WE DON'T REALLY NEED TO DELETE IT. IF YOU CANT
//  FIND A SOLUTION I'LL ASK ADAM ABOUT IT.

{
    try
    {
        Node<T,G>* result = _searcher(_root,key);
        if(result==NULL)
        {
            throw (runtime_error ("Key was not found"));   //LITERALS
        }
        else if((result->getLeftChild() != NULL) || (result->getRightChild() != NULL))
        {
            throw (runtime_error ("The node is not a leaf!"));   //LITERALS
        }

        else if ( (result != NULL) && (result->getLeftChild() == NULL) &&
        (result->getRightChild() == NULL))
        {
            _deleter(result, key);
        }
    }

    catch (runtime_error &error)
    {
        cerr << error.what() << endl;
        return;
    }
}



template <typename T, typename G>
void Tree<T,G>::_deleter(Node<T,G>* targetedLeaf, const T& key){
    if (key < targetedLeaf->getParent()->getKey())
    {
        (targetedLeaf->getParent()) ->setLeft(NULL);
    }
    else
    {
        (targetedLeaf->getParent()) ->setRight(NULL);
    }
    delete targetedLeaf;
}


template <typename T, typename G>
void Tree<T,G>::quit(){
    if (_root==NULL)
    {
        return;
    }

    else
    {
        _quitter(_root);
        delete _root;
    }
}

template <typename T, typename G>
void Tree<T,G>::_quitter(Node<T, G> *currNode){
    if(currNode->getLeftChild()!=NULL)
    {
        _quitter(currNode->getLeftChild());
        delete(currNode->getLeftChild());
    }
    if(currNode->getRightChild()!=NULL)
    {
        _quitter(currNode->getRightChild());
        delete(currNode->getRightChild());
    }
}

#endif
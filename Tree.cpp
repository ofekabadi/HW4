#include <iostream>
#include <stdexcept>
#include <string>
#include "Tree.h"
#include "Node.h"

template <typename T, typename G>
bool Tree<T,G>::isEmpty() const {
    if(_size)
    {
        cout<<"The tree is not empty"<<endl;  //literals
        return false;
    }
    else
    {
        cout<<"The tree is empty"<<endl;        //literals
        return true;
    }
}


template <typename T, typename G>
size_t Tree<T,G>::size() const{
    cout<<"Tree size: "<<_size<<endl;       //literals
    return _size;
}


template <typename T, typename G>
Node<T,G>* Tree<T,G>::search (const T& key) const{
    try {
        Node<T,G>* result = _searcher(_root, &key);
        if(result==NULL)
        {
            throw           //missing
        }
        cout<<"found: "<<result->getItem()<<endl;   //literals
        return result;
    }
    catch(){                //missing
        cout<<"Key was not found"<<endl;    //literals
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
        _searcher(currNode->getLeftChild(), &key);
    }
    else if(currNode->getRightChild()!=NULL)
    {
        _searcher(currNode->getRightChild(), &key);
    }
    return NULL;
}


template <typename T, typename G>
void Tree<T,G>::insert(const T& key,const G& item){
    try
    {
        if(_searcher(_root, &key)!=NULL)
        {
            throw (1);
        }
        if(_root==NULL)
        {
            _root= new Node<T,G>(&key, &item, NULL); //needs to be deleted
        }
        else
        {
            _inserter(&key, &item);
        }
        return;
    }

    catch (1)
    {
        cout<<"Key not unique"<<endl;            //literals
        return;
    }
}


template <typename T, typename G>
void Tree<T,G>::inserter(const T& key,const G& item){
    Node<T,G>* y =_root, x=NULL;
    while (y!=NULL)
    {
        x=y;
        {
            if(key<y->getKey())
            {
                y=y->getLeftChild();
            }
            else if(key>y->getKey())
            {
                y=y->getRightChild();
            }
        }
    }

    Node<T,G>* newNode = new Node<T,G>(&key, &item, x);
    if (key<x.getKey())
    {
        x.setLeft(newNode);
    }
    else
    {
        x.setRight(newNode);
    }

    return;
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
    cout<<"Key:"<<currNode->getKey()<<" data: "<<currNode->getItem()<<endl;  //literals
    if (currNode->getLeftChild()!=NULL)  //might be a code duplication...
    {
        _traverser(currNode->getLeftChild());
    }
    if (currNode->getRightChild()!=NULL)
    {
        _traverser(currNode->getRightChild());
    }
    return;
}
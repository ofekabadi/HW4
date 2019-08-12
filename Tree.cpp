#include <iostream>
#include <stdexcept>
#include <string>
#include "Tree.h"
#include "Node.h"

template <typename T, typename G>
bool Tree<T,G>::isEmpty() const {
    if(_size)
    {
        cout<<"The tree is not empty"<<endl;
        return false;
    }
    else
    {
        cout<<"The tree is empty"<<endl;
        return true;
    }
}


template <typename T, typename G>
size_t Tree<T,G>::size() const{
    cout<<"Tree size: "<<_size<<endl;
    return _size;
}


template <typename T, typename G>
Node<T,G>* Tree<T,G>::search (const T& key) const{
    try {
        Node<T,G>* result = _searcher(_root, &key);
        if(result==NULL)
        {
            throw;
        }
        cout<<"found: "<<result->getItem()<<endl;
        return result;
    }
    catch(int){
        cout<<"Key was not found"<<endl;
    }
}

template <typename T, typename G>
Node<T,G>* Tree<T,G>::_searcher (Node<T,G>* currNode, const T& key) const{
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
    if(key._root==NULL)
    {
       key._root = item;
    }
    else
    {
        =
    }

}



template <typename T, typename G>
void Tree<T,G>::inOrderTraversal() const{
    cout<<"Binary search tree content:"<<endl;
    if (_root==NULL)
    {
        return;
    }
    _traverser(_root);
    return;

}

template <typename T, typename G>
void Tree<T,G>::_traverser(Node<T,G>* currNode) const{
    cout<<"Key:"<<currNode->getKey()<<" data: "<<currNode->getItem()<<endl;
    if (currNode->getLeftChild()!=NULL)
    {
        _traverser(currNode->getLeftChild());
    }
    if (currNode->getRightChild()!=NULL)
    {
        _traverser(currNode->getRightChild());
    }
    return;
}
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
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
using std::vector;

const string PRINT_TREE_SIZE("Tree size: ");
const string PRINT_NOT_EMPTY_TREE("The tree is not empty");
const string PRINT_EMPTY_TREE("The tree is empty");
const string KEY_NOT_UNIQUE("Key not unique");
const string KEY_NOT_FOUND("Key was not found");
const string NODE_NOT_LEAF("The node is not a leaf!");
const string PRINT_KEY("key: ");
const string DATA("\t data:");
const string TREE_CONTENT("Binary search tree content:");
const string PRINT_FOUND("found:");
//Creates binary tree with nodes, which stores an item according to the key number.

template <typename T, typename G>
class Tree{
public:
    //Constructor
    inline Tree(): _size(0), _root(NULL){}

    //checks if tree has no nodes
    bool isEmpty() const;

    //finds tree size
    size_t size() const;

    //searches for specific key, returns node.
    Node<T,G>* search (const T& key) const;

    //create new node, correct location within the tree, if empty inserts new node
    void insert(const T& key,const G& item);

    //deletes node if is a leaf and if it exists.
    void deleteLeaf(const T& key);

    //prints all nodes(key,item) in tree recursively
    void inOrderTraversal() const;

    // ends program
    void quit();

    //Destructor
    ~Tree(){}

private:
    Node<T,G>*_root;

    size_t _size;


    //those are the functions that virtually make the operations
    Node<T,G>* _searcher (Node<T,G>* currNode, const T& key) const;

    void _inserter(const T& key,const G& item);

    void _deleter(Node<T,G>* targetedLeaf, const T& key);

    void _traverser(Node<T,G>* currNode) const;

    void _quitter(Node<T,G>* currNode);

    inline void _error(const string& err){throw (runtime_error(err));}

};



template <typename T, typename G>
size_t Tree<T,G>::size() const{
    cout<<PRINT_TREE_SIZE<<_size<<endl;
    return _size;
}

template <typename T, typename G>
bool Tree<T,G>::isEmpty() const {
    if(_size)
    {
        cout<<PRINT_NOT_EMPTY_TREE<<endl;
        return false;
    }
    else
    {
        cout<<PRINT_EMPTY_TREE<<endl;
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
            _error(KEY_NOT_UNIQUE);
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
    Node<T,G>* newNodeRoot = _root;
    Node<T,G>* currentNode = NULL;
    while (newNodeRoot != NULL)
    {
        currentNode=newNodeRoot;
        {
            if(key < newNodeRoot->getKey())
            {
                newNodeRoot = newNodeRoot->getLeftChild();
            }
            else if(key > newNodeRoot->getKey())
            {
                newNodeRoot = newNodeRoot->getRightChild();
            }
        }
    }

    Node<T,G>* newNode = new Node<T,G>(key, item, currentNode);
    if (key<currentNode->getKey())
    {
        currentNode->setLeft(newNode);
    }
    else
    {
        currentNode->setRight(newNode);
    }
}



template <typename T, typename G>
Node<T,G>* Tree<T,G>::search (const T& key) const{
    try {
        Node<T,G>* result = _searcher(_root, key);
        if(result==NULL)
        {
            throw (runtime_error (KEY_NOT_FOUND));
        }
        cout<<PRINT_FOUND<<PRINT_KEY<<key<<DATA<<result->getItem()<<endl;
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
    cout<<TREE_CONTENT<<endl;
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
    cout<<PRINT_KEY<<currNode->getKey()<<DATA<<currNode->getItem()<<endl;
    if (currNode->getRightChild()!=NULL)
    {
        _traverser(currNode->getRightChild());
    }
    return;
}


template <typename T, typename G>
void Tree<T,G>::deleteLeaf(const T& key)

{
    try
    {
        Node<T,G>* result = _searcher(_root,key);
        if(result==NULL)
        {
            throw (runtime_error (KEY_NOT_FOUND));
        }
        else if((result->getLeftChild() != NULL) || (result->getRightChild() != NULL))
        {
            throw (runtime_error (NODE_NOT_LEAF));
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

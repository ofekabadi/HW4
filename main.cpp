#include <iostream>
#include <stdexcept>
#include <string>
#include "Tree.h"

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
void treeSession( const T &keyType, const G &valueType);
template <typename T>
void treeCreator(const T &keyType);

typedef enum {NEW=0, INSERT, DELETE, SEARCH, EMPTY, SIZE, TRAVEL, QUIT} CommandsEnum;
const string consoleCommands[] = {"new", "insert", "deleteLeaf", "search", "empty",
                                  "size", "inorderTraversal", "quit"};

typedef enum {INT=0, FLOAT, STRING} TreeTypes;
const string treeTypes[] = {"int", "float", "string"};

typedef enum {KEY, ITEM} TypesLocationErrors;
const string typesErrorLocation[] = {"Key", "Item"};

const string EMPTY_TREE("empty");
const string NOT_EMPTY_TREE("not ");
const string FOUND = "found:";

void errorThrower(TypesLocationErrors loc, const string& erroredType){
    throw runtime_error("Bad " + typesErrorLocation[loc] + " Type: " + erroredType);
}

template<typename Type1>
Type1 getInputs(CommandsEnum command){
    Type1 input;
    cin >> input;
    if (cin.fail()){
        // insert your code here
    }
    return input;
}

template<typename Type1, typename Type2>
pair<Type1, Type2> getInputs(CommandsEnum command){
    Type1 firstInput(getInputs<Type1>(command));
    Type2 secondInput(getInputs<Type2>(command));
    return make_pair(firstInput, secondInput);
}

template <typename T, typename G>
void treeSession( const T &keyType, const G &valueType) {
    Tree<T, G> tree;
    string input;
    cin >> input;
    while (input != consoleCommands[QUIT]){/*
        if (input == consoleCommands[INSERT]) {
            try{
                pair<T,G> tempPair(getInputs<T, G>(INSERT));
                T key(tempPair.first);
                G item(tempPair.second);
                tree.insert(key, item);
            }
            catch (const logic_error& error){
                cerr << error.what() << endl;
            }
        }
        else if (input == consoleCommands[DELETE]){
            try{
                pair<T,G> tempPair(getInputs<T, G>(DELETE));
                T key(tempPair.first);
                G item(tempPair.second);
                tree.deleteLeaf(key);
            }
            catch (const logic_error& error){
                cerr << error.what() << endl;
            }

        }
        else if (input == consoleCommands[SEARCH]){
            try{
                pair<T,G> tempPair(getInputs<T, G>(SEARCH));
                T key(tempPair.first);
                G item(tempPair.second);
                tree.search(key);
            }
            catch (const logic_error& error){
                cerr << error.what() << endl;
            }
        }
        else*/ if (input == consoleCommands[EMPTY]){
            tree.isEmpty();
        }
        else if (input == consoleCommands[SIZE]){
            tree.size();
        }
        /*else if (input == consoleCommands[TRAVEL]){
            tree.inOrderTraversal();
        }
        else {
            cerr << "Bad command" << endl;
        }*/
        cin >> input;
    }
}

template <typename T>
void treeCreator(const T &keyType){
    string valueType(NULL);
    int valueTypeInt(0);
    float valueTypeFloat(0);
    cin >> valueType;
    if (valueType == treeTypes[INT]){
        treeSession(keyType,valueTypeInt);
    }
    else if (valueType == treeTypes[FLOAT]){
        treeSession(keyType,valueTypeFloat);
    }
    else if (valueType == treeTypes[STRING]){
        treeSession(keyType,valueType);
    }
    else{
        // insert your code here
    }
}

int main() {
    try{
        string input;
        string keyType;
        int keyTypeInt;
        float keyTypeFloat;
        cin >> input;
        cin>>keyType;
        if (input == consoleCommands[NEW]) {

            if (keyType == treeTypes[INT]) {
                 treeCreator(keyTypeInt);
            }
            else if (keyType == treeTypes[FLOAT]){
                    treeCreator(keyTypeFloat);
            }
            else if (keyType == treeTypes[STRING]){
                    treeCreator(keyType);
            }
            else{
                errorThrower(KEY, keyType);
            }
        }
        else {
            // insert your code here
        }
    }
    catch( const runtime_error& error){
        cerr << error.what() << endl;
    }
}
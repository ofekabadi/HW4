#include <string>
#include <iostream>
#include <stdexcept>
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

typedef enum {NEW=0, INSERT, DELETE, SEARCH, EMPTY, SIZE, TRAVEL, QUIT} CommandsEnum;
const string consoleCommands[] = {"new", "insert", "deleteLeaf", "search", "empty",
                                  "size", "inorderTraversal", "quit"};

typedef enum {INT=0, FLOAT, STRING} TreeTypes;
const string treeTypes[] = {"int", "float", "string"};

typedef enum {KEY=0, ITEM} TypesLocationErrors;
const string typesErrorLocation[] = {"Key", "Item"};

const string EMPTY_TREE("empty");
const string NOT_EMPTY_TREE("not ");
const string FOUND = "found:";
const string BAD_COMMAND = "Bad command";
const string BAD_INPUT = "Bad Input: ";
const string BAD_INPUT_TYPE = "Bad input type!";

void errorThrower(TypesLocationErrors loc, const string& erroredType){
    throw runtime_error("Bad " + typesErrorLocation[loc] + " Type: " + erroredType);
}

template<typename Type1>
Type1 getInputs(CommandsEnum command){
    try{
        Type1 input;
        cin >> input;
        //cout<<"input: "<<input<<endl;
        if (cin.fail()){
            throw (runtime_error (BAD_INPUT_TYPE));
        }
        return input;
    }

    catch( const runtime_error& error){
        cerr << error.what() << endl;
    }
}


template<typename Type1, typename Type2>
pair<Type1, Type2> getInputs(CommandsEnum command){
    Type1 firstInput(getInputs<Type1>(command));
    Type2 secondInput(getInputs<Type2>(command));
    return make_pair(firstInput, secondInput);
}

template <typename T, typename G>
void treeSession() {
    Tree<T, G> tree;
    string input;
    cin >> input;
    while (input != consoleCommands[QUIT]){
        if (input == consoleCommands[INSERT]) {     //WORKS, BUT CURRENTLY CAN'T DISCERN
            // BETWEEN RIGHT AND WRONG INPUT TYPES, E.G. YOU CAN GIVE A FLOAT WHILE
            // WAITING FOR AN INT
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
            T key;
            cin >> key;
            tree.deleteLeaf(key);

        }
        else if (input == consoleCommands[SEARCH]){
            T key;
            cin >> key;
            tree.search(key);
        }
        else if (input == consoleCommands[EMPTY]){
            tree.isEmpty();
        }
        else if (input == consoleCommands[SIZE]){
            tree.size();
        }
        else if (input == consoleCommands[TRAVEL]){
            tree.inOrderTraversal();
        }
        else {
            cerr << BAD_COMMAND << endl;
        }
        cin >> input;
    }
    tree.quit();
}

template <typename T>
void treeCreator(){
    string valueType;
    cin >> valueType;
    if (valueType == treeTypes[INT]){
        treeSession<T, int>();
    }
    else if (valueType == treeTypes[FLOAT]){
        treeSession<T, float>();
    }
    else if (valueType == treeTypes[STRING]){
        treeSession<T, string>();
    }
    else{
            errorThrower(ITEM, valueType);
    }
}

int main() {
    try{
        string input;
        cin >> input;
        if (input == consoleCommands[NEW]) {
            string keyType;
            cin >> keyType;
            if (keyType == treeTypes[INT]) {
                treeCreator<int>();
            }
            else if (keyType == treeTypes[FLOAT]){
                treeCreator<float>();
            }
            else if (keyType == treeTypes[STRING]){
                treeCreator<string>();
            }
            else{
                errorThrower(KEY, keyType);
            }
        }
        else {
            throw (runtime_error (BAD_COMMAND));
        }
    }
    catch( const runtime_error& error){
        cerr << error.what() << endl;
    }
}
/*
 *  lookupTable.cpp
 *  ENSF 694 Lab 4, exercise A part 2
 *  Completed by: Jaskirat Singh
 *  Submission date: July 26
 */

#include "lookupTable.h"

//LT_Node constructor
//Initialized pairM and nextM using pairA and nextA respectively
LT_Node::LT_Node(const Pair& pairA, LT_Node *nextA):pairM(pairA), nextM(nextA){
}

//LookupTable constructor
//Initializing size, cursor and head to zero or nullptr
LookupTable::LookupTable() : sizeM(0), cursorM(nullptr), headM(nullptr){
}

//Copy constructor
LookupTable::LookupTable(const LookupTable &source){
    //COPY FUNC TO SIMPLIFY CODE
    copy(source);
}

//Assignment operator
LookupTable& LookupTable::operator=(const LookupTable &rhs){
    //Check if rhs = this
    if (this != &rhs) {
        destroy();
        copy(rhs);
    }
    //Return this if same obj on both sides of the = operator
    return *this;
}

//Destructor
LookupTable::~LookupTable() {
    destroy();
}

//Move cursorM to the beginning of the list
LookupTable& LookupTable::begin() {
    cursorM = headM;
    return *this;
}

//Return the number of keys in the table
int LookupTable::size() const {
    int count = 0;
    //Move cursor to the beginning of the list
    LT_Node* element = headM;
    //Increment cursor until end of list, and keep count
    while(element != nullptr){
        count ++;
        element = element->nextM;
    }
    return count;
}

//Check if the cursor is attached to a key/datum pair
int LookupTable::cursor_ok() const {
    return cursorM != nullptr;
}

//Return the key of the key/datum pair to which the cursor is attached
const int& LookupTable::cursor_key() const {
    if(!cursor_ok()) {
        cerr << "Cursor not ok!" << endl;
        exit(1);
    }
    return cursorM->pairM.key;
}

//Return the datum of the key/datum pair to which the cursor is attached
const Type& LookupTable::cursor_datum() const {
    //If cursor is not valid then return error
    if(!cursor_ok()) {
        cerr << "Cursor not ok!" << endl;
        exit(1);
    }
    //If cursor is valid then return corresponding datum
    return cursorM->pairM.datum;
}

//Insert a key/datum pair into the table
void LookupTable::insert(const Pair& pairA){
    //Find key in data
    find(pairA.key);
    
    //At this point if key is found then cursor points to it
    //If key is not found then cursor is in off-list state
    if (cursor_ok()){
        cursorM->pairM.datum = pairA.datum;
    } else{
        //Create new node
        LT_Node* newNode = new LT_Node(pairA, nullptr);

        //If the list is empty, insert at the head
        if(headM == nullptr) {
            headM = newNode;
        } else{
            //Move cursor to the head
            begin();
            //Keep track of previous node
            LT_Node* previous = nullptr;

            //Find the right position to insert new node
            while(cursorM != nullptr && cursorM->pairM.key < pairA.key) {
                previous = cursorM;
                cursorM = cursorM->nextM;
            }

            //Insert at the head if the new key is the smallest
            if(previous == nullptr){
                newNode->nextM = headM;
                headM = newNode;
            } else{
                // Insert between previous and current
                previous->nextM = newNode;
                newNode->nextM = cursorM;
            }
        }
        //Increase the size of list
        sizeM++;
    }
    //Move cursor to off-list state
    cursorM = nullptr;
}

//Remove a key/datum pair from the table
int LookupTable::remove(const int& keyA) {
    // Find key in data
    find(keyA);
    // At this point if key is found then cursor points to it
    // If key is not found then cursor is in off-list state
    if(cursor_ok()){
        LT_Node* toBeDeleted = cursorM;
        int deletedKey = toBeDeleted->pairM.key;

        //If node to be deleted is head
        if(toBeDeleted == headM) {
            headM = headM->nextM;
        } else{
            //Find the node before the one to be deleted
            LT_Node* previous = headM;
            while(previous->nextM != toBeDeleted) {
                previous = previous->nextM;
            }
            //Set nextM on previous to nextM of node to be deleted
            previous->nextM = toBeDeleted->nextM;
        }

        //Delete node from memory
        delete toBeDeleted;
        //Update size of list
        sizeM--;
        //Move cursor to off-list state
        cursorM = nullptr;
        //Return the key that was deleted
        return deletedKey;
    }
    //Else table is unchanged
    //Move cursor to off-list state
    cursorM = nullptr;
    //Nothing was removed
    return 0;
}

//Find a key in the table
void LookupTable::find(const int& keyA){
    //Set cursor to the beginning of the list
    begin();
    while(cursorM != nullptr){
        if(cursorM->pairM.key == keyA){
            //Cursor now attached to the correct key/datum pair
            return;
        }
        //Move cursor to the next node
        cursorM = cursorM->nextM;
    }
    //KeyA does not match any key
    cursorM = nullptr;
}

//Move cursor to the first key/datum pair in the table
void LookupTable::go_to_first(){
    if(size() > 0){
        cursorM = headM;
    }
}

//Move cursor forward from one pair to the next
void LookupTable::step_fwd() {
    if(cursor_ok()){
        cursorM = cursorM->nextM;
    }
}

//Make the table empty
void LookupTable::make_empty() {
    //destroy() handles memory management
    //destroy() seets size to 0
    //destroy() points cursor to off-list state
    destroy();
    headM = nullptr;
}

//Display the table
void LookupTable::display() const {
    //If table is empty exit the function
    if(isEmpty()) return;
    //Print the node that the cursor is pointing to
    cout << cursorM->pairM.key << " " << cursorM->pairM.datum.get_label() << endl;
}

// Check if the table is empty
bool LookupTable::isEmpty() const {
    return sizeM == 0;
}

// Retrieve the key at a specific position
int* LookupTable::retrieve_at(int i) {
    //Check if i is within the valid range
    if(i < 0 || i >= sizeM){
        return nullptr;
    }
    
    //Point the cursor to the head
    begin();
    
    //Iterate through the list moving the cursor forward
    while(i > 0 && cursorM != nullptr){
        cursorM = cursorM->nextM;
        i--;
    }
    
    //Get location of requested key
    int* keyAti = &cursorM->pairM.key;
    
    //Point cursor to off-lsit state
    cursorM = nullptr;
    
    return keyAti;
}

// Destroy all nodes in the list
void LookupTable::destroy(){
    //Iterate through all the elements
    while(headM != nullptr){
        LT_Node* temp = headM;
        //Shift head forward
        headM = headM->nextM;
        //Delete original head
        delete temp;
    }
    
    //Set size to 0
    sizeM = 0;
    
    //Set cursor to off-list state
    cursorM = nullptr;
}

// Copy the source LookupTable into this LookupTable
void LookupTable::copy(const LookupTable& source) {
    if (source.headM == nullptr) {
        headM = nullptr;
        cursorM = nullptr;
        sizeM = 0;
        return;
    }

    headM = new LT_Node(source.headM->pairM, nullptr);
    LT_Node* current = headM;
    LT_Node* sourceCurrent = source.headM->nextM;

    while (sourceCurrent != nullptr) {
        current->nextM = new LT_Node(sourceCurrent->pairM, nullptr);
        current = current->nextM;
        sourceCurrent = sourceCurrent->nextM;
    }

    sizeM = source.sizeM;

    if (source.cursorM == nullptr) {
        cursorM = nullptr;
    } else {
        sourceCurrent = source.headM;
        current = headM;
        while (sourceCurrent != source.cursorM) {
            sourceCurrent = sourceCurrent->nextM;
            current = current->nextM;
        }
        cursorM = current;
    }
}

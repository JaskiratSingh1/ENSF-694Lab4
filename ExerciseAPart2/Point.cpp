/*
 *  Point.cpp
 *  ENSF 694 Lab 4, exercise A part 2
 *  Completed by: Jaskirat Singh
 *  Submission date: July 26
 */

#include "Point.h"

//Constructor
Point::Point(int x, int y, const char* label): x(x), y(y){
    //Allocate memory for label
    this->label = new char[strlen(label) + 1];
    //Copy the label
    strcpy(this->label, label);
}

//Destructor
Point::~Point() {
    // Deallocate memory for label
    delete[] label;
}

//Copy constructor
Point::Point(const Point& src): x(src.x), y(src.y) {
    //Allocate memory for label
    this->label = new char[strlen(src.label) + 1];
    //Copy the label
    strcpy(this->label, src.label);
}

//Assignment operator
Point& Point::operator=(const Point& rhs) {
    //Self assignment
    if(this == &rhs){
        return *this;
    }

    //Deallocate label
    delete[] label;
    
    //Allocate memory for label
    label = new char[strlen(rhs.label) + 1];
    
    //Copy label
    strcpy(label, rhs.label);

    //Copy x and y
    x = rhs.x;
    y = rhs.y;

    return *this;
}

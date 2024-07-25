//
//  Point.cpp
//  ExerciseAPart2
//
//  Created by Jaskirat Singh on 2024-07-25.
//

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
    //Self-assignment
    if(this == &rhs){
        return *this;
    }

    //Deallocate label
    delete[] label;

    //Copy x and y
    x = rhs.x;
    y = rhs.y;

    //Allocate memory for label
    label = new char[strlen(rhs.label) + 1];
    //Copy label
    strcpy(label, rhs.label);

    return *this;
}

//
//  Point.hpp
//  Lookup Table
//
//  Created by Mahmood Moussavi on 2024-05-10.
//

#include <cstring>

#ifndef Point_h
#define Point_h
class Point {
public:
    Point(int x, int y, const char* label);
    ~Point();
    Point(const Point& src);
    Point& operator=(const Point& rhs);
    int getx() const {return x;}
    int gety() const {return y;}
    char* get_label()const {return label;}
    
private:
    int x, y;    // x and y coordinates of a point on Cartesian plain
    char* label; // pointer to an array allocated on the heap to store the label for a point
};



#endif /* Point_h */

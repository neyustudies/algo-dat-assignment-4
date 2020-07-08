#ifndef POINT_HPP
#define POINT_HPP
#include <math.h>
#include <iostream>

/**
 * @brief Generate a set of random points (as a matrix / list-of-list) 
 * given the size of the set and the ranges (vertical and horizontal) 
 * in which the points are generated.
 */

// 2D Point
struct Point {
  int X = 0;
  int Y = 0;
};

namespace Points {

  // compare x coordinate for sorting
  template <typename T>
  bool compareX(T const& p1, T const& p2) {
    return p1.X < p2.X;
  }

  // compare y coordinate for sorting
  template <typename T>
  bool compareY(T const& p1, T const& p2) {
    return p1.Y < p2.Y;
  }

  // return distance between two points
  float distance(Point const& p1, Point const& p2) {
    return sqrt(((p2.X - p1.X) * (p2.X - p1.X)) +
                ((p2.Y - p1.Y) * (p2.Y - p1.Y)));
  }
  
}

// free function operator<<() prints a 2D Point
std::ostream& operator<<(std::ostream& os, Point const& p) {
  os << "(" << p.X << "," << p.Y << ")";
  return os;
}

#endif // POINT_HPP
#ifndef DIVIDEANDCONQUER_HPP
#define DIVIDEANDCONQUER_HPP
#include "Point.hpp"
#include "MergeSort.hpp"

/**
 * @brief Implement the presented Divide & Conquer algorithm 
 * for finding the two closest points in the generated set 
 */

namespace DivideAndConquer {

  // produce random points in a given interval
  std::vector<Point> randomPoints(unsigned int size, int minX, int maxX, int minY, int maxY) {
    std::srand((int)time(0));
    std::vector<Point> p;
    while(p.size() < size) {
      int X = minX + std::rand() % (( maxX + 1 ) - minX);
      int Y = minY + std::rand() % (( maxY + 1 ) - minY);
      auto it = std::find_if(std::cbegin(p), std::cend(p), 
                [X, Y](Point const& p) {return p.X == X && p.Y == Y;});
      if(it == std::cend(p)) {p.push_back({X, Y});}
    } return p;
  }

  
  // naive algorithm of finding distances between all pairs of points O(n²)
  std::pair<Point, Point> NaiveClosestPoints(std::vector<Point> const& p) {
    std::pair<Point, Point> closest_points;
    if(p.size() <=1) {
      throw "There needs to be at least two points";
    }
    float minDistance = std::numeric_limits<float>::max();
    for(Point p1 : p) {
      for(Point p2 : p) {
        if(p1.X == p2.X && p1.Y == p2.Y) {continue;}
        float dist = Points::distance(p1, p2);
        if(dist < minDistance) {
          minDistance = dist;
          closest_points = std::make_pair(p1, p2);
        }
      }
    } return closest_points;
  }


  // divide and conquer strategy: divide, conquer and combine O(n log n)
  std::pair<Point, Point> FindClosestPoints(std::vector<Point> const& pX, std::vector<Point> const& pY) {
    
    /* D I V I D I N G */
    
    unsigned int size = pX.size();
    unsigned int half = (size / 2);
    std::vector<Point> lX, rX, lY, rY;
    if(size < 4) { // brute force strategy for small value of point 
      return NaiveClosestPoints(pX);
    }
    int halfX = pX[half].X;
    // pushing all values into the correct container
    for(auto i = 0; i < half; ++i) {
      lX.push_back(pX[i]);
    }
    for(auto i = half; i < size; ++i) {
      rX.push_back(pX[i]);
    }
    for(Point p : pY) {
      if(p.X < halfX) {
        lY.push_back(p);
      } else {
        rY.push_back(p);
      }
    }

    /* C O N Q U E R I N G */

    // finding closest points in each sub-plane
    auto  pair_left   = FindClosestPoints(lX, lY);
    auto  pair_right  = FindClosestPoints(rX, rY);
    float minLeft     = Points::distance(pair_left.first, pair_left.second);
    float minRight    = Points::distance(pair_right.first, pair_right.second);
    float minDistance = std::min(minLeft, minRight);

     /* C O M B I N I N G */

    // check if there are closer points in two different sub-planes
    std::pair<Point, Point> overallMinPoints = (minDistance == minLeft ? pair_left : pair_right);
    std::vector<Point> subY;
    for(Point p : pY) {
      if(p.X >= (halfX - minDistance) && p.X <= (halfX + minDistance)) {
        subY.push_back(p);
      }
    }
    for(auto i = 0; i < subY.size(); ++i) {
      for(auto j=i+1; j< subY.size() && (subY[j].Y - subY[i].Y) < minDistance; ++j) {
        float dist = Points::distance(subY[i], subY[j]);
        if(dist < minDistance) {
          overallMinPoints = std::make_pair(subY[i], subY[j]);
          minDistance = dist;
        }
      }
    } return overallMinPoints;
  }


  // return the two closest points, as presort using mergesort
  std::pair<Point, Point> closestPoints(std::vector<Point> const& p) {
    std::vector<Point> pX{p}, pY{p};
    MergeSort::mergesort(std::begin(pX), std::end(pX), Points::compareX<Point>);
    MergeSort::mergesort(std::begin(pY), std::end(pY), Points::compareY<Point>);
    return DivideAndConquer::FindClosestPoints(pX, pY);
  }

}

#endif // DIVIDEANDCONQUER_HPP
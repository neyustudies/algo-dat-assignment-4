#include "DivideAndConquer.hpp"

/**
 * @brief Implement a main function/script that calls the algorithm 
 * with the different inputs and checks if the result is correct 
 * (using the naive algorithm, which checks the distances pair-by-pair).
 */


int size = 1000;  // container size
int minX = 1;     // smallest possible X
int minY = 1;     // smallest possible Y
int maxX = 10000; // largest possible X
int maxY = 10000; // largest possible Y


int main() {

  // part one: generate random points in a given container size (1000)
  std::vector<Point> p  = DivideAndConquer::randomPoints(size, minX, maxX, minY, maxY);


  // part two: find closest pair by using both DivideAndConquer and naive algorithm
  std::pair<Point,Point> dac = DivideAndConquer::closestPoints(p);
  std::pair<Point,Point> naive = DivideAndConquer::NaiveClosestPoints(p);


  // output
  std::cout << p.size() << " random points between min("
            << minX << "," << minY << ") and max(" 
            << maxX << "," << maxY << ") have been generated...\n"
            << "Sorting and searching for the two closest Points...\n";
  std::cout << "\nDivide and Conquer algorithm:";
  std::cout << "\nClosest points: " << dac.first << " and " << dac.second
            << "\nDistance: " << Points::distance(dac.first, dac.second);
  std::cout << "\nComparing to result of naive algorithm:";
  std::cout << "\nClosest pair: " << naive.first << " and " << naive.second
            << "\nDistance: " << Points::distance(naive.first, naive.second) << std::endl;


  // part three: compare the results of both algorithms
  std::cout << "----------------------------------------\n";
  if(Points::distance(dac.first, dac.second) == Points::distance(naive.first, naive.second)) {
    std::cout << "Results match, mission accomplished ✔︎\n\n";
  } else {
    std::cout << "Mission failed, results don't match! ✗\n\n";
  }

  return 0;

}

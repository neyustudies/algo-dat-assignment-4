#ifndef MERGESORT_HPP
#define MERGESORT_HPP
#include <vector>
#include <algorithm>
#include <iterator>

/**
 * @brief Implement the sorting algorithm Merge Sort, which you will 
 * have to use in the algorithm for solving Closest-Points
 * ---
 * Based on divide and conquer algorithm with worst-case time 
 * complexity being Ο(n log n) it very efficient.
 * Merge sort first divides the array into equal halves and then 
 * combines them in a sorted manner
 */

 namespace MergeSort {

  // second call Merge Sort, used in mergesort() when combining
  template <typename First, typename Sec, typename Output, typename Compare>
  Output merge(First f1, First l1, Sec f2, Sec l2, Output d, Compare comp) {
    for(;f1 != l1; ++d) {
      if(f2 == l2) {
      return std::move(f1, l1, d);
    } 
    if(comp(*f2, *f1)) {
      *d = std::move(*f2);
      ++f2;
    } else {
      *d = std::move(*f1);
      ++f1;
      }
    } return std::move(f2, l2, d);
  }

  // first call Merge Sort
  // since we have pairs of points, we can use iterators and a comparator
  template <typename Iterator, typename Compare>
  void mergesort(Iterator first, Iterator last, Compare comp) {
    auto r = std::distance(first, last);
    if (r < 2) {return;}
    auto q = first + r / 2;       // subdividing the input
    mergesort(first, q, comp);    // sort recursively
    mergesort(q, last, comp);
    // dereferencing the iterator
    std::vector<typename std::iterator_traits<Iterator>::value_type> it(r);
    MergeSort::merge(first, q, q, last, it.begin(), comp); // combine result
    std::move(std::make_move_iterator(it.begin()),
              std::make_move_iterator(it.end()), first);
  }
                  
}

 
 #endif // MERGESORT_HPP
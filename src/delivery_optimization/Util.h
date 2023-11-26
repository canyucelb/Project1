#pragma once
#include <unordered_map>

// A constant to represent a very high value, effectively infinity, used in calculations.
const int inf = 1e9;
class Car;

// The 'statistics' namespace is dedicated to keeping track of various statistics during the simulation.
namespace statistics {
  // Count of processed queries.
  extern int cnt_processed_queries;

  // Maximum, minimum, and sum of the ideal wait time w0 for orders.
  extern int max_w0;
  extern int min_w0;
  extern int sum_w0;

  // Maximum, minimum, and sum of the actual wait time for orders.
  extern int max_wait;
  extern int min_wait;
  extern int sum_wait;

  // Maximum, minimum, and sum of payments for orders.
  extern int max_pay;
  extern int min_pay;
  extern int sum_pay;

  // Mapping of Car objects to the number of orders they have handled.
  extern std::unordered_map<Car *, int> how_many_orders;

  // Count of payments, indexed by the payment amount.
  extern std::unordered_map<double, int> cnt_of_pay;

  // Function to output the collected statistics.
  void output_statistics();

  // Function to compute the average payment.
  double get_avg_pay();
} // namespace statistics

// The 'Geometry' namespace contains functions related to geometric calculations.
namespace Geometry {

  // Function to calculate the Manhattan distance between two points (x1, y1) and (x2, y2).
  int distance(int x1, int y1, int x2, int y2);

  // Overloaded function to calculate the Manhattan distance between two points given as pairs.
  int distance(std::pair<int, int> p1, std::pair<int, int> p2);

  // Function to find the midpoint between two points given as pairs.
  std::pair<int, int> get_middle(std::pair<int, int> p1, std::pair<int, int> p2);
} // namespace Geometry

// The 'Algorithm' namespace includes algorithms used in the simulation.
namespace Algorithm {

  // Function to find the best matching between two sets of points, typically used for optimizing order assignments.
  std::vector<std::pair<int, int>>
  find_best_matching(std::vector<std::pair<int, int>> p1,
                     std::vector<std::pair<int, int>> p2);

}

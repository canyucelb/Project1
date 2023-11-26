#include "Util.h"
#include <vector>

// Namespace for statistics-related variables and functions.
namespace statistics {

// Statistical counters and mappings.
int cnt_processed_queries = 0; // Count of processed queries.
int max_w0 = -inf; // Maximum ideal wait time, initialized to negative infinity.
int min_w0 = +inf; // Minimum ideal wait time, initialized to positive infinity.
int sum_w0 = 0; // Sum of ideal wait times.
int max_wait = -1e9; // Maximum actual wait time, initialized to a large negative value.
int min_wait = +1e9; // Minimum actual wait time, initialized to a large positive value.
int sum_wait = 0; // Sum of actual wait times.
int max_pay = -1e9; // Maximum payment amount, initialized to a large negative value.
int min_pay = +1e9; // Minimum payment amount, initialized to a large positive value.
int sum_pay = 0; // Sum of payments.
std::unordered_map<Car *, int> how_many_orders; // Map of cars to the number of orders processed.
std::unordered_map<double, int> cnt_of_pay; // Map of payment amounts to their frequency.

// Function to output the gathered statistics.

    void output_statistics() {
        printf("\n---Order Summary---\n");

        printf("1. Order Processing Statistics:\n");
        int mn_orders = +inf, mx_orders = -inf, sm_orders = 0;
        for (const auto& iter : how_many_orders) {
            mn_orders = fmin(mn_orders, iter.second);
            mx_orders = fmax(mx_orders, iter.second);
            sm_orders += iter.second;
        }
        printf("   - Total Orders Processed: %d\n", cnt_processed_queries);
        printf("   - Failed Orders: %d\n", cnt_of_pay[0]);
        printf("   - Average Orders per Car: %.4lf\n", 1.0 * sm_orders / how_many_orders.size());
        printf("   - Maximum Orders by a Single Car: %d\n", mx_orders);
        printf("   - Minimum Orders by a Single Car: %d\n", mn_orders);

        printf("\n2. Distance Metrics:\n");
        printf("   - Total Distance Covered: %d units\n", sum_w0);
        printf("   - Average Distance per Car: %.4lf units\n", 100 + 1.0 * sum_w0 / fmax(1, cnt_processed_queries));
        printf("   - Maximum Distance by a Single Car: %d units\n", max_w0);
        printf("   - Minimum Distance by a Single Car: %d units\n", min_w0);

        printf("\n3. Time Metrics:\n");
        printf("   - Total Wait Time: %d ticks\n", sum_wait);
        printf("   - Average Wait Time per Order: %.4lf ticks\n", 1.0 * sum_wait / cnt_processed_queries);
        printf("   - Maximum Wait Time for an Order: %d ticks\n", max_wait);
        printf("   - Minimum Wait Time for an Order: %d ticks\n", min_wait);

        printf("\n4. Payment Statistics:\n");
        printf("   - Total Payment Received: %d credits\n", sum_pay);
        printf("   - Average Payment per Order: %.4lf credits\n", 1.0 * sum_pay / cnt_processed_queries);
        printf("   - Maximum Payment for a Single Order: %d credits\n", max_pay);
        printf("   - Minimum Payment for a Single Order: %d credits\n", min_pay);

        printf("\n---Summary Ends---\n");
    }
// Function to calculate the average payment.
double get_avg_pay() {
  return 100 + 1.0 * sum_w0 / fmax(1, cnt_processed_queries);
}

} 
// Namespace for geometric calculations.
namespace Geometry {
// Function to calculate the Manhattan distance between two points.
int distance(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}
// Overloaded function to calculate Manhattan distance between points given as pairs.
int distance(std::pair<int, int> p1, std::pair<int, int> p2) {
  return distance(p1.first, p1.second, p2.first, p2.second);
}
// Function to calculate the midpoint between two points.
std::pair<int, int> get_middle(std::pair<int, int> p1, std::pair<int, int> p2) {
  return std::make_pair((p1.first + p2.first) / 2, (p1.second + p2.second) / 2);
}

} 
// Namespace for algorithmic functions.
namespace Algorithm {
  // Function to find the best matching between two sets of points.
std::vector<std::pair<int, int>>
 // Implementation of an algorithm to find the best matching between two sets of points.
  // This involves a form of assignment problem solving, a variant of the Hungarian Algorithm.
find_best_matching(std::vector<std::pair<int, int>> p1,
                   std::vector<std::pair<int, int>> p2) {
  int n = (int)p1.size();
  int m = (int)p2.size();

  reverse(p1.begin(), p1.end());
  reverse(p2.begin(), p2.end());

  p1.push_back({0, 0});
  p2.push_back({0, 0});

  reverse(p1.begin(), p1.end());
  reverse(p2.begin(), p2.end());

  std::vector<int> u(n + 1), v(m + 1), p(m + 1), way(m + 1);

  for (int i = 1; i <= n; i++) {
    p[0] = i;
    int j0 = 0;
    std::vector<int> minv(m + 1, inf);
    std::vector<char> used(m + 1);
    do {
      used[j0] = true;
      int i0 = p[j0], delta = inf, j1;
      for (int j = 1; j <= m; j++) {
        if (!used[j]) {
          int cur =
              /*a[i0][j]*/ Geometry::distance(p1[i0], p2[j]) - u[i0] - v[j];
          if (cur < minv[j]) {
            minv[j] = cur;
            way[j] = j0;
          }
          if (minv[j] < delta) {
            delta = minv[j];
            j1 = j;
          }
        }
      }
      for (int j = 0; j <= m; j++) {
        if (used[j]) {
          u[p[j]] += delta;
          v[j] -= delta;
        } else {
          minv[j] -= delta;
        }
      }
      j0 = j1;
    } while (p[j0] != 0);
    do {
      int j1 = way[j0];
      p[j0] = p[j1];
      j0 = j1;
    } while (j0);
  }
  std::vector<std::pair<int, int>> matching;
  for (int j = 1; j <= m; j++) {
    if (p[j]) {
      matching.push_back({p[j] - 1, j - 1});
    } else {
     
    }
  }
  return matching;
}

} 

#include "City.h"
#include "Car.h"
#include "Order.h"
#include "Util.h"

#include <iostream>
#include <random>
#include <set>
#include <unordered_map>

// Constructor for the City class.
City::City(int width, int height, int numCars) : width(width), height(height) {
  // Initialize cars with the default constructor and add them to the cars
  // vector.
  for (int i = 0; i < numCars; i++) {
    cars.push_back(new Car());
  }
}

// Method to process orders up to a given timestamp.
void City::process_orders(int timestamp) {
  // Iterate through each car and process its orders up to the given timestamp.
  for (Car *car : cars) {
    car->process_orders(timestamp);
  }
}

// Method to read and process the next order.
bool City::read_order() {
  int nid = (int)orders.size() + 1;           // Calculate the next order ID.
  orders.push_back(Order::create_order(nid)); // Create and add the order.
  // If the last order signals the end, give final orders and process them.
  if (orders.back()->get_time_created() == -1) {
    City::give_orders();
    City::process_orders(1e7); // Process all remaining orders.
    return false;              // Indicate no more orders to read.
  }
  // Process orders up to the time the last order was created.
  City::process_orders(orders.back()->get_time_created());
  return orders.back()->get_time_created() !=
         -1; // Return whether more orders are available.
}

// Method to give instructions to the cars based on current orders.
void City::give_orders() {
  // If no orders or a termination signal is received, do not process further.
  if (City::orders.empty() ||
      City::orders.back()->get_begin_coordinates().first == -1) {
    return;
  }
  // Logic to determine balance points for distributing orders among cars.
  // Continued logic to process and assign orders to the cars.
  static std::vector<std::pair<int, int>> balance_points;

  if (balance_points.empty()) {
    for (Car *car : cars) {
      balance_points.push_back(car->get_coordinates());
    }
  } else {
    balance_points.clear();
    while ((int)cars.size() > (int)balance_points.size()) {
      int x0, y0;
      x0 = rand() % width + 1;
      y0 = rand() % height + 1;
      balance_points.push_back({x0, y0});
    }
  }

  static std::set<Order *> pending;

  pending.clear();
  pending.insert(City::orders.back());

  for (Car *car : cars) {
    car->cut_sequence();
  }

  for (Car *car : cars) {
    car->erase_zero_pay();
    car->shake_sequence();
  }

  std::vector<std::pair<int, std::vector<std::pair<std::pair<int, int>,
                                                   std::pair<Order *, int>>>>>
      out;
  std::vector<int> perm((int)cars.size());

  for (int i = 0; i < (int)cars.size(); i++) {
    perm[i] = i;
  }

  for (Order *q : pending) {
    int best_car = -1;
    double best_val = -inf;

    for (int i : perm) {
      double tmp_val = cars[i]->best_graw_score_after_insert(q, false);
      if (tmp_val > best_val) {
        best_car = i;
        best_val = tmp_val;
      }
    }

    cars[best_car]->best_graw_score_after_insert(q, true);
  }

  for (Car *car : cars) {
    car->erase_zero_pay();
  }

  std::vector<int> best_pt((int)cars.size());
  std::vector<
      std::vector<std::pair<std::pair<int, int>, std::pair<Order *, int>>>>
      mem((int)cars.size());
  std::vector<std::pair<int, int>> p1((int)cars.size());

  for (int i = 0; i < (int)cars.size(); i++) {
    Car *car = cars[i];
    auto ad = car->get_remaining_instructions();
    reverse(ad.begin(), ad.end());
    ad.push_back(
        std::make_pair(car->get_coordinates(), std::make_pair(nullptr, 0)));
    reverse(ad.begin(), ad.end());
    p1[i] = ad.back().first;
    mem[i] = ad;
  }

  std::vector<std::pair<int, int>> matching =
      Algorithm::find_best_matching(p1, balance_points);

  for (std::pair<int, int> ed : matching) {
    best_pt[ed.first] = ed.second;
  }

  for (int i = 0; i < (int)cars.size(); i++) {
    mem[i].push_back(
        std::make_pair(balance_points[best_pt[i]], std::make_pair(nullptr, 0)));
    cars[i]->listen_instruction(mem[i]);
    out.push_back(std::make_pair(i + 1, mem[i]));
  }


}



// Method to calculate the total score for all processed orders.
int City::get_total_score() const {
  double sum = 0;
  // Sum the scores from all cars.
  for (const Car *car : cars) {
    sum += car->get_score();
  }
  // Calculate the average score.
  sum /= (double)(orders.size() - 1);
  return (int)(floor(sum + 0.5)); // Round to the nearest integer.
}

// Variable to keep track of the total number of commands.
int total_cmd_len = 0;

// // Method to print the instructions for a car.
void City::print_instruction(
    int car_id,
    const std::vector<std::pair<std::pair<int, int>, std::pair<Order *, int>>>
        &seq) {

  total_cmd_len += (int)seq.size(); // Update the total command length.

  // Print each instruction in the sequence.
  for (auto pr : seq) {
    // Print action based on whether it's a pickup, drop-off, or other.
    if (pr.second.second == 1) {
      printf("Car %d drives to location (%d, %d) ",car_id, pr.first.first, pr.first.second);
      printf("to pick up order.\n"); 
    } else if (pr.second.second == -1) {
      printf("Car %d drives to location (%d, %d) ",car_id, pr.first.first, pr.first.second);
      printf("to deliver order.\n");
    }
  }
}


 std::vector<std::pair<int, std::vector<std::pair<std::pair<int, int>,
                                                   std::pair<Order *, int>>>>> City::get_instructions() {
  return instructions;
}

std::vector<Car *> City::getCars(){
  return cars;
}


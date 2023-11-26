
#pragma once
#include <iostream>
#include <random>
#include <set>
#include <unordered_map>
#include <utility>


// Forward Decleration for Order Class to resolve cicular dependency
class Order;
// Car Class shows delivery vehicle in the simulation
class Car {
public:
  //  Default Constructors
  Car();
  // // Parameterized constructor to initialize a Car object with commands, accepted orders, and other attributes.
  Car(std::vector<std::pair<std::pair<int, int>, std::pair<Order *, int>>>
          _cmds,
      std::set<Order *> _accepted, int _current_time, int _x, int _y,
      int _current_cmd, double _score);

  // Getter to retrieve the current time in the simulation for this car.
  int get_current_time() const;
  // Getter to retrieve the current coordinates of this car.
  std::pair<int, int> get_coordinates() const;

   // Method to process orders. The logic of how the car handles orders should be implemented here.

  void process_orders(int check_point_time);
  void add_score(double delt_score);
  void listen_instruction(
      std::vector<std::pair<std::pair<int, int>, std::pair<Order *, int>>>
          new_instructions);
  int get_num_of_orders() const;
  std::vector<std::pair<std::pair<int, int>, std::pair<Order *, int>>> getAllInstructions();
  std::vector<std::pair<std::pair<int, int>, std::pair<Order *, int>>>
  get_remaining_instructions() const;
  int get_remaining_instructions_size() const;
  double get_score() const;
  int get_remaining_time() const;
  int get_dist_after_all_orders(int tox, int toy) const;
  int get_dist_after_all_orders(std::pair<int, int> pr) const;
  std::pair<int, int> get_coordinates_after_all_orders() const;
  void cut_sequence();
  double best_graw_score_after_insert(Order *q, bool do_insert);
  void erase_zero_pay();
  double expected_score() const;
  void shake_sequence(); 
  void append_order(Order *q);
  Order *pop_back();
// Private member variables
private:
  bool check_if_last_point();
  void finish_instruction();
  void process(int check_point_time);
  void move(int &x1, int &y1, int x2, int y2, int path_len);
  int get_distance_on_segment(int l, int r, bool from_now) const;
  bool can_swap(int i, int j);

  // Internal variables
  std::vector<std::pair<std::pair<int, int>, std::pair<Order *, int>>>
      instructions;
  std::set<Order *> orders;
  int current_time;
  int x, y;
  int current_instruction;
  double score;
    std::vector<std::pair<std::pair<int, int>, std::pair<Order *, int>>>
      allInstructions;

};

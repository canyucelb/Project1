
#include "Car.h"
#include "Order.h"
#include "Util.h"

// Default constructor initializing the Car object with default values for its member variables.
Car::Car() : current_time(0), x(0), y(0), current_instruction(0), score(0) {
  // Reads the initial x and y coordinates from standard input for the car's location.
  scanf("%d %d", &x, &y);
}

// Parameterized constructor to initialize a Car object with a specific set of instructions, orders, 
// current time, location, and score.
Car::Car(std::vector<std::pair<std::pair<int, int>, std::pair<Order *, int>>>
             _instructions,
         std::set<Order *> _orders, int _current_time, int _x, int _y,
         int _current_instruction, double _score)
    : instructions(_instructions), orders(_orders), current_time(_current_time),
      x(_x), y(_y), current_instruction(_current_instruction), score(_score) {}

// Method to process orders up to a given checkpoint time. It updates the car's state accordingly.
void Car::process_orders(int check_point_time) {
  for (; current_time < check_point_time;) {
    // Process the next order or instruction.
    Car::process(check_point_time);
  }
}


// Getter method to return the current simulation time for this car.
int Car::get_current_time() const { return current_time; }

// Getter method to return the current coordinates of the car as a pair (x, y).
std::pair<int, int> Car::get_coordinates() const {
  return std::make_pair(x, y);
}

// Method to add to the car's score, typically after successfully completing an order.
void Car::add_score(double delt_score) { // 'delt_score' is the delta increase in score.
  score += delt_score;

  { // Update statistics related to the car's performance.
    statistics::how_many_orders[this]++;
    statistics::cnt_of_pay[delt_score]++;
  }
}

// Additional methods implementation for the Car class.

// Method to update the instructions for the car.
void Car::listen_instruction(
    std::vector<std::pair<std::pair<int, int>, std::pair<Order *, int>>>
        new_instructions) {
  instructions = new_instructions;  // Replace current instructions with new ones.
  current_instruction = 0;          // Reset the current instruction index.
}

// Getter method to retrieve the number of orders the car currently has.
int Car::get_num_of_orders() const { 
  return (int)orders.size(); 
}

// Method to get the remaining instructions for the car after the current instruction.
std::vector<std::pair<std::pair<int, int>, std::pair<Order *, int>>>
Car::get_remaining_instructions() const {
  if (current_instruction < (int)instructions.size()) {
    // Return a vector of instructions from the current to the end.
    return std::vector<std::pair<std::pair<int, int>, std::pair<Order *, int>>>(
        instructions.begin() + current_instruction, instructions.end());
  } else {
    // If there are no remaining instructions, return an empty vector.
    return {};
  }
}

std::vector<std::pair<std::pair<int, int>, std::pair<Order *, int>>> Car::getAllInstructions(){
  return allInstructions;
}

// Method to get the number of remaining instructions.
int Car::get_remaining_instructions_size() const {
  // Subtract the current instruction index from the total number of instructions.
  return (int)instructions.size() - current_instruction;
}

// Getter method to return the car's current score.
double Car::get_score() const { 
  return score; 
}

// Method to compute the time remaining for the car to complete its current set of instructions.
int Car::get_remaining_time() const {
  int result = 0;  // Initialize the result counter.
  int cx = x, cy = y;  // Start with the car's current coordinates.

  // Iterate through the remaining instructions.
  for (int nx, ny, i = current_instruction; i < (int)instructions.size(); i++) {
    std::tie(nx, ny) = instructions[i].first; // Get the next instruction's coordinates.
    // Add the distance to the next instruction to the result.
    result += abs(cx - nx) + abs(cy - ny);
    // Update current coordinates to the next instruction's coordinates.
    cx = nx;
    cy = ny;
  }
  return result; // Return the total remaining time.
}


// Method to calculate the distance from the last order's location to a specified location.
int Car::get_dist_after_all_orders(int tox, int toy) const {
  // If there are remaining instructions, calculate distance from the last instruction to the target.
  if (current_instruction < (int)instructions.size()) {
    return Geometry::distance(instructions.back().first, std::make_pair(tox, toy));
  } else {
    // Otherwise, calculate distance from the car's current location to the target.
    return Geometry::distance(x, y, tox, toy);
  }
}

// Overloaded method to calculate distance to a point given as a pair.
int Car::get_dist_after_all_orders(std::pair<int, int> pr) const {
  return Car::get_dist_after_all_orders(pr.first, pr.second);
}


// Method to get the car's coordinates after completing all current orders.
std::pair<int, int> Car::get_coordinates_after_all_orders() const {
  // If there are remaining instructions, return the last instruction's coordinates.
  if (current_instruction < (int)instructions.size()) {
    return instructions.back().first;
  } else {
    // Otherwise, return the car's current coordinates.
    return std::make_pair(x, y);
  }
}


// Method to optimize the instruction sequence by removing unnecessary parts.
void Car::cut_sequence() {
  // If all instructions are processed, reset the instruction set.
  if (current_instruction >= (int)instructions.size()) {
    for(auto i:instructions){
      allInstructions.push_back(i);
    }

    current_instruction = 0;
    instructions.clear();
    return;
  }

  // If there are partially processed instructions, remove processed ones.
  if (current_instruction > 0) {
    for(auto i=instructions.begin(); i<instructions.begin() + current_instruction;i++){
      allInstructions.push_back(*i);
    }

    instructions.erase(instructions.begin(), instructions.begin() + current_instruction);
    current_instruction = 0;
  }

  // Remove trailing instructions with no associated actions.
  while (!instructions.empty() && instructions.back().second.second == 0) {
    instructions.pop_back();
  }
}

// Method to calculate the best score the car can achieve after inserting a new order.
double Car::best_graw_score_after_insert(Order *q, bool do_insert) {
// Implementation logic to calculate the score based on the new order insertion.
  // This includes checking different positions to insert the new order and computing the score
  // for each scenario, then selecting the scenario with the best score.
  if (instructions.empty()) {
    double w0 = q->get_route_distance();
    double d1 = Geometry::distance(Car::get_coordinates(),
                                   q->get_begin_coordinates()); 
    double d2 = 0; 
    double alpha = (1e7 - std::min(d1 * d1 + d2 * d2, 1e7)) / 1e7;
    if (do_insert) {
      instructions.push_back(
          std::make_pair(q->get_begin_coordinates(), std::make_pair(q, +1)));
      instructions.push_back(std::make_pair(q->get_destination_coordinates(),
                                            std::make_pair(q, -1)));
    }
    return alpha * (100 + w0);
  }

  int best_i = (int)instructions.size() - 1;
  int best_j = (int)instructions.size() - 1;
  double best_score = -inf, tmp_score;
  double before = Car::expected_score();

  for (int i = (int)instructions.size() - 1; i >= -1; i--) {
    for (int j = i; j < (int)instructions.size(); j++) {
      instructions.insert(instructions.begin() + j + 1,
                          std::make_pair(q->get_destination_coordinates(),
                                         std::make_pair(q, -1)));
      instructions.insert(
          instructions.begin() + i + 1,
          std::make_pair(q->get_begin_coordinates(), std::make_pair(q, +1)));
      try {
        tmp_score = Car::expected_score() - before;
      } catch (...) {
        tmp_score = -1e9;
      }
      if (tmp_score > best_score) {
        best_score = tmp_score;
        best_i = i;
        best_j = j;
      }
      instructions.erase(instructions.begin() + j + 2);
      instructions.erase(instructions.begin() + i + 1);
    }
  }

  if (do_insert) {
    instructions.insert(instructions.begin() + best_j + 1,
                        std::make_pair(q->get_destination_coordinates(),
                                       std::make_pair(q, -1)));
    instructions.insert(
        instructions.begin() + best_i + 1,
        std::make_pair(q->get_begin_coordinates(), std::make_pair(q, +1)));
  }

  return best_score;
}
// Method to remove orders from the instruction set that do not contribute to the score.
void Car::erase_zero_pay() {
   // Implementation logic to identify and remove orders that have zero or negligible pay.
  if (current_instruction != 0)
    throw -1;
  std::vector<int> pos;
  for (int i = 0; i < (int)instructions.size(); i++) {
    if (Car::orders.count(instructions[i].second.first)) {
      continue;
    }
    if (instructions[i].second.second != +1)
      continue;
    int j = -1;
    for (int z = i + 1; z < (int)instructions.size(); z++) {
      if (instructions[z].second.second == -1 &&
          instructions[z].second.first == instructions[i].second.first) {
        j = z;
        break;
      }
    }
    if (j == -1)
      throw -1;
    int arrival_time =
        Car::get_current_time() + Car::get_distance_on_segment(0, i, true);
    int time_on_road = Car::get_distance_on_segment(i, j, false);
    if (abs(instructions[i].second.first->get_cost(arrival_time,
                                                   time_on_road)) <= 1e-8) {
      pos.push_back(i);
      pos.push_back(j);
    }
  }
  sort(pos.begin(), pos.end());
  reverse(pos.begin(), pos.end());

  for (int i : pos) {
    instructions.erase(instructions.begin() + i);
  }
}
// Method to calculate the expected score for the current set of instructions.
double Car::expected_score() const {
// Implementation logic to calculate the expected score based on the current instructions.
  int glob_capacity = 4 - Car::get_num_of_orders();
  int globx, globy;
  std::tie(globx, globy) = Car::get_coordinates();
  double glob_score = Car::get_score();
  int glob_time = Car::get_current_time();
  std::unordered_map<Order *, int> glob_start_time, glob_waiting_time;

  for (Order *q : Car::orders) {
    glob_start_time[q] = q->get_start_time();
    glob_waiting_time[q] = q->get_wait_time();
  }

  for (int i = 0; i < (int)instructions.size(); i++) {
    { 
      glob_time += Geometry::distance({globx, globy}, instructions[i].first);
      std::tie(globx, globy) = instructions[i].first;
      if (instructions[i].second.second == -1) {
        glob_capacity++;
        if (glob_capacity > 4)
          throw -1;
        { 
          double w0 = instructions[i].second.first->get_route_distance();
          double d1 = glob_waiting_time[instructions[i].second.first];
          double d2 =
              (glob_time - glob_start_time[instructions[i].second.first]) - w0;
          double alpha = (1e7 - std::min(d1 * d1 + d2 * d2, 1e7)) / 1e7;
          double ad_score = alpha * (100 + w0);
          glob_score += ad_score;
        }
      } else if (instructions[i].second.second == +1) {
        if (glob_capacity <= 0)
          throw -1;
        glob_capacity--;
        glob_start_time[instructions[i].second.first] = glob_time;
        glob_waiting_time[instructions[i].second.first] =
            glob_time - instructions[i].second.first->get_time_created();
      }
    }
  }

  return glob_score;
}
// Additional methods such as `shake_sequence`, `append_order`, `pop_back`, and `can_swap` are also 
// implemented in this section. Each of these methods plays a specific role in managing the car's 
// instructions and optimizing the order sequence.
void Car::shake_sequence() {
  if ((int)instructions.size() < 2)
    return;
  static std::mt19937 rnd(37);
  double current_score = Car::expected_score();
  for (int any, iter = 0; iter < 200; iter++) {
    any = 0;
    for (int it = 0; it < 5 * (int)instructions.size(); it++) {
      int i = rnd() % ((int)instructions.size() - 1);
      int j = i + rnd() % ((int)instructions.size() - i - 1) + 1;
      if (Car::can_swap(i, j)) {
        swap(instructions[i], instructions[j]);
        double tmp_score = -1e9;
        try {
          tmp_score = Car::expected_score();
        } catch (...) {
          tmp_score = -1e9;
        }
        if (tmp_score > current_score) {
          any = 1;
          current_score = tmp_score;
        } else {
          swap(instructions[i], instructions[j]);
        }
      }
    }
    if (!any)
      break;
  }
}

void Car::append_order(Order *q) {
  Car::instructions.push_back(
      std::make_pair(q->get_begin_coordinates(), std::make_pair(q, +1)));
  Car::instructions.push_back(
      std::make_pair(q->get_destination_coordinates(), std::make_pair(q, -1)));
}

Order *Car::pop_back() {
  if ((int)instructions.size() > 2 &&
      current_instruction + 2 < (int)instructions.size()) {
    int sz = (int)instructions.size();
    if (instructions[sz - 2].second.first ==
        instructions[sz - 1].second.first) {
      Order *q = instructions[sz - 1].second.first;
      instructions.pop_back();
      instructions.pop_back();
      return q;
    } else {
      return nullptr;
    }
  } else {
    return nullptr;
  }
}

bool Car::can_swap(int i, int j) {

  if (0 <= i && i < j && j < (int)instructions.size()) {
  } else
    return false;
  int capacity = Car::get_num_of_orders();
  swap(instructions[i], instructions[j]);
  int ok = 1;
  for (int jj = 0; jj < (int)instructions.size(); jj++) {
    if (instructions[jj].second.second == 1) {
      if (capacity <= 0) {
        ok = 0;
        break;
      } else {
        capacity--;
      }
    } else if (instructions[jj].second.second == -1) {
      capacity++;
    }
  }
  if (!ok) {
    swap(instructions[i], instructions[j]);
    return false;
  }
  for (int w = 0; w < (int)instructions.size(); w++) {
    if (instructions[w].second.second != +1)
      continue;
    int hm = 0;
    for (int z = w + 1; z < (int)instructions.size(); z++) {
      if (instructions[z].second.second == -1 &&
          instructions[z].second.first == instructions[w].second.first) {
        hm = 1;
        break;
      }
    }
    if (!hm) {
      swap(instructions[i], instructions[j]);
      return false;
    }
  }
  swap(instructions[i], instructions[j]);
  return true;
}

bool Car::check_if_last_point() {
  return (current_instruction < (int)instructions.size() &&
          instructions[current_instruction].first == get_coordinates());
}


void Car::finish_instruction() {
    Order *q = instructions[current_instruction].second.first;
    if (instructions[current_instruction].second.second == 1) {
        orders.insert(q);
        q->take_order(this);
    } else if (instructions[current_instruction].second.second == -1) {
        orders.erase(q);
        q->deliver(this);
    }

}
 
void Car::process(int check_point_time) {
  while (current_instruction < (int)instructions.size()) {
    if (instructions[current_instruction].second.second == 1) {
      Order *q = instructions[current_instruction].second.first;

      if (q->get_status() == Order::STATUS::PENDING) {
        q->set_car();
      }
    }

    int remaining_path_len = Geometry::distance(
        Car::get_coordinates(), instructions[current_instruction].first);
    if (Car::get_current_time() + remaining_path_len <= check_point_time) {
      Car::move(x, y, instructions[current_instruction].first.first,
                instructions[current_instruction].first.second,
                remaining_path_len);
      current_time += remaining_path_len;
      finish_instruction();
      current_instruction++;
    } else {
      Car::move(x, y, instructions[current_instruction].first.first,
                instructions[current_instruction].first.second,
                check_point_time - Car::get_current_time());
      current_time += check_point_time - Car::get_current_time();
      break;
    }
  }

  current_time = check_point_time;
}

void Car::move(int &x1, int &y1, int x2, int y2, int path_len) {

  //int dist_after = Geometry::distance(x1, y1, x2, y2) - path_len;

  if (path_len <= Geometry::distance(x1, y1, x2, y1)) {
    if (x1 < x2) {
      x1 += path_len;
    } else {
      x1 -= path_len;
    }
  } else {
    path_len -= Geometry::distance(x1, y1, x2, y1);
    x1 = x2;
    if (y1 < y2) {
      y1 += path_len;
    } else {
      y1 -= path_len;
    }
  }

    
}

int Car::get_distance_on_segment(int l, int r, bool from_now) const {
  int result = 0;
  if (from_now) {
    result += Geometry::distance(Car::get_coordinates(), instructions[l].first);
  }
  for (int i = l; i < r; i++) {
    result +=
        Geometry::distance(instructions[i].first, instructions[i + 1].first);
  }
  return result;
}

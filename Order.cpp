#include "Order.h"
#include "Car.h"
#include "Util.h"

#include <iostream>
#include <random>
#include <set>
#include <unordered_map>
#include <utility>

// Copy constructor for Order class.
Order::Order(Order *other)
    : status(other->status), begin_x(other->begin_x), begin_y(other->begin_y),
      destination_x(other->destination_x), destination_y(other->destination_y),
      time_created(other->time_created), start_time(other->start_time),
      finish_time(other->finish_time), wait_time(other->wait_time),
      id(other->id) {}

// Method to create a new Order object with a specific ID.
Order *Order::create_order(int _id) {
  Order *res = new Order(); // Create a new Order instance.
  res->id = _id;            // Set the Order's ID.
  res->read();              // Read the Order's details from input.
  return res;               // Return the newly created Order object.
}

// Getter methods for various properties of the order.
int Order::get_time_created() const { return time_created; }
std::pair<int, int> Order::get_begin_coordinates() const { return std::make_pair(begin_x, begin_y); }
std::pair<int, int> Order::get_destination_coordinates() const { return std::make_pair(destination_x, destination_y); }

// Method to handle the order being taken by a car.
void Order::take_order(Car *car) {
  start_time = car->get_current_time(); // Record the start time as the current time of the car.
  wait_time = start_time - time_created; // Calculate wait time.
  status = Order::STATUS::ON_THE_WAY; // Update the order status.
}

// Method to handle the delivery of the order.
void Order::deliver(Car *car) {
  finish_time = car->get_current_time(); // Record the finish time as the current time of the car.
  car->add_score(Order::calculate_score()); // Add the calculated score for this order to the car.
  status = Order::STATUS::DELIVERED; // Update the order status.
  update_statistics(); // Update order-related statistics.
}

// Method to mark the order as assigned to a car.
void Order::set_car() {
  status = Order::STATUS::ASSIGNED_TO_CAR; // Update the order status.
}

// Getter methods for other properties and calculations related to the order.
Order::STATUS Order::get_status() const { return status; }
int Order::get_id() const { return id; }
int Order::get_route_distance() const { return Geometry::distance(begin_x, begin_y, destination_x, destination_y); }

 // Calculate the cost of the order based on arrival time and time on the road.
double Order::get_cost(int arrival_time, int time_on_road) const {
  double distance = Order::get_route_distance();
  double d1 = arrival_time - Order::get_time_created();
  double d2 = time_on_road - distance;
  double alpha = (1e7 - std::min(d1 * d1 + d2 * d2, 1e7)) / 1e7;
  return alpha * (100 + distance);
}

int Order::get_start_time() const { return Order::start_time; }

int Order::get_wait_time() const { return Order::wait_time; }

// Method to calculate the score of the order based on various factors like wait time and distance.
double Order::calculate_score() const {
  // Implementation of score calculation logic.
  double w0 = Order::get_route_distance();
  double d1 = wait_time;
  double d2 = (finish_time - start_time) - w0;
  double alpha = (1e7 - std::min(d1 * d1 + d2 * d2, 1e7)) / 1e7;
  return alpha * (100 + w0);
}
// Method to read order details from input.
void Order::read() {
  scanf("%d %d %d %d %d", &time_created, &begin_x, &begin_y, &destination_x,
        &destination_y);
}
// Method to update statistical data related to orders.
void Order::update_statistics() {
  // Implementation of statistical data update logic.
  statistics::cnt_processed_queries++;

  statistics::max_w0 =
      std::max(statistics::max_w0, Order::get_route_distance());
  statistics::min_w0 =
      std::min(statistics::min_w0, Order::get_route_distance());
  statistics::sum_w0 += Order::get_route_distance();

  statistics::max_wait = std::max(statistics::max_wait, Order::wait_time);
  statistics::min_wait = std::min(statistics::min_wait, Order::wait_time);
  statistics::sum_wait += Order::wait_time;

  statistics::max_pay =
      std::max(statistics::max_pay, (int)Order::calculate_score());
  statistics::min_pay =
      std::min(statistics::min_pay, (int)Order::calculate_score());
  statistics::sum_pay += Order::calculate_score();
}
#pragma once

#include <utility>

// Forward declaration of Car class to use it as a reference.
class Car;

// Order class represents a single delivery order in the simulation.
class Order {
public:
  // Enumeration of possible states of an order during the simulation.
  enum STATUS { 
    PENDING,          // Order not picked up yet and not assigned to a car.
    ON_THE_WAY,       // Order is currently being delivered.
    DELIVERED,        // Order has been delivered.
    ASSIGNED_TO_CAR   // Order is assigned to a car but not picked up yet.
  };

  // Default constructor.
  Order() = default;

  // Copy constructor.
  Order(Order *other);

  // Static method to create a new order with a given id.
  static Order *create_order(int id);

  // Getters for various properties of the order.
  STATUS get_status() const;
  std::pair<int, int> get_begin_coordinates() const;
  std::pair<int, int> get_destination_coordinates() const;
  int get_time_created() const;
  int get_start_time() const;
  int get_finish_time() const;
  int get_wait_time() const;
  int get_id() const;

  // Helper function to calculate the route distance for this order.
  int get_route_distance() const;

  // Compute the cost of the order based on arrival and travel times.
  double get_cost(int arrival_time, int time_on_road) const;

  // Methods to process the order, like taking and delivering the order, and assigning it to a car.
  void take_order(Car *car);
  void deliver(Car *car);
  void set_car();

private:
  // Internal method to calculate the score for this order.
  double calculate_score() const;

  // Method to read the order information from input.
  void read();

  // Method to update the statistics after order processing.
  void update_statistics();

  // Member variables to store the details and state of the order.
  STATUS status;
  int begin_x, begin_y;                 // Pickup coordinates.
  int destination_x, destination_y;     // Drop-off coordinates.
  int time_created;                     // Timestamp when the order was created.
  int start_time;                       // Timestamp when the order was picked up.
  int finish_time;                      // Timestamp when the order was delivered.
  int wait_time;                        // Time the customer waited for the pickup.
  int id;                               // Unique identifier for the order.
};

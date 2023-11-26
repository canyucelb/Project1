#pragma once

#include <utility>
#include <vector>

// Forward declarations to make the Car and Order classes known to City.h without including their headers.
class Car;
class Order;

// The City class represents the simulation space where cars operate and orders are processed.
class City {
public:
  // Constructor to create a city with given dimensions and number of cars.
  City(int width, int height, int numCars);

  // Method to process orders at a given timestamp.
  void process_orders(int timestamp);

  // Method to read the next order from the input. Returns true if an order is read successfully.
  bool read_order();

  // Method to give instructions to the cars based on current and pending orders.
  void give_orders();

  // Getter method to calculate and return the total score of all processed orders.
  int get_total_score() const;

 std::vector<std::pair<int, std::vector<std::pair<std::pair<int, int>,
                                                   std::pair<Order *, int>>>>>
  get_instructions();    

  // Method to print the instruction sequence for a car with a given id.
  void print_instruction(
      int id,
      const std::vector<std::pair<std::pair<int, int>, std::pair<Order *, int>>>
          &seq);

  std::vector<Car *> getCars();


private:
  

  // Internal variables to store the width and height of the city grid.
  int width;
  int height;

  // Vector to store pointers to Car objects representing the cars in the city.
  std::vector<Car *> cars;

  // Vector to store pointers to Order objects representing the orders in the city.
  std::vector<Order *> orders;

   std::vector<std::pair<int, std::vector<std::pair<std::pair<int, int>,
                                                   std::pair<Order *, int>>>>> instructions;
  
};

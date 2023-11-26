#include <iostream>
#include <random>
#include <set>
#include <unordered_map>

#include "City.h"
#include "Car.h"
#include "Util.h"

// The main function - entry point of the program.
int main() {
  int width, height, numCars;
  // Read the dimensions of the city and the number of cars from the standard input.
  scanf("%d %d %d", &width, &height, &numCars);

  // Create a City object with the specified dimensions and number of cars.
  City city(width, height, numCars);
  // Initially give orders to cars based on the starting scenario.
  city.give_orders();

  printf("\n - Welcome ! - \n");
  printf("\n  **State College Food Optimization Service (SCFOS)**  \n");

  // Main simulation loop: continue reading and processing orders until there are no more.
  while (true) {
    // Read the next order, and if there are no more orders, exit the loop.
    if (!city.read_order()) {
      break;
    }
    // Give new orders to cars after each order is read.
    city.give_orders();
  }


  auto cars = city.getCars();
  for(int i=0;i<(int)cars.size();i++){
    cars[i]->cut_sequence();
  }

  for(int i=0;i<(int)cars.size();i++){
    printf("Instructions assigned to car %d:\n",i+1);
    auto instr = cars[i]->getAllInstructions();
    city.print_instruction(i+1, instr);
  }


  // Output statistics collected during the simulation.
  statistics::output_statistics();
  
  // End of the program.
  return 0;
}

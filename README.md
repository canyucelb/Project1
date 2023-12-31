# State College Food Optimization Service (SCFOS)

## Overview

SCFOS is an interactive optimization solution designed to automate and optimize food delivery services. The system manages a fleet of delivery cars, each capable of processing multiple food orders simultaneously, ensuring efficient routing and customer satisfaction.

## Features

- Simulates a city grid for food delivery.
- Each car can deliver up to four orders simultaneously.
- Dynamic order processing based on efficiency.
- Statistical output for performance analysis.

## Requirements

- C++ Compiler (C++14 standard or later)
- Make (for building the project using the provided Makefile)

## Compilation and Running

Ensure you have a C++ compiler installed and configured on your system.

To compile the project, navigate to the `src` directory and use the Makefile:

cd src
make clean  # Cleans previous builds
make        # Compiles the project

This will generate the executable `main` which you can run with:

./main < tests/testfile

Replace `testfile` with the name of your test input file.

## Input Formatand Description

The SCFOS program expects the input to be structured as follows:

### 1. City Grid Dimensions:

First line contains <w> <h>, representing the width and height of the city grid.

### 2. Number of Cars:

Second line specifies <k>, the number of cars available for delivery.

### 3.Initial Car Locations:

The next k lines detail the initial coordinates of each car in <x> <y> format.

### 4. Order Details:

Subsequent lines are formatted as <tj> <sxj> <syj> <txj> <tyj> for each order, indicating the moment of order tj, pickup location (sxj, syj), and drop-off location (txj, tyj).

## Output Description

Upon completing the simulation, the SCFOS program generates two main types of outputs:

### 1. Instruction Sets for Cars

#### Detailed Navigation: 

Each car receives a set of instructions outlining its journey through the city grid. This includes sequential actions such as moving to specific coordinates for pickups and deliveries.

#### Order Handling: 

The instructions detail the order in which each car will handle pickups and drop-offs, ensuring optimal route planning and time management.

#### Dynamic Adaptation: 

As new orders come in, the instruction sets are dynamically updated to reflect the most efficient routes and actions at that moment.

### 2. Statistical Data and Performance Metrics

#### Order Processing Summary: 

This includes the total number of orders processed, any failed orders, and the average number of orders handled per car.

#### Distance Metrics: 

The program calculates and displays the total distance covered by all cars, average distance per car, and the maximum/minimum distance covered by any single car.

#### Time Efficiency Analysis: 

This includes metrics like the total wait time for all orders, average wait time per order, and the longest/shortest wait times experienced by any order.

#### Financial Overview: 

The output provides details about the total payment received, average payment per order, and the highest/lowest payment received for individual orders.

#### Visual Representation (Optional): 

UPCOMING! (the program will provide a visual representation of car movements and order processing on the city grid)

## Testing

The `tests/` directory contains test files that can be used to run simulations and assess the performance of the delivery system.

## License

TBA (Probably MIT)

## Contribution

TBA

## Authors

- Baran Can Yucel 

## Acknowledgments

- Thank you very much for Dr. Thanakorn Khamvilai for his continuous support to this project during Fall23 Semester for AERSP-424 Course Project


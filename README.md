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

```sh
cd src
make clean  # Cleans previous builds
make        # Compiles the project

This will generate the executable `main` which you can run with:

./main < tests/testfile

Replace `testfile` with the name of your test input file.

## Input Format
The program expects input in the following format:
- First line: `<w> <h>` (width and height of the city grid)
- Second line: `<k>` (number of cars)
- Next `k` lines: `<x> <y>` (initial coordinates of each car)
- Subsequent lines: `<tj> <sxj> <syj> <txj> <tyj>` (order details with moment of order `tj`, pickup location `(sxj, syj)`, and drop-off location `(txj, tyj)`)

## Output
The program outputs the instruction sets for cars and statistical data after processing all orders.

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


# Genetic Algorithm for Ackley Function Optimization

This project implements a Genetic Algorithm (GA) to minimize the Ackley function, a well-known optimization problem. The GA is a heuristic search and optimization algorithm inspired by the process of natural selection.

## Objective

The goal of this assignment is to develop a basic genetic algorithm approach to minimize the Ackley function. The Ackley function is characterized by having two variables, x1 and x2, and the objective is to find the optimal solution that minimizes the function.

## Ackley Function

The Ackley function is chosen due to its simplicity and suitability for evaluating the efficiency of the developed GA program.

## Getting Started

1. Download all the necessary files from the provided GitHub repository.
2. Run the makefile for different population sizes and max generations.
3. Examine results.

### Mutation

Mutation is a crucial component of the GA, involving a random alteration of an individual's genetic code. It introduces diversity by making small changes in the solution space. The mutation rate controls the probability of mutation for each gene.

### Crossover (Recombination)

Crossover involves the exchange of genetic material between two parents to create offspring. The specific crossover method determines how this exchange occurs. For example, one-point crossover selects a random point in the genetic code, swapping segments of the parents' genetic code to create two offspring. Two-point crossover involves selecting two random points for the exchange.

## Termination Criteria

The GA terminates when a given number of iterations is reached or when a solution is found – an individual with a certain fitness.

## Running the Program

Execute the provided GA program to observe its evolution in minimizing the Ackley function. Analyze the results and compare them with the known optimal solution obtained from the visual analysis of the Ackley function.

## Dependencies

- Being able to run a C program.

## Acknowledgments

This project was part of a foundational C programming course at McMaster University.

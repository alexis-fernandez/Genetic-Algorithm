// Include everything necessary here 
#include <stdio.h>
#include <stdlib.h> //header needed for srand() and rand()
#include <time.h> //header needed for time()
#include "functions.h"
#include <math.h> //header needed for absolute value of doubles
#include <float.h> //header needed for DBL_MAX


int main(int argc, char *argv[])
{
    printf("Genetic Algorithm is initiated.\n");
    printf("------------------------------------------------\n");
    printf("The number of variables: 2\n");
    printf("Lower bounds: [-5.000000, -5.000000]\n");
    printf("Upper bounds: [ 5.000000,  5.000000]\n");
    printf("\n");

    srand((unsigned int)time(NULL));


    // <YOUR CODE: Assign all inputs given by the user argv[i]> like
    // POPULATION_SIZE, MAX_GENERATIONS, crossover_rate, mutate_rate, stop_criteria
    
    int POPULATION_SIZE = atoi(argv[1]);
    int MAX_GENERATIONS = atoi(argv[2]);
    double crossover_rate = atof(argv[3]);
    double mutate_rate = atof(argv[4]);
    double stop_criteria = atof(argv[5]);

    // <YOUR CODE: Handle the possible errors in input data given by the user and say how to execute the code>
    if (argc != 6)
    {
        printf("Usage: %s POPULATION_SIZE MAX_GENERATIONS crossover_rate mutate_rate stop_criteria\n", argv[0]);
    }
    if (POPULATION_SIZE <= 0 || MAX_GENERATIONS <= 0 || crossover_rate < 0 || mutate_rate < 0 || stop_criteria < 0)
    {
        printf("Inavlid input. Please provide positive values.\n");
    }

    // ###################################################################################
    // you dont need to change anything here
    // the number of variables
    int NUM_VARIABLES = 2;
    // the lower bounds of variables
    double Lbound[] = {-5.0, -5.0};
    // the upper bounds of variable
    double Ubound[] = {5.0, 5.0};
    // ###################################################################################


    // <YOUR CODE: Here make all the initial print outs>
    printf("Population Size: %d\n", POPULATION_SIZE);
    printf("Max Generations: %d\n", MAX_GENERATIONS);
    printf("Crossover Rate: %f\n", crossover_rate);
    printf("Mutation Rate: %f\n", mutate_rate);
    printf("Stopping Criteria: %.16f\n", stop_criteria);
    printf("\n");
    printf("Results\n");
    printf("------------------------------------------------\n");
    

    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();

    // <YOUR CODE: Declare all the arrays you need here>
    double population[POPULATION_SIZE][NUM_VARIABLES];
    double new_population[POPULATION_SIZE][NUM_VARIABLES];
    double fitness[POPULATION_SIZE];

    // <YOUR CODE: Call generate_population function to initialize the "population"> like:
    generate_population(POPULATION_SIZE, NUM_VARIABLES, population, Lbound, Ubound);


    double best_solution[NUM_VARIABLES];     //stores the genes that give the best fitness value (the best solution to the Akley function)
    //double prev_min_fitness = DBL_MAX / 2.0;    //initializing to non-reachable value
    double current_min_fitness = DBL_MAX / 2.0;    //initializing to non-reachable value 
    

    // iteration starts here. The loop continues until MAX_GENERATIONS is reached
    // Or stopping criteria is met
    for (int generation = 0; generation < MAX_GENERATIONS; generation++)
    {
        // <YOUR CODE: Compute the fitness values using objective function for
        // each row in "population" (each set of variables)> like:
        compute_objective_function(POPULATION_SIZE, NUM_VARIABLES, population, fitness);

        // <YOUR CODE: Here implement the logic of finding best solution with minimum fitness value
        // and the stopping criteria>

        
        //Whenever the minimum fitness value is found, the best solution is stored in best_solution
        for (int i = 0; i < POPULATION_SIZE; i++)
        {
            if (fitness[i] < current_min_fitness)
            {
                current_min_fitness = fitness[i];
                for (int j = 0; j < NUM_VARIABLES; j++)
                {
                    best_solution[j] = population[i][j];
                }
            }
        }

        if (current_min_fitness < stop_criteria)   //if the current minimum fitness is less than the stopping criteria, the criteria is met before MAX_GENERATIONS (break out of for loop)
        {
            printf("The stop criteria was met before MAX_GENERATIONS was met \n");
            break;
        }


        

        // <YOUR CODE: Here call the crossover function>
        crossover(POPULATION_SIZE, NUM_VARIABLES, fitness, new_population, population, crossover_rate);

        // <YOUR CODE: Here call the mutation function>
        mutate(POPULATION_SIZE, NUM_VARIABLES, new_population, population, Lbound, Ubound, mutate_rate);
        
        // Now you have the a new population, and it goes to the beginning of loop to re-compute all again
        printf("Current Generation: %d\n",generation);
    }

    
    

    // ###################################################################################
    // You dont need to change anything here
    // Here we print the CPU time taken for your code
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU time: %f seconds\n", cpu_time_used);
    // ###################################################################################

    // <YOUR CODE: Jump to this part of code if the stopping criteria is met before MAX_GENERATIONS is met>

    

    // <Here print out the best solution and objective function value for the best solution like the format>

    printf("Best solution found: ");
    for (int j = 0; j < NUM_VARIABLES; j++)
    {
        printf("%.16f ", best_solution[j]);
    }
    printf("\n");

    printf("Best fitness: %.16f\n", current_min_fitness);


    return 0;
}

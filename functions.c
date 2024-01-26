// Include everything necessary here 
#include <stdio.h>
#include <stdlib.h> //header needed for srand() and rand()
#include "functions.h"


double generate_random(double min, double max)
{
    // implement a function to return a value between min and max

    //Generating a random double value between the min and max
    return ((double)rand()/(double) RAND_MAX)*(max-min) + min;    
}

unsigned int generate_int()
{
    // implement the function to return a random integer value
    return (unsigned int)rand();
    
}

// Function to initialize a random population
void generate_population(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES])
{
    // randomly initialize for all values in "population[i][j]""

    //In order to generate a population 2D array, we can iterate over each of the rows (POPULATION_SIZE) and the columns (NUM_VARIABLES) and generate a random double value between the given min and max
    //This us a 2D array of the population filled with random double values within the specified range
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUM_VARIABLES; j++)
        {
            population[i][j] = generate_random(Lbound[j],Ubound[j]);
        }
    }
}

// Function to compute the objective function for each member of the population
void compute_objective_function(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double fitness[POPULATION_SIZE])
{
    /* compute "fitness[i]"" for each set of decision variables (individual) or each row in "population"
    by calling "Objective_function" */

    //Iterating through every member and calling the objective function with each individual's variables and storing the result in the fitness array
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        fitness[i] = Objective_function(NUM_VARIABLES, population[i]);   //population[i] represents each member and NUM_VARIABLES represents that individual's variables
    }
}

void crossover(int POPULATION_SIZE, int NUM_VARIABLES, double fitness[POPULATION_SIZE], double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double crossover_rate)
{
    /* Implement the logic of crossover function here based on "fitness_probs" or each set
    of decision variables (individual) or each row in "population".
    And save the new population in "new_population"*/

    //Adding all the computed fitness values in order to get the fitness probability in a later step
    double fitness_sum = 0.0;
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        fitness_sum += fitness[i];
    }

    //Now that we know the total sum of fitness values, the probability for each fitness value can be calculated by dividing each individual fitness value by the total
    double fitness_probs [POPULATION_SIZE];
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        fitness_probs[i] = fitness[i]/fitness_sum;
    }

    ///////////////////////Selecting parents to crossover based on their probabilities/////////////////////////////

    //In order to have a weighted random selection of the parents based on their probabilities, a cumulative probability is required
    double cumulative_prob [POPULATION_SIZE];
    cumulative_prob[0] = fitness_probs[0];      //Setting the intial case
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        cumulative_prob[i] = cumulative_prob[i-1]+fitness_probs[i];   //Adding the fitness probabilities up to that index to each specified index
    }


    //Selecting random parents
    int reference[POPULATION_SIZE];    // a reference list to index
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        double random_selector = generate_random(0,1);    //Generating random double with bounds [0,1] (in the bounds of fitness_probs)
        double random_parent = generate_random(0, POPULATION_SIZE);
        if (cumulative_prob[i] < random_selector && random_selector < cumulative_prob[i+1])   //If random number (between 0 and 1) is greater than the cumulative probability at that index and less than the cummulative at the next index, at the index to reference. This allows for indices with higher proabilities to be more likely to become parents
        {
            reference[i] = i;
        }

        else
        {
            reference[i] = random_parent;    //If not a chosen parent,choose a random parent from the ones available
        }
    }

    for (int i = 0; i < POPULATION_SIZE; i++)   //FIlling new population array
    {
        for (int j = 0; j < NUM_VARIABLES; j++)
        {
            new_population[i][j] = population[reference[i]][j];   
        }
    }
    


    for (int i = 0; i < POPULATION_SIZE; i+=2)   //Iterating every two indices (every two parents)
    {
        double random_selector = generate_random(0,1); 

        if (random_selector < crossover_rate)
        {
            //Creating the arrays for the two parents of the size of the number of columns for each row in population
            double parent1 [NUM_VARIABLES];
            double parent2 [NUM_VARIABLES];

            //Copying the the genes from the new population array to the parents
            for (int j = 0; j < NUM_VARIABLES; j++)
            {
                parent1[j] = new_population[i][j];
                parent2[j] = new_population[i+1][j];    //The second parent would be the one that is one row below the first one
            }

            int crosspoint = generate_int() % (NUM_VARIABLES - 1) + 1; //Generating a random integer between the second column and the second last column of the parents array

            //Creating the two new children
            double child1 [NUM_VARIABLES];
            double child2 [NUM_VARIABLES];

            //Giving the children the same genes as the parents up to the crosspoint generated and then switching between parents for both children
            for (int j = 0; j < crosspoint; j++)   
            {
                //Cutting the parent's gens at the crosspoint for both children and then swapping with the next for loop
                child1[j] = parent1[j];
                child2[j] = parent2[j];
            }

            for (int j = crosspoint; j < NUM_VARIABLES; j++)
            {
                child1[j] = parent2[j];
                child2[j] = parent1[j];
            }

            //Replacing the parents with the new children
            for (int j = 0; j < NUM_VARIABLES; j++)
            {
                new_population[i][j] = child1[j];
                new_population[i+1][j] = child2[j];
            }
        }
    }
}

void mutate(int POPULATION_SIZE, int NUM_VARIABLES, double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES], double mutate_rate)
{
    /*Implement the logic of mutation on "new_population" and then copy everything into "population"*/

    int total_gen = NUM_VARIABLES*POPULATION_SIZE;      //Calculating the number of total genes
    //int random_int = generate_int() % total_gen + 1;    //Generating random int between 1 and total_gen

    int total_gen_mutate = total_gen*mutate_rate;       //Calculating the number of genes that will be mutated
    
    
    for (int i = 0; i < total_gen_mutate; i++)          //This loop will run for the number of times mutation was determined to occur
    {
        //For the number of total genes that will mutate, a random individual and gene will be selected and that specific gene of that individual will the mutate to a value within the specified bounds
        int random_chromosome = rand() % POPULATION_SIZE;
        int random_gene = rand() % NUM_VARIABLES;

        new_population[random_chromosome][random_gene] = generate_random(Lbound[NUM_VARIABLES], Ubound[NUM_VARIABLES]);
    }
    
    for (int i = 0; i < POPULATION_SIZE; i++)  //Copyiing everything into the population array
    {
        for (int j = 0; j < NUM_VARIABLES; j++)
        {
            population[i][j] = new_population[i][j];
        }
    }

    
}
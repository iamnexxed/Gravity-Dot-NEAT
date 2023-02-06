#include "NeuroEvolution.h"

void NeuroEvolution::Initiate() {
    // Create a new random population 
}


void NeuroEvolution::Mutate() {

    // Perform mutation for all the genomes
       

}

void NeuroEvolution::Speciate() {
    // For each genome in global genomes
        // For each species in this->species
            // if the genome is compatible with the species
                // Add the genome to the species
                // return
        
        // Otherwise
        // Create a new species 
        // Append the genome to the species
        // Make the genome as it's representative

        // Calculate the shared fitness for the genome wrt other genomes

}

void NeuroEvolution::CrossOver() {
    // Remove a percentage of population from from the total based on the fitness
    // For every species
        // Loop till population is recovered for that species
            // Select two available parents randomly
            // Create a new offspring through crossover
            // Mutate the offspring
    
}
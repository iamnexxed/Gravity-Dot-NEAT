#ifndef NEUROEVOLUTION_CLASS_H
#define NEUROEVOLUTION_CLASS_H

#include <vector>
#include "Species.h"
#include "NeuralNetwork.h"

// Initial Neural Network configuration
const int INPUTCOUNT = 4;
const int OUTPUTCOUNT = 1;

class NeuroEvolution {
    private:
        // Species Array
        std::vector<Species*> speciesArray;

    public:

       // Maximum generations allowed
        const int maxGenerations = 100;

        // Total Population
        const int populationSize = 100;

        // Genomes Array
        std::vector<Genome*> genomes;

        float meanAdjustedFitness = 0.0f;

        bool SetGenomeFitness( int index, float fitness );
    
        // Initiate a population
        void Initiate();

        // Mutation
        void Mutate();
        
        // Crossover
        void CrossOver();
        
        // Speciation
        void Speciate();

        ~NeuroEvolution();
};

#endif


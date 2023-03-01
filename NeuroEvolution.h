#ifndef NEUROEVOLUTION_CLASS_H
#define NEUROEVOLUTION_CLASS_H

#include <vector>
#include "Species.h"
#include "NeuralNetwork.h"

class NeuroEvolution {
    private:
        // Species Array
        std::vector<Species*> speciesArray;
        void clearSpecies();
        void clearGenomes();

    public:

       // Maximum generations allowed
        const int maxGenerations = 100;

        // Total Population
        const int populationSize = 100;

        // Initial Neural Network configuration
        const int INPUTCOUNT = 6;
         
        const int OUTPUTCOUNT = 1;

        const int MAXGENS = 100;

        const char* SAVE_PATH = "Data/";

        // Genomes Array
        std::vector<Genome*> genomes;

        float meanAdjustedFitness = 0.0f;

        int currentGeneration = 0;

        bool SetGenomeFitness( int index, float fitness );
    
        // Initiate a population
        void Initiate();

        // Mutation
        void Mutate();
        
        // Crossover
        void CrossOver();
        
        // Speciation
        void Speciate();

        void SaveGenomesToJSON();

        ~NeuroEvolution();
};

#endif


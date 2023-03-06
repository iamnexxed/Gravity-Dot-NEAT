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
        // Total Population
        const int populationSize = 20;

        // Initial Neural Network configuration
        const int INPUTCOUNT = 5;
         
        const int OUTPUTCOUNT = 1;

        const int MAXGENS = 500;

        // How many parents to keep from the last generation
        const int ELITISM = 2;

        const char* SAVE_PATH = "Data/";

        // Genomes Array
        std::vector<Genome*> genomes;

        float meanAdjustedFitness = 0.0f;

        int currentGeneration = 0;

        int bestGenomeIndex = -1;

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

        int SpeciesCount();

        ~NeuroEvolution();
};

#endif


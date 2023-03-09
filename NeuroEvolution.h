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
     
        // Genomes Array
        std::vector<Genome*> genomes;

        float meanAdjustedFitness = 0.0f;

        int currentGeneration = 0;

        int bestGenomeIndex = -1;

        bool SetGenomeFitness( int index, float fitness );
    
        // Initiate a population
        void Initiate();

        void Initiate( const char* path );

        // Mutation
        void Mutate();
        
        // Crossover
        void CrossOver();
        
        // Speciation
        void Speciate();

        void SaveGenomesToJSON();

        int SpeciesCount();

        void SaveBestGenome();

        ~NeuroEvolution();
};

#endif


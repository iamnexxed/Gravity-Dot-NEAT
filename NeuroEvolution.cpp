#include "NeuroEvolution.h"


bool NeuroEvolution::SetGenomeFitness( int index, float fitness ) {
    if( index >= 0 && index < this->genomes.size() ) {
        this->genomes[index]->fitness = fitness;
        return true;
    }
    return false;
}

void NeuroEvolution::Initiate() {
    // Create a new random population 
    for( int i = 0; i < this->populationSize; ++i ) {
        this->genomes.push_back( new Genome( INPUTCOUNT, OUTPUTCOUNT ) );
    }
    //std::cout << "\nInitiate. Species Array Size: " << this->speciesArray.size();
    //std::cout << "\nInitiate. Genomes Array Size: " << this->genomes.size();
}


void NeuroEvolution::Mutate() {
    //this->genomes[0]->ShowNodeData();
    //std::cout << "\n\n--------TEst Mutation--------";
    // Perform mutation for all the genomes  
    for( int i = 0; i < this->genomes.size(); ++i ) {
        this->genomes[i]->Mutate();
    }
    //this->genomes[0]->Mutate();
    //this->genomes[0]->ShowNodeData();
}

void NeuroEvolution::Speciate() {
    // For each genome in global genomes
    for( int i = 0; i < this->genomes.size(); ++i ) {
        bool foundMatch = false;
        //std::cout << "\nSpeciate. Species Array Size: " << this->speciesArray.size();
        // For each species in this->species
        for( int j = 0; j < this->speciesArray.size(); ++j ) {
            // Get species representative index
            int representativeIndex = 
                this->speciesArray[j]->GetRepresentativeGenomeIndex();
        
            if( i != representativeIndex ) {
                // if the genome is compatible with the species
                if( 
                    this->genomes[i]->IsCompatible( 
                        *this->genomes[representativeIndex] 
                    ) 
                ) {
                    // A genome in the current generation is placed in the first species in which it is compatible with the representative genome of that species
                    this->speciesArray[j]->Add( i );
                    foundMatch = true;
                    // no need to check further for species
                    break;
                }     
            }  
        } 

        // Otherwise if no species match found
        if( !foundMatch ) {
            // Create a new species 
            // Append the genome to the species
            // Make the genome as it's representative
            this->speciesArray.push_back( new Species( i ) );
        }
   
        // Calculate the shared fitness for the genome wrt other genomes
        float sum = 0;
        for( int j = 0; j < this->genomes.size(); ++j ) {
            if( i != j ) {
                sum += this->genomes[i]->IsCompatible(
                    *this->genomes[j] 
                ) ? 1.0f : 0.0f;
            }
        }
        if( sum > 0 )
            this->genomes[i]->fitness /= sum;
    } 
    //std::cout << "\nSpeciate. Genomes Array Size: " << this->genomes.size();
    //std::cout << "\nSpeciate. Species Array Size: " << this->speciesArray.size();
}

void NeuroEvolution::CrossOver() {
    // Every species is assigned a potentially different number of offspring in proportion to the sum of adjusted fitnesses of its member organisms
    // Remove a percentage of population from from the total based on the fitness including stale species
    // For every species
        // Loop till population is recovered for that species
            // Select two available parents randomly
            // Create a new offspring through crossover
            // Mutate the offspring
    
}

 NeuroEvolution::~NeuroEvolution() {
    for(int i = 0; i < this->speciesArray.size(); ++i ) {
        delete this->speciesArray[i];
    } 

    for(int i = 0; i < this->genomes.size(); ++i ) {
        delete this->genomes[i];
    } 
 }
#include "NeuroEvolution.h"


bool NeuroEvolution::SetGenomeFitness( int index, float fitness ) {
    if( index >= 0 && index < this->genomes.size() ) {
        this->genomes[index]->fitness = fitness;
        return true;
    }
    return false;
}

void NeuroEvolution::Initiate() {
    this->currentGeneration = 0;
    // Create a new random population 
    for( int i = 0; i < this->populationSize; ++i ) {
        this->genomes.push_back( 
            new Genome( 
                this->INPUTCOUNT, this->OUTPUTCOUNT, this->currentGeneration 
            ) 
        );
    }
}


void NeuroEvolution::Mutate() {
    this->genomes[0]->ShowNodeData();
    std::cout << "\n\n--------TEst Mutation--------";
    // Perform mutation for all the genomes  
    for( int i = 0; i < this->genomes.size(); ++i ) {
        //this->genomes[i]->Mutate();
    }
    this->genomes[0]->Mutate();
    this->genomes[0]->ShowNodeData();
}

void NeuroEvolution::Speciate() {
    this->meanAdjustedFitness = 0.0f;
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

        this->meanAdjustedFitness += this->genomes[i]->fitness;
    } 

    // Store the mean adjusted fitness of all the genomes
    this->meanAdjustedFitness /= this->genomes.size();
    
    //std::cout << "\nSpeciate. Genomes Array Size: " << this->genomes.size();
    //std::cout << "\nSpeciate. Species Array Size: " << this->speciesArray.size();
}

void NeuroEvolution::CrossOver() {
    // Prerequisite: CrossOver operation must be performed after Speciation

    // Create a new genomes array
    std::vector<Genome> nextGenomes;
    // For every species
    for( int i = 0; i < this->speciesArray.size(); ++i ) {
        // Calculate the sum of adjusted fitnesses for the species
        float sumAdjustedFitness = 0.0f;
        for( int j = 0; j < this->speciesArray[i]->Size(); ++j ) {
            int index = this->speciesArray[i]->GetGenomeIndexAt( j );
            sumAdjustedFitness += this->genomes[index]->fitness;
        }

        // Calculate the offspring length of the new generation for the species
        // Every species is assigned a potentially different number of offspring in proportion to the sum of adjusted fitnesses of its member organisms    
        // offspring_length = ( sum_of_adjusted_fitness of all the genomes in the species ) / ( mean adjusted fitness of all the genomes )
        int offspringLength = this->meanAdjustedFitness > 0 
            ? (int)std::round( sumAdjustedFitness / this->meanAdjustedFitness )
            : this->speciesArray[i]->Size();

        // Cull the species and keep parents
        this->speciesArray[i]->CullSpecies( this->genomes );
        // TO DO: Keep topmost parent for a small number of possibilities since it will be the fittest
        
        // Loop till population is recovered for that species
        while( offspringLength-- > 0 ) {
            // Select two available parents randomly
            int rand1Index = this->speciesArray[i]->GetRandomParent();
            int rand2Index = this->speciesArray[i]->GetRandomParent();
            // Create a new offspring through crossover
            Genome newGenome = this->genomes[rand1Index]->CrossOver( 
                *this->genomes[rand2Index] 
            );
            // Mutate the offspring
            newGenome.Mutate();
            // Add the offspring genome to the new genomes array
            nextGenomes.push_back( newGenome );
        }            
    }

    // Reassign the previous genomes with the new genomes array
    this->clearGenomes();
    this->currentGeneration++;
    for( int i = 0; i < nextGenomes.size(); ++i ) {
        this->genomes.push_back( 
            new Genome( nextGenomes[i], this->currentGeneration ) 
        );
    }
    // New generation of genomes are ready to ROCK!
    std::cout << "\nAfter CrossOver genome size is: " << this->genomes.size() << "\n\n";
}

void NeuroEvolution::clearSpecies() {
    for(int i = 0; i < this->speciesArray.size(); ++i ) {
        delete this->speciesArray[i];
    } 
    this->speciesArray.clear();
}

void NeuroEvolution::clearGenomes() {
    for(int i = 0; i < this->genomes.size(); ++i ) {
        delete this->genomes[i];
    } 
    this->genomes.clear();
}

void NeuroEvolution::SaveGenomesToJSON() {
    for(int i = 0; i < this->genomes.size(); ++i ) {
        this->genomes[i]->SaveToJSON( SAVE_PATH );
    } 
}

 NeuroEvolution::~NeuroEvolution() {
    this->clearSpecies();
    this->clearGenomes();
 }
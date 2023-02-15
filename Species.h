#ifndef SPECIES_CLASS_H
#define SPECIES_CLASS_H

#include <vector>
#include "Genome.h"
#include "Primitives/Mathematics.h"

class Species {
    private:
        // Genome array
        std::vector<int> genomeTracker;
        // Representative Genome
        int representativeIndexLocation;
        // Stale Species Generation counter
        
    public:
        Species( int index );
        // Add new genome
        void Add( int index );
        int GetRepresentativeGenomeIndex();
};

#endif
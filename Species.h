#ifndef SPECIES_CLASS_H
#define SPECIES_CLASS_H

#include <vector>
#include "Genome.h"
#include "Helpers/Mathematics.h"

class Species {
    private:
        // Genome array
        std::vector<int> genomeTracker;
        // Parent store array
        std::vector<int> parents;
        // Representative Genome
        int representativeIndexLocation;
        // Stale Species Generation counter

    public:
        

        Species( int index );
        // Add new genome
        void Add( int index );
        int Size();
        int GetGenomeIndexAt( int location );
        int GetParentGenomeIndexAt( int location );
        int GetRandomParent();
        int GetRepresentativeGenomeIndex();
        void CullSpecies( const std::vector<Genome*>& genomeArray );
};

#endif
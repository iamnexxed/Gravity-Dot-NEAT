#include "Species.h"

Species::Species( int index ) {
    this->Add( index );
}

void Species::Add( int index ) {
    // Add to the genome array
    this->genomeTracker.push_back( index );
    this->representativeIndexLocation = Mathematics::RandomInRange( 
        0, this->genomeTracker.size() - 1 
    );
}

int Species::GetRepresentativeGenomeIndex() {
    return this->genomeTracker[this->representativeIndexLocation];
}

void Species::CullSpecies( const std::vector<Genome*>& genomeArray ) {
    // Sort all the genome indices based on the fitness of each genome
    std::sort( 
        this->genomeTracker.begin(), 
        this->genomeTracker.end(), 
        [&]( int a, int b) {
            return genomeArray[a]->fitness > genomeArray[b]->fitness;
        }
    );
    // Get parent_length = ceil( CULLFACTOR * genomeTracker.size() );
    int parentLength = ( int )std::ceil( 
        SPECIES_KEEP_FACTOR * this->genomeTracker.size() 
    );

    // Empty the parent store array
    this->parents.clear();
    // For( i = 0 > parent_length)
    for( int i = 0; i < parentLength; ++i ) {
        // store genomeTracker[i] in parent store array
        this->parents.push_back( this->genomeTracker[i] );
    }
    // empty out the genomeTracker
    this->genomeTracker.clear();
}

int Species::Size() {
    return this->genomeTracker.size();
}

int Species::GetGenomeIndexAt( int location ) {
    if( location < 0 ) return -1;
    return this->genomeTracker[location];
}

int Species::GetParentGenomeIndexAt( int location ) {
    if( location < 0 ) return -1;
    return this->parents[location];
}

int Species::GetRandomParent() {
    int rnd = Mathematics::RandomInRange( 0, this->parents.size() - 1 );
    return this->parents[rnd];
}

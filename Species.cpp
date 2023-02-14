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
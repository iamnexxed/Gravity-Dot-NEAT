#include "Genome.h"

Genome::Genome() {

    this->Initialize( 3, 2 );
}

void Genome::Initialize( int inputCount, int outputCount ) {
    this->nodeCounter = 0;
    this->nodes.clear();
    for( int i = 0; i < inputCount; ++i ) {
        this->nodes.push_back( { this->nodeCounter, NodeType::Sensor } ); 
        this->nodeCounter++;
    } 

    for( int i = 0; i < outputCount; ++i ) {
        this->nodes.push_back( { this->nodeCounter, NodeType::Output } ); 
        this->nodeCounter++;
    } 

}
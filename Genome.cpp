#include "Genome.h"

Node::Node( int id, LayerType type ) {
    this->index = id;
    this->type = type;
    this->outputActivation = 0;
    this->input = 0;

    // If type is sensor, layer->0
    // Else, layer->1
}

float Node::SigmoidActivation( float value ) {
    return 1 / ( 1 + std::pow( E, -value ) );
}

void Node::Activate() {
    this->outputActivation = Node::SigmoidActivation( this->input );
}

Genome::Genome() {

    this->Initialize( 3, 2 );
}

void Genome::Initialize( int inputCount, int outputCount ) {
    this->inputCount = inputCount;
    this->outputCount = outputCount;
    this->nodeCounter = 0;
    this->nodes.clear();
    for( int i = 0; i < inputCount; ++i ) {
        //this->nodes.push_back( { this->nodeCounter, NodeType::Sensor } ); 
        this->nodeCounter++;
    } 

    for( int i = 0; i < outputCount; ++i ) {
        //this->nodes.push_back( { this->nodeCounter, NodeType::Output } ); 
        this->nodeCounter++;
    } 

    // Create a new hidden node based on probability
    // Create connections to the other nodes based on probability
    // Assign weights randomly to the connections created
    // Enable/Disable connections based on probability

}

void Genome::CreateConnection( 
    int inNodeIndex, 
    int outNodeIndex, 
    float weight, 
    bool isEnabled, 
    int innovNum 
) {

}
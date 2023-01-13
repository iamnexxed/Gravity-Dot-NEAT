#include "Genome.h"

Node::Node( int id, LayerType type ) {
    this->index = id;
    this->type = type;
    this->outputActivation = 0;
    this->input = 0;
    this->layerIndex = 0;
    // If type is sensor, layer->0 Else, layer->1
    if( this->type == LayerType::Sensor ) {
        this->layerIndex = 0;
    } else {
        this->layerIndex = 1;
    }
   
}

float Node::SigmoidActivation( float value ) {
    return 1 / ( 1 + std::pow( E, -value ) );
}

void Node::Activate() {
    this->outputActivation = Node::SigmoidActivation( this->input );
}

void Node::ShowData() {
    std::cout << "\n\nNode Id: " << this->index;
    std::cout << "\nType: " << this->type;
    std::cout << "\nLayer Index: " << this->layerIndex;

    std::cout << "\nInput: " << this->input;
    std::cout << "\nOutput: " << this->outputActivation;
    if( this->connectionIndices.size() > 0) {
        std::cout << "\nConnection Indices: ";
        for( int i = 0; i < this->connectionIndices.size(); ++i ) {
            std::cout << "\t" << this->connectionIndices[i];
        }
    } else {
        std::cout << "\nNo In Connections.";
    }
    
}

Genome::Genome( int inputCount, int outputCount ) {

    this->Initialize( inputCount, outputCount );
}

void Genome::Initialize( int inputCount, int outputCount ) {
    this->inputCount = inputCount;
    this->outputCount = outputCount;
    this->nodeCounter = 0;
    this->nodes.clear();
    for( int i = 0; i < inputCount; ++i ) {
        this->AddNode( LayerType::Sensor );
    } 

    for( int i = 0; i < outputCount; ++i ) {
        this->AddNode( LayerType::Output );
    } 

    // Create a new hidden node based on probability
    // Create connections to the other nodes based on probability
    // Assign weights randomly to the connections created
    // Enable/Disable connections based on probability

}

bool Genome::CreateConnection( 
    int inNodeIndex, 
    int outNodeIndex, 
    float weight, 
    bool isEnabled
) {
    // Don't create connections if the inputs are connected to the inputs or if the outputs are connected to the outputs
    if( 
        this->nodes[inNodeIndex].type != LayerType::Hidden && (
            this->nodes[inNodeIndex].type == LayerType::Output ||
            this->nodes[outNodeIndex].type == LayerType::Sensor
        )
    ) return false; 

    if( 
        inNodeIndex < this->nodes.size() && 
        outNodeIndex < this->nodes.size() 
    ) {
        this->connections.push_back({
            inNodeIndex,
            outNodeIndex,
            weight,
            isEnabled,
            this->innovNumber++
        });
        // For each connection increment the innovation number
        //this->innovNumber++;
        return true;
    }
    return false; 
}

void Genome::AddNode( LayerType type ) {
    Node node( this->nodeCounter, type );
    this->nodes.push_back( node );
    this->nodeCounter++;
}

void Genome::ShowNodeData() {
    // Show Nodes
    for( int i = 0; i < this->nodes.size(); ++i ) {

        this->nodes[i].ShowData();
  
    }

    // Show connections
    std::cout << "\n\nConnections: \n";
    for( int i = 0; i < this->connections.size(); ++i ) {

        std::cout << "\ni: " << i;
        std::cout << "\nIn Node: " << this->connections[i].inNodeIndex;
        std::cout << "\nOut Node: " << this->connections[i].outNodeIndex;
        std::cout << "\nWeight: " << this->connections[i].weight;
        std::cout << "\nEnabled: " << this->connections[i].isEnabled;
        std::cout << "\nInnovation Num: " << this->connections[i].innovNum;
        std::cout << "\n";
    }

    std::cout << "\n\n";
}

Genome Genome::GenerateTestGenome() {
    // Create a genome with 3 inputs and 1 output
    Genome g( 3, 1 );

    // Add one hidden node
    g.AddNode( LayerType::Hidden );

    // Create Connections
    g.CreateConnection( 0, 3,   0.7f, true );
    g.CreateConnection( 1, 3,  -0.5f, false );
    g.CreateConnection( 2, 3,   0.5f, true );
    g.CreateConnection( 1, 4,   0.2f, true );
    g.CreateConnection( 4, 3,   0.4f, true );
    g.CreateConnection( 0, 4,   0.6f, true );

    return g;
}
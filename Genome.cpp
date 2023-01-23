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
    std::cout << "\n\n===============";
    std::cout << "\nNode Id: " << this->index;
    std::cout << "\nType: " << this->type;
    std::cout << "\n===============";
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
            // Get Innovation number based on the history
            Genome::GetInnovationNum( inNodeIndex, outNodeIndex )
        });

        return true;
    }
    return false; 
}

int Genome::AddNode( LayerType type ) {
    Node node( this->nodeCounter, type );
    this->nodes.push_back( node );
    return this->nodeCounter++;
}

void Genome::ShowNodeData() {
    std::cout << "\n\n-------------------GENOME----------------\n";
    std::cout << "\nNodes:\n";
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

void Genome::Mutate() {

    // Mutation in NEAT can change both connection weights and network structures
    // Connection weights mutate as in any NE system at each generation

    // Create a new hidden node based on probability
    // Create connections to the other nodes based on probability
    // Assign weights randomly to the connections created
    // Enable/Disable connections based on probability
}

std::vector<int> Genome::GetRandomConnIndices() {
    std::vector<int> indices;

    // Create a list
    std::list<int> inIds;
    std::list<int> outIds;

    int randomIndexOut = -1;
    int randomIndexIn = -1;

    // Assign all nodes to the outlist except the input nodes
    for( int i = this->inputCount; i < this->nodes.size(); ++i ) {
        outIds.push_back( this->nodes[i].index );       
    }

    // While a certain count is reached loop true
    while( outIds.size() > 0 ) {
        // Assign all node ids to the list except the output nodes
        for( int i = 0; i < this->nodes.size(); ++i ) {
            if( this->nodes[i].type != LayerType::Output ) {
                inIds.push_back( this->nodes[i].index );
            }      
        }

        // Choose a randomIndexOut from the Hidden and the Output Nodes
        int rndOut = Mathematics::RandomInRange( 
            0, outIds.size() - 1 
        );
        randomIndexOut = Utils::GetIntValueAt( outIds, rndOut );

        // remove the randomIndexOut from the outids list
        outIds.remove( randomIndexOut );

        // Remove the randomIndexOut from the inids list
        inIds.remove( randomIndexOut );

        // For each connection
        for( int i = 0; i < this->connections.size(); ++i ) {
            // If the randomIndex == outConnectionIndex
            if( randomIndexOut == this->connections[i].outNodeIndex ) {
                // Remove the input connection id from the list if present
                inIds.remove( this->connections[i].inNodeIndex );
            }
            
        }

        // If the list is not empty
        //   break from the while loop
        if( inIds.size() > 0) break; 
    }
   
    // Select a randomIndexIn from the remaining List
    if(inIds.size() > 0 ) {
        int rndInt = Mathematics::RandomInRange( 0, inIds.size() - 1 );
        randomIndexIn = Utils::GetIntValueAt( inIds, rndInt );
    }
   
    //std::cout << "\nIndices: " << randomIndexOut << ", " << randomIndexIn;
    // Put randomIndexOut and randomIndexIn into the vector
    indices.push_back( randomIndexOut );
    indices.push_back( randomIndexIn );

    // Return the vector array
    return indices;
}

// Initialize static variables
int Genome::innovNumber = 0;
std::map<std::string, int> Genome::innoDictionary;

int Genome::GetInnovationNum( int inIndex, int outIndex ) {
    std::string checkKey = std::to_string( inIndex ) +
        "-" + std::to_string( outIndex );
    std::map<std::string, int>::iterator it = Genome::innoDictionary.find( 
        checkKey 
    );
    // if the new connection "inIndex-outIndex" key is present in the hashmap
    if( it != Genome::innoDictionary.end() ) {
        // return the value of the key from the hashmap as the innovation number for the new connection
        return Genome::innoDictionary[checkKey];
    } 

    // Otherwise
    // increment the global innovation number
    // assign the number as the innovation number for the new connection
    // Insert the connection's "inIndex-outIndex" and innovation number as key value into the hashmap
    Genome::innoDictionary.insert( { checkKey, ++Genome::innovNumber } );
    // return the global innovation number
    return Genome::innovNumber;
}

bool Genome::AddRandomConnection() {
    // Get two distinct nodeIndices randomly which are not connected
    // Either of them can be input or output node but not both
    std::vector<int> nodeIndices = this->GetRandomConnIndices();
   
    // Create connection between the two by randomly assigning a weight between -1 and 1
    if( nodeIndices[0] != -1 && nodeIndices[1] != -1 &&
        this->CreateConnection(
            nodeIndices[1],
            nodeIndices[0],
            Mathematics::RandomInRange( -1.0f, 1.0f ),
            true
        )
    ) return true;

    return false;
}

void Genome::InsertNodeRandom() {
    // Select a random connection index
    int rndIndex = Mathematics::RandomInRange( 0, this->connections.size() - 1 );
    // Disable the connection at that index
    this->connections[rndIndex].isEnabled = false;
    // Create a new hidden node
    int newIndex = this->AddNode( LayerType::Hidden );

    // Create a new connection from the previous connection's inIndex to newNodeIndex 
    // Assign weight as 1
    this->CreateConnection( 
        this->connections[rndIndex].inNodeIndex, 
        newIndex,
        1.0f,
        true
    );
   
    // Create a new connection from newNodeIndex to previous connection's outIndex 
    // Assign weight as previous connection
    this->CreateConnection( 
        newIndex,
        this->connections[rndIndex].outNodeIndex, 
        this->connections[rndIndex].weight,
        true
    );

}
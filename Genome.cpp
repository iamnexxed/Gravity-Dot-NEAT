#include "Genome.h"

// Initialize static variables
int Genome::innovNumber = 0;
int Genome::globalCounter = 0;
std::map<std::string, int> Genome::innoDictionary;
const char* Genome::EXTENSION = ".genome";

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

void Genome::GetExcessDisjointCount( const Genome& other, int& eCount, int& dCount ) {
    // Disjoint Genes-  Genes that occur within the range of the other parent's innovation numbers
    // Excess Genes-  Genes that occur outside the range of the other parent's innovation numbers
    // Reset the arguments
    eCount = 0;
    dCount = 0;

    int thisLength = this->connections.size();
    int otherLength = other.connections.size();

    // Make sure connection have size that can be compared
    if( thisLength <= 0 || otherLength <= 0 ) {
        eCount = std::max( thisLength, otherLength );
        return;
    }

    //std::cout << "\n This Length: " << thisLength << ", Other Length: " << otherLength << std::endl << std::endl;

    // Calculate the upper and lower bounds for the common range
    int lowerbound = std::max( 
        this->connections[0].innovNum, other.connections[0].innovNum 
    );
    int upperbound = std::min( 
        this->connections[thisLength - 1].innovNum, 
        other.connections[otherLength - 1].innovNum 
    );

    // Initialize i, j = 0
    int i = 0, j = 0;

    while( i < thisLength || j < otherLength ) {
        if( i < thisLength && this->connections[i].innovNum < lowerbound ) {    // Lower bound check
            eCount++;
            i++;
        } else if( j < otherLength && other.connections[j].innovNum < lowerbound ) {
            eCount++;
            j++;
        } else if( i < thisLength && j < otherLength && (                       // Mid range check
            (
                this->connections[i].innovNum >= lowerbound && 
                this->connections[i].innovNum <= upperbound 
            ) || 
            (
                other.connections[j].innovNum >= lowerbound && 
                other.connections[j].innovNum <= upperbound 
            ) )
        ) {
            if( 
                this->connections[i].innovNum < 
                other.connections[j].innovNum 
            ) {
                dCount++;
                i++;
            } else if( 
                this->connections[i].innovNum > other.connections[j].innovNum 
            ) {
                dCount++;
                j++;
            } else {
                i++;
                j++;
            }
               
        } else if(                                                              // Upper bound check
            i < thisLength && this->connections[i].innovNum > upperbound 
        ) {
            eCount++;
            i++;
        } else if( 
            j < otherLength && other.connections[j].innovNum > upperbound 
        ) {
            eCount++;
            j++;
        }  
    }
}

Genome::Genome( int inputCount, int outputCount, int gen ) {
    this->generation = gen;
    this->Initialize( inputCount, outputCount );
}

Genome::Genome( const Genome& copy, int gen ) {
    this->generation = gen;
    // Assign same input count
    // Assign same output count
    this->Initialize( copy.inputCount, copy.outputCount );
  
    // Add nodes
    for( 
        int i = copy.inputCount + copy.outputCount; 
        i < copy.nodes.size(); 
        ++i 
    ) {
        if( !this->AddHiddenNodeWithId( copy.nodes[i].index ) ) {
            std::cout   << "\n" << __FILE__ << " line " << __LINE__ 
                        << " Cannot add node index : "
                        << copy.nodes[i].index;
        }
    }

    // Set connections
    for( int i = 0; i < copy.connections.size(); ++i ) {
        if( !this->CreateConnection( copy.connections[i] ) ) {
            std::cout   << "\n" << __FILE__ << " line " << __LINE__ 
                        << " Cannot create connection : "
                        << " In Index: " << copy.connections[i].inNodeIndex
                        << " Out Index: " << copy.connections[i].outNodeIndex;
        }
    }
}

Genome::Genome( const char* path ) {
    using json = nlohmann::json;
    std::string text = Utils::getFileContents(path);
    json j = json::parse(text);
    int inputCount = j["inputCount"];
    int outputCount = j["outputCount"];
    int hiddenCount = j["hiddenCount"];
    int totalCount = inputCount + outputCount + hiddenCount;
    this->Initialize( inputCount, outputCount );

    // Add nodes
     for( 
        int i = inputCount + outputCount; 
        i < totalCount; 
        ++i 
    ) {
        int index = j["nodes"][i]["index"];
        if( !this->AddHiddenNodeWithId( index ) ) {
            std::cout   << "\n" << __FILE__ << " line " << __LINE__ 
                        << " Cannot add node index : "
                        << index;
        }
    }

    int connectionsCount = j["connectionsCount"];
    // Add connections
    for( int i = 0; i < connectionsCount; ++i ) {
        if( 
            !this->CreateConnection( 
                j["connections"][i]["inNodeIndex"],
                j["connections"][i]["outNodeIndex"],
                j["connections"][i]["weight"],
                j["connections"][i]["isEnabled"]
            ) 
        ) {
            std::cout   << "\n" << __FILE__ << " line " << __LINE__ 
                        << " Cannot create connection : "
                        << " In Index: " << j["connections"][i]["inNodeIndex"]
                        << " Out Index: " << j["connections"][i]["outNodeIndex"];
        }
    }
}

void Genome::SaveToJSON( const char* path ) {
    using json = nlohmann::json;
    json j;

    // Store the id
    j["id"] = this->id;

    // Store the generation
    j["generation"] = this->generation;

    // Store Input count
    j["inputCount"] = this->inputCount;

    // Store output count
    j["outputCount"] = this->outputCount;

    // Store Hidden node count
    j["hiddenCount"] = this->GetHiddenNodeCount();

    // Store connection count
    j["connectionsCount"] = this->connections.size();

    // Store the fitness
    j["fitness"] = this->fitness;

    // Store the nodes
    for( int i = 0; i < this->nodes.size(); ++i ) {
        // Node properties
        j["nodes"][i]["index"] = this->nodes[i].index;
        j["nodes"][i]["type"] = (int)this->nodes[i].type;
    }

    // Store the connections
    for( int i = 0; i < this->connections.size(); ++i ) {
        j["connections"][i]["id"] = i;
        j["connections"][i]["inNodeIndex"] = this->connections[i].inNodeIndex;
        j["connections"][i]["outNodeIndex"] = this->connections[i].outNodeIndex;
        j["connections"][i]["weight"] = this->connections[i].weight;
        j["connections"][i]["isEnabled"] = this->connections[i].isEnabled;
        j["connections"][i]["innovNum"] = this->connections[i].innovNum;
    }
    std::string uPath = 
        path + 
        std::to_string(this->generation) + 
        "_" + 
        std::to_string(this->id) +
        Genome::EXTENSION;

    // write the json at output path
    std::string s = j.dump();
    Utils::writeToFile( uPath.c_str(), s.c_str() );
}

void Genome::Initialize( int inputCount, int outputCount ) {
    this->id = Genome::globalCounter++;
    //std::cout << "\nGenome Id: " << this->id;
    this->inputCount = inputCount;
    this->outputCount = outputCount;
    this->nodeCounter = 0;
    this->fitness = -1.0f;
    this->nodes.clear();
    // Indices ranging from 0 to ( inputCount - 1 ) are input nodes
    for( int i = 0; i < inputCount; ++i ) {
        this->AddNode( LayerType::Sensor );
    } 
    // Indices ranging from inputCount to ( inputCount + outputCount - 1 ) are output nodes
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

        // Sort the connections array based on innovation number
        std::sort( this->connections.begin(), this->connections.end(),  
            [&]( Connection a, Connection b ) {
                return a.innovNum < b.innovNum;
            }
        );

        return true;
    }
    return false; 
}

bool Genome::CreateConnection( const Connection& connection ) {
    return this->CreateConnection(
        connection.inNodeIndex,
        connection.outNodeIndex,
        connection.weight,
        connection.isEnabled
    );
}

bool Genome::SetConnectionEnable( int index, bool value ) {
    if( index >= 0 && index < this->connections.size() ) {
        if( this->connections[index].isEnabled != value ) {
            this->connections[index].isEnabled = value; 
        }
        return true;
    }
    return false;
}

int Genome::AddNode( LayerType type ) {
    Node node( this->nodeCounter, type );
    this->nodes.push_back( node );
    this->nodeCounter = this->nodes.size();
    return this->nodeCounter;
}

bool Genome::AddHiddenNodeWithId( int id ) {
    // Check if the id already exists, as we don't want nodes with same ids
    for( int i = 0; i < this->nodeCounter; ++i ) {
        if( id == this->nodes[i].index )
            return false;
    }
    Node node( id, LayerType::Hidden );
    this->nodes.push_back( node );
    this->nodeCounter = this->nodes.size();
    return true;
}

int Genome::GetHiddenNodeCount() const { 
    return this->nodeCounter - this->inputCount - this->outputCount;
}

void Genome::ShowNodeData() {
    std::cout << "\n\n-------------------GENOME----------------\n";
    std::cout << "\nNodes:\n";
    // Show Nodes
    for( int i = 0; i < this->nodes.size(); ++i ) {

        this->nodes[i].ShowData();
  
    }
    std::cout << "\n++++++++++++++++++++++++++++++++++++\n";
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
    std::cout << "\n-------------------------------------------\n\n";
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

void Genome::ResetGenomeCounter() {
    Genome::globalCounter = 0;
}

void Genome::Mutate() {
    // Mutation in NEAT can change both connection weights and network structures
    // Connection weights mutate as in any NE system at each generation

    // Create a new hidden node based on probability
    float probability = Mathematics::RandomInRange( 0.0f, 1.0f );
    //std::cout << "\nProbability: " << probability << std::endl << std::endl;
    if( probability < NODE_ADD_PROBABILITY ) {
        this->InsertNodeRandom();
        //std::cout << "\nATTEMPT: Added Random Node";
    }

    // Create connections to the other nodes based on probability
    probability = Mathematics::RandomInRange( 0.0f, 1.0f );
    if( probability < CONNECTION_ADD_PROBABILITY ) {
        //std::cout << "\nATTEMPT: Added Random Connection";
        this->AddRandomConnection();
    }

    // Enable/Disable connections based on probability
    probability = Mathematics::RandomInRange( 0.0f, 1.0f );
    if( probability < CONNECTION_ENABLE_PROBABILITY ) {
        int randIndex = Mathematics::RandomInRange( 
            0, this->connections.size() - 1
        );
        //std::cout << "\nATTEMPT: Enabled Random Connection";
        this->SetConnectionEnable( randIndex, true );
    }

    probability = Mathematics::RandomInRange( 0.0f, 1.0f );
    if( probability < CONNECTION_DISABLE_PROBABILITY ) {
        int randIndex = Mathematics::RandomInRange( 
            0, this->connections.size() - 1
        );
        //std::cout << "\nATTEMPT: Disabled Random Connection";
        this->SetConnectionEnable( randIndex, false );
    }

    // Assign weights randomly to the connections created
    this->MutateConnectionWeights();
}

void Genome::MutateConnectionWeights() {
    float probability = 0.0f;
    for( int i = 0; i < this->connections.size(); ++i ) {
        probability = Mathematics::RandomInRange( 0.0f, 1.0f );
        // Choose a connection based on probability
        if( probability < CONNECTION_SELECTION_PROBABILITY ) {
            // Choose if to mutate weight or to set a different weight
            probability = Mathematics::RandomInRange( 0.0f, 1.0f );
            if( probability < WEIGHT_MUTATION_PROBABILITY ) {
                this->connections[i].weight += Mathematics::RandomInRange(
                    -WEIGHT_MUTATION_FACTOR, WEIGHT_MUTATION_FACTOR
                );
                this->connections[i].weight = Mathematics::Clamp(
                    this->connections[i].weight, 
                    -MAX_CONNECTION_WEIGHT, 
                    MAX_CONNECTION_WEIGHT
                );
            } else {
                this->connections[i].weight = Mathematics::RandomInRange( 
                    -MAX_CONNECTION_WEIGHT, MAX_CONNECTION_WEIGHT 
                );
            }
        }
    }
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

// Static function for getting the global innovation number
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
            nodeIndices[1],     // In Index
            nodeIndices[0],     // Out Index
            Mathematics::RandomInRange( 
                -MAX_CONNECTION_WEIGHT, MAX_CONNECTION_WEIGHT 
            ),
            true
        )
    ) return true;

    return false;
}

void Genome::InsertNodeRandom() {
    if( this->connections.size() > 0 ) {
        // Select a random connection index
        int rndIndex = Mathematics::RandomInRange( 0, this->connections.size() - 1 );
        //std::cout << "\nRandIndex : " << rndIndex << std::endl << std::endl;
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
    
}

Genome* Genome::CrossOver( const Genome& other ) {
    // Preconditions
    // 1. Connections of this and the other genome should be sorted in ascending order

    Genome* g = new Genome( this->inputCount, this->outputCount );

    // Create nodes in genome for connections if they don't exist
    int hiddenCount = std::max( 
        this->GetHiddenNodeCount(), 
        other.GetHiddenNodeCount() 
    ); 
    for( int i = 0; i < hiddenCount; ++i ) {
        g->AddNode( LayerType::Hidden );
    }


    // Set variables i and j to 0
    int i = 0, j = 0; 

    while( i < this->connections.size() || j < other.connections.size() ) {
        if( j < other.connections.size() ) {
            //std::cout << "\n\nThis Genome Conn Size: " << this->connections.size();
            //std::cout << "\nThis Genome i InnoNum: " << this->connections[i].innovNum;
            //std::cout << "\nOther Genome j InnoNum: " << other.connections[j].innovNum;
            if( ( i >= this->connections.size() ) || ( 
                    i < this->connections.size() && 
                    this->connections[i].innovNum > other.connections[j].innovNum 
                )
            ) { // Excess found in other genome OR Disjoint found
                if( this->fitness < other.fitness && g->CreateConnection( other.connections[j] ) ) {
                    // Include other.connections[j] in the child connections
                    //std::cout << "\nConnection Created for innoNum: " << other.connections[j].innovNum;
                }
                else if( this->fitness == other.fitness ) {
                    // Include other.connections[j] in the child connections based on random probability
                    int rndInt = Mathematics::RandomInRange( 0, 1 );
                    //std::cout << "\nrndInt: " << rndInt;
                    if( rndInt == 1 && g->CreateConnection( other.connections[j] ) ) {
                        //std::cout << "\nConnection Created for innoNum: " << other.connections[j].innovNum;
                    }
                }   
                // Increment j
                j++;
                // continue
                continue;
            } 
        }
        
        if( i < this->connections.size() ) {
            //std::cout << "\n\nOther Genome Conn Size: " << other.connections.size();
            //std::cout << "\nThis Genome i InnoNum: " << this->connections[i].innovNum;
            //std::cout << "\nOther Genome j InnoNum: " << other.connections[j].innovNum;
            if ( ( j >= other.connections.size() ) || ( 
                    j < other.connections.size() && 
                    this->connections[i].innovNum < other.connections[j].innovNum 
                )
            ) { // Disjoint found
                if( this->fitness > other.fitness && g->CreateConnection( this->connections[i] ) ) {
                    // Include this->connections[i] in the child connections
                    //std::cout << "\nConnection Created for innoNum: " << this->connections[i].innovNum;

                }
                else if( this->fitness == other.fitness ) {
                    // Include this->connections[i] in the child connections based on random probability
                    int rndInt = Mathematics::RandomInRange( 0, 1 );
                    //std::cout << "\nrndInt: " << rndInt;
                    if( rndInt == 0 && g->CreateConnection( this->connections[i] ) ) {
                        //std::cout << "\nConnection Created for innoNum: " << this->connections[i].innovNum;
                    }
                }   
                // Increment i
                i++;
                // continue
                continue;
            }     
        }
            
        //std::cout << "\n\nThis Genome i InnoNum: " << this->connections[i].innovNum;
        //std::cout << "\nOther Genome j InnoNum: " << other.connections[j].innovNum;
        // Matching genes are inherited randomly
        if( this->connections[i].innovNum == other.connections[j].innovNum ) {
            // Include any of this->connections[i] and other.connections[j] in the child connections randomly
            int rndInt = Mathematics::RandomInRange( 0, 1 );
            //std::cout << "\nrndInt: " << rndInt;
            if( rndInt == 0 && g->CreateConnection( this->connections[i] ) ) {
                //std::cout << "\nConnection Created for innoNum: " << this->connections[i].innovNum;
            } else if( g->CreateConnection( other.connections[j] ) ) {
                //std::cout << "\nConnection Created for innoNum: " << other.connections[j].innovNum;
            }
            // Increment i and j
            i++;
            j++;
        }    
    }
            
    return g;
}

bool Genome::IsCompatible( const Genome& other ) {
    
    int excess = 0, disjoint = 0;
    // Calculate Disjoint and Excess Genes
    this->GetExcessDisjointCount( other, excess, disjoint );
    //std::cout << "\nExcess: " << excess << ", Disjoint: " << disjoint << std::endl << std::endl;
    // Calculate N- Number of Genes in larger genome
    int N = std::max( this->connections.size(), other.connections.size() );
    N = N < LEAST_BIG_GENOME_SIZE ? 1 : N;

    // Calculate WBar- Average weight differences of matching genes
    float thisW = this->GetAverageGeneWeight();
    float otherW = other.GetAverageGeneWeight();
    float barW = std::abs( thisW - otherW );

    // Calulate delta = c1 * E / N + c2 * D / N + c3 * WBar
    float delta = C1 * excess / N + C2 * disjoint / N + C3 * barW;

    return delta < COMPATIBILITY_THRESHOLD;
}

float Genome::GetAverageGeneWeight() const {
    if( this->connections.size() <= 0 ) return 0;
    float sum = 0;
    for( int i = 0; i < this->connections.size(); ++i ) {
        sum += this->connections[i].weight;
    }
    return sum / (float) this->connections.size();
}
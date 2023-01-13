#include "NeuralNetwork.h" 


Layer::Layer() {

   
}

void Layer::AddNode( Node& node ) {
    this->nodes.push_back(&node);
}

void Layer::ActivateNeurons() {
    for( int i = 0; i < this->nodes.size(); ++i ) {
        this->nodes[i]->Activate();
    }
}

std::vector<float> Layer::GetActivationOutput() {
    std::vector<float> outputs;
    for( int i = 0; i < this->nodes.size(); ++i ) {
        outputs.push_back( this->nodes[i]->outputActivation );
    }
    return outputs;
}

int Layer::GetNodeCount() {
    return this->nodes.size();
}

void Layer::ShowLayerData() {
    //std::cout << "\n\nLayer type: " << this->type;
    for( int i = 0; i < this->nodes.size(); ++i ) {
        this->nodes[i]->ShowData();
    }
}


NeuralNetwork::NeuralNetwork( Genome& genome ): genome( genome ) {

    // First inputCount nodes will be input nodes
    // Indices ranging from inputCount to outputCount will be outputNodes
    
    int totalLayers = 0;
    // For each connection
    for( int i = 0; i < genome.connections.size(); ++i ) {
        int outIndex = genome.connections[i].outNodeIndex;
        int inIndex = genome.connections[i].inNodeIndex;
        if( 
            genome.nodes[outIndex].layerIndex < 
            genome.nodes[inIndex].layerIndex + 1
        ) {
            //  nodes[outIndex].layerIndex = nodes[inIndex].layerIndex + 1;
            genome.nodes[outIndex].layerIndex = genome.nodes[inIndex].layerIndex + 1;
            //  if(nodes[outIndex].layerIndex > totalLayers) totalLayers = nodes[outIndex].layerIndex
            // Store last layer index
            if( genome.nodes[outIndex].layerIndex > totalLayers )
                totalLayers = genome.nodes[outIndex].layerIndex;
        }
        

        //  If the connection is enabled
        //  Add connectionIndex associated with the outputNode to the outputNode
        if( genome.connections[i].isEnabled )
            genome.nodes[outIndex].connectionIndices.push_back( i );
    }
    
    // Set layer count based on prev last layer index
    totalLayers += 1;

    // For i 0 to totalLayers
    for( int i = 0; i < totalLayers; ++i ) {
        //  create a new Layer
        this->layers.push_back( Layer() );
    }

    //genome.ShowNodeData();

    // For each node in the genome
    for( int i = 0; i < genome.nodes.size(); ++i ) {
        // Add nodes to the layers if it has connections
        if( 
            genome.nodes[i].layerIndex < this->layers.size() && (
                genome.nodes[i].type != LayerType::Hidden ||
                genome.nodes[i].connectionIndices.size() > 0  
            )
        )
            this->layers[genome.nodes[i].layerIndex].AddNode( genome.nodes[i] );        
    }

    this->ShowLayers();    
    

}

void NeuralNetwork::ShowLayers() {
    std::cout << "\n---------------NN Layers------------------------------\n";
    for( int i = 0; i < this->layers.size(); ++i ) {
        std::cout << "\n\n----------------- i: " << i;
        this->layers[i].ShowLayerData();
    }
    std::cout << "\n\n";
}



std::vector<float> NeuralNetwork::Predict( const std::vector<float>& inputs ) {

    // Map each input to each node of the input layer
    if( inputs.size() != this->layers[0].GetNodeCount() ) {
        // Incorrect sensor node count 
        std::cout << "\nIncorrect input size!....";
        return std::vector<float>();
    }
    for( int i = 0; i < inputs.size(); ++i ) {
        this->layers[0].nodes[i]->outputActivation = inputs[i];
    }

    // For each Layer after the sensory layer
    for( int i = 1; i < this->layers.size(); ++i ) {
        //  for each node of the layer
        for( int j = 0; j < this->layers[i].nodes.size(); ++j ) {
            // Iterate through each connection associated
            for( 
                int k = 0; 
                k < this->layers[i].nodes[j]->connectionIndices.size(); 
                ++k 
            ) {
                // Add the nodes[inNodeIndex].output * weight to the input of the node
                this->layers[i].nodes[j]->input += 
                    this->genome.nodes[
                        this->genome.connections[
                            this->layers[i].nodes[j]->connectionIndices[k]
                        ].inNodeIndex
                    ].outputActivation * 
                        this->genome.connections[
                            this->layers[i].nodes[j]->connectionIndices[k]
                        ].weight;
                        
                
            }
            // Activate the node
            this->layers[i].nodes[j]->Activate();
        }
       

    }
    
    // Get Output associated with the last layer
    return this->layers[this->layers.size() - 1].GetActivationOutput();
}
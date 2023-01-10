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


NeuralNetwork::NeuralNetwork( const Genome& genome ): genome( genome ) {


    // First inputCount nodes will be input nodes
    // Indices ranging from inputCount to outputCount will be outputNodes

    // int totalLayers;
    // For each connection
    //  nodes[outIndex].layerIndex = nodes[inIndex].layerIndex + 1;
    //  if(nodes[outIndex].layerIndex > totalLayers) totalLayers = nodes[outIndex].layerIndex
    //  Add connectionIndex associated with the outputNode to the outputNode

    // For i 0 to totalLayers
    //  create a new Layer

    // For each node in the genome
    //  layers[node.layerIndex].Add(ref node);

}



std::vector<float> NeuralNetwork::Predict( const std::vector<float>& inputs ) {

    // For each Layer
    //  for each node of the layer
    //      Iterate through each connection associated
    //          If the connection is enabled
    //              Add the inNode.output * weight to the node
    //      Activate the node

    // OutputLayer.GetActivationOutput()
    return inputs;
}
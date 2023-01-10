#ifndef NEURALNETWORK_CLASS_H
#define NEURALNETWORK_CLASS_H

#include "Genome.h"
#include "Matrix.h"

class Layer {

    private: 
        // Node references
        std::vector<Node*> nodes;
        LayerType type;

    public:
        Layer();
        void AddNode( Node& node );
        // Activate neuron nodes
        void ActivateNeurons();
        std::vector<float> GetActivationOutput();
};

class NeuralNetwork {
    
    // Layers
    std::vector<Layer> layers;

    const Genome& genome;
    public:
        NeuralNetwork( const Genome& genome );
    
        std::vector<float> Predict( const std::vector<float>& inputs );
};


#endif
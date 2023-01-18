#ifndef NEURALNETWORK_CLASS_H
#define NEURALNETWORK_CLASS_H

#include "Genome.h"
#include "Matrix.h"

class Layer {

    private: 
       
        //LayerType type;

    public:
         // Node references
        std::vector<Node*> nodes;

        Layer();
        void AddNode( Node& node );
        void ShowLayerData();
        // Activate neuron nodes
        void ActivateNeurons();
        std::vector<float> GetActivationOutput();
        int GetNodeCount();
};

class NeuralNetwork {
    
    // Layers
    std::vector<Layer> layers;

    Genome& genome;
    public:
        NeuralNetwork( Genome& genome );
        void ShowLayers();
        std::vector<float> Predict( const std::vector<float>& inputs );
};


#endif
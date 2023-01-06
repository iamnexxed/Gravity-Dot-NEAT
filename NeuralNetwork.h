#ifndef NEURALNETWORK_CLASS_H
#define NEURALNETWORK_CLASS_H

#include "Genome.h"
#include "Matrix.h"


class NeuralNetwork;
class Layer {

    private: 
       friend class NeuralNetwork;

    public:
        // WeightMatrix - RowCol
        Matrix weightMatrix;

        // Bias Matrix - Col
        Matrix biasMatrix;

        Layer( int inputCount, int nodeCount );

        // ColMatrx GetOutput( InputMatrix )
        Matrix GetOutput( 
            const Matrix& inputMatrix, 
            bool shouldUseActivation = true
        );
    
};

class NeuralNetwork {
    
    // Layers
    std::vector<Layer> layers;
    public:
        NeuralNetwork();
        NeuralNetwork( const Genome& genome );
        void CreateLayers(const Genome& genome );
        // Activation function
        static float SigmoidActivation( float value );

        Matrix Predict( const Matrix& inputMatrix );
};


#endif
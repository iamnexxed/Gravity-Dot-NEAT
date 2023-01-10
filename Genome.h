#ifndef GENOME_CLASS_H
#define GENOME_CLASS_H

#include <vector>
#include "Primitives/Mathematics.h"

enum LayerType {
    Sensor,
    Hidden,
    Output
};

class Node {
    public:
        int index;
        LayerType type;
        // Output Activation
        float outputActivation;
        float input;
        std::vector<int> connectionIndices;
        int layerIndex;

        Node( int id, LayerType type );
        // Activation Function
        void Activate();
        static float SigmoidActivation( float value );


};

struct Connection {
    int inNodeIndex;
    int outNodeIndex;
    float weight;
    bool isEnabled;
    int innovNum;
};

class Genome {

    // Consists of Nodes and Connections
    private:
        int nodeCounter = 0;
    public:
        int inputCount = 0;
        int outputCount = 0;
        std::vector<Node> nodes;
        std::vector<Connection> connections;

        // Default Genome Configuration:


        Genome();
        void Initialize( int inputCount, int outputCount );
        void CreateConnection( 
            int inNodeIndex, 
            int outNodeIndex, 
            float weight, 
            bool isEnabled, 
            int innovNum 
        );
};

#endif
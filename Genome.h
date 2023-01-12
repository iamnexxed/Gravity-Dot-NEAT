#ifndef GENOME_CLASS_H
#define GENOME_CLASS_H

#include <vector>
#include <iostream>
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
        void ShowData();

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
        int innovNumber = 1;
    public:
        int inputCount = 0;
        int outputCount = 0;
        std::vector<Node> nodes;
        std::vector<Connection> connections;

        // Default Genome Configuration:


        Genome( int inputCount, int outputCount );
        void Initialize( int inputCount, int outputCount );
        void CreateConnection( 
            int inNodeIndex, 
            int outNodeIndex, 
            float weight, 
            bool isEnabled
        );
        void ShowNodeData();
        void AddNode( LayerType type );
        static Genome GenerateTestGenome();
};

#endif
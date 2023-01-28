// Main reference: https://nn.cs.utexas.edu/downloads/papers/stanley.ec02.pdf

#ifndef GENOME_CLASS_H
#define GENOME_CLASS_H

#include <vector>
#include <list>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include "Primitives/Mathematics.h"
#include "Primitives/Utils.h"

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

 // Consists of Nodes and Connections
class Genome {
    private:    
        // static global innovation Number
        static int innovNumber;
        // HashMap var containing connection innovation history
        static std::map<std::string, int> innoDictionary;

        static int GetInnovationNum( int inIndex, int outIndex );

        // Counter for assigning node ids
        int nodeCounter = 0;

        std::vector<int> GetRandomConnIndices();
        

    public:

    
        int inputCount = 0;
        int outputCount = 0;

        float fitness = 0;

        std::vector<Node> nodes;
        std::vector<Connection> connections;

        // Default Genome Configuration:


        static Genome GenerateTestGenome();

        Genome( int inputCount, int outputCount );
        void Initialize( int inputCount, int outputCount );
        bool CreateConnection( 
            int inNodeIndex, 
            int outNodeIndex, 
            float weight, 
            bool isEnabled
        );
        bool CreateConnection( const Connection& connection );
        void ShowNodeData();
        int AddNode( LayerType type );
        int GetHiddenNodeCount() const;
        void Mutate();
        bool AddRandomConnection();
        void InsertNodeRandom();
        Genome CrossOver( const Genome& other );
};

#endif
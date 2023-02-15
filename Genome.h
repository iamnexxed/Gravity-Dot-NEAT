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


// DEFAULT GENOME CONFIG VARIABLES:

// Compatibility Calculation
const float C1 = 1.0f;
const float C2 = 1.0f;
const float C3 = 0.4f;
const float COMPATIBILITY_THRESHOLD = 3.0f;
const int LEAST_BIG_GENOME_SIZE = 20;

// Mutation Probabilities: 0.0 - 1.0
const float NODE_ADD_PROBABILITY = 0.3f;
const float CONNECTION_ADD_PROBABILITY = 0.4f;
const float CONNECTION_ENABLE_PROBABILITY = 0.2f;
const float CONNECTION_DISABLE_PROBABILITY = 0.1f;
const float CHANGE_WEIGHT_PROBABILITY = 0.3f;
const float CONNECTION_SELECTION_PROBABILITY = 0.2f;
const float WEIGHT_MUTATION_PROBABILITY = 0.7f;

const float MAX_CONNECTION_WEIGHT = 1.0f;
const float WEIGHT_MUTATION_FACTOR = 0.1f;



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
        bool SetConnectionEnable( int index, bool value );
        void ShowNodeData();
        int AddNode( LayerType type );
        int GetHiddenNodeCount() const;
        void Mutate();
        void MutateConnectionWeights();
        bool AddRandomConnection();
        void InsertNodeRandom();
        Genome CrossOver( const Genome& other );
        float GetAverageGeneWeight() const;
        void GetExcessDisjointCount( const Genome& other, int& eCount, int& dCount );
        // Compare function that inputs other genome. Returns the number of Disjoint, Excess genes, avg diff weights, and N
        bool IsCompatible( const Genome& other );
};

#endif
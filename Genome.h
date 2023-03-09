// Main reference: https://nn.cs.utexas.edu/downloads/papers/stanley.ec02.pdf

#ifndef GENOME_CLASS_H
#define GENOME_CLASS_H

#include <vector>
#include <list>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <json/json.h>
#include "Helpers/Mathematics.h"
#include "Helpers/Utils.h"
#include "Globals.h"

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
        static float TanHActivation( float value );
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
        // Global Genome Counter
        static int globalCounter;
        // HashMap var containing connection innovation history
        static std::map<std::string, int> innoDictionary;

        static int GetInnovationNum( int inIndex, int outIndex );

        // Counter for assigning node ids
        int nodeCounter = 0;

        std::vector<int> GetRandomConnIndices();

    public:   
        int id = -1; 
        int generation = -1;
        int inputCount = 0;
        int outputCount = 0;
        float fitness = -1.0f;
        std::vector<Node> nodes;
        std::vector<Connection> connections;


        static Genome GenerateTestGenome();
        static void ResetGenomeCounter();

        Genome( int inputCount, int outputCount, int gen = -1 );
        Genome( const Genome& copy, int gen = -1 );
        Genome( const char* path );
        void SaveToJSON( const char* path );
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
        bool AddHiddenNodeWithId( int id );
        int GetHiddenNodeCount() const;
        void Mutate();
        void MutateConnectionWeights();
        bool AddRandomConnection();
        void InsertNodeRandom();
        Genome* CrossOver( const Genome& other );
        float GetAverageGeneWeight() const;
        void GetExcessDisjointCount( const Genome& other, int& eCount, int& dCount );
        // Compare function that inputs other genome. Returns the number of Disjoint, Excess genes, avg diff weights, and N
        bool IsCompatible( const Genome& other );
};

#endif
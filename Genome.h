#ifndef GENOME_CLASS_H
#define GENOME_CLASS_H

#include <vector>
#include "Primitives/Mathematics.h"

enum NodeType {
    Sensor,
    Hidden,
    Output
};

struct Node {
    int index;
    NodeType type;
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
        std::vector<Node> nodes;
        std::vector<Connection> connections;

        Genome();
        void Initialize( int inputCount, int outputCount );
};

#endif
#ifndef NEURALNETWORK_CLASS_H
#define NEURALNETWORK_CLASS_H

#include <vector>

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
}

class Genome {

    // Consists of Nodes and Connections
    private:
        std::vector<Node> nodes;
        std::vector<Connection> connections;
};

#endif
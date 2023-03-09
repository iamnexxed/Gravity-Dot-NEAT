# Gravity-Dot-NEAT

Simulating Flappy Bird Clone with NeuroEvolution of Augmenting Topologies.

Created with OpenGL C++. 

### Generation 1
![](https://github.com/iamnexxed/Gravity-Dot-NEAT/blob/main/Images/GravityDotCapture1.gif)

.
.

### Generation 20
![](https://github.com/iamnexxed/Gravity-Dot-NEAT/blob/main/Images/GravityDotCapture2.gif)

You can save/load a genome into/from a JSON file.

Here's a GENOME/GENOTYPE example


```
{
  "connections": [            // Connections associated with the nodes
    {
      "id": 0,                // Connection ID
      "inNodeIndex": 3,       // Input of the connection
      "innovNum": 1,          // Innovation number of the connection
      "isEnabled": false,     // If the connection is enabled/disabled
      "outNodeIndex": 5,      // Output of the connection
      "weight": -0.5446997284889221   // Weight associated with the connection
    }
  ],
  "connectionsCount": 1,      // Number of connections
  "fitness": 43,              // Fitness of the genome
  "generation": 2,            // Generation of the genome
  "hiddenCount": 0,           // Hidden node count within the genome
  "id": 57,                   // ID of the genome       
  "inputCount": 5,            // Input Node Count of the genome
  "nodes": [
    {
      "index": 0,             // ID of the node
      "type": 0               // Type: 0- Input Node, 1- Hidden Node, 2- Output Node
    },
    {
      "index": 1,
      "type": 0
    },
    {
      "index": 2,
      "type": 0
    },
    {
      "index": 3,
      "type": 0
    },
    {
      "index": 4,
      "type": 0
    },
    {
      "index": 5,
      "type": 2
    }
  ],
  "outputCount": 1            // Output Node Count of the genome
}

```

References:
- https://neat-python.readthedocs.io/en/latest/neat_overview.html
- https://nn.cs.utexas.edu/downloads/papers/stanley.ec02.pdf

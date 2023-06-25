# Gravity-Dot-NEAT

Simulating Flappy Bird Clone with NeuroEvolution of Augmenting Topologies.

Created with OpenGL C++. 

Libraries used- GLAD, GLFW, GLM, JSON

Make sure to download the binaries according to your system architecture:
https://www.glfw.org/download

If you have correct libraries in place you can execute the project with the following command
```
/usr/bin/clang++ -std=c++17 -ILibraries/include -g **.cpp glad.cc -o Main -LLibraries/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit && ./Main
```


### Generation 1
![](https://github.com/iamnexxed/Gravity-Dot-NEAT/blob/main/Images/GravityDotCapture1.gif)

.
.

### Generation 20
![](https://github.com/iamnexxed/Gravity-Dot-NEAT/blob/main/Images/GravityDotCapture2.gif)

You can save/load a genome into/from a JSON file.

Here's a GENOME/GENOTYPE example JSON


```
{
  "connections": [            // Connections associated with the nodes
    {
      "id": 0,                // Connection ID
      "inNodeIndex": 3,       // Input Node Index of the connection
      "innovNum": 1,          // Innovation number of the connection
      "isEnabled": false,     // If the connection is enabled/disabled
      "outNodeIndex": 5,      // Output Node Index of the connection
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

The Neural Network takes following inputs:

1. The horizontal distance from organism to the next pillar

2. The vertical distance from the organism to the next pillar's upper edge of the gap

3. The vertical distance from the organism to the next pillar's lower edge of the gap

4. The vertical velocity of the organism


A TanH function is used to normalise the summation of the weights * inputs.


The output threshold determines if an organism should jump or not.


Fitness function used to evaluate each organism:
```
Number of frames survived + ( Number of pillars passed * 100 )
```

References:
- https://neat-python.readthedocs.io/en/latest/neat_overview.html
- https://nn.cs.utexas.edu/downloads/papers/stanley.ec02.pdf

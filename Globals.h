#ifndef GLOBALS_H
#define GLOBALS_H

#define WIDTH 720
#define HEIGHT 480
#define WINDOW_NAME "Gravity Dot"

// Note: Please check Globals.cpp for correct comments and values
namespace Globals {
    extern const float kBG_COLOR_R;
    extern const float kBG_COLOR_G;
    extern const float kBG_COLOR_B;
    extern const float kBG_COLOR_A;

    // DEFAULT GENOME CONFIG VARIABLES:

    // Compatibility Calculation
    extern const float C1;
    extern const float C2;
    extern const float C3;
    extern const float COMPATIBILITY_THRESHOLD;
    extern const int LEAST_BIG_GENOME_SIZE;

    // Mutation Probabilities: 0.0 - 1.0
    extern const float NODE_ADD_PROBABILITY;
    extern const float CONNECTION_ADD_PROBABILITY;
    extern const float CONNECTION_ENABLE_PROBABILITY;
    extern const float CONNECTION_DISABLE_PROBABILITY;
    extern const float CHANGE_WEIGHT_PROBABILITY;
    extern const float CONNECTION_SELECTION_PROBABILITY;
    extern const float WEIGHT_MUTATION_PROBABILITY;

    extern const float MAX_CONNECTION_WEIGHT;
    extern const float WEIGHT_MUTATION_FACTOR;

    // Speciation constants
    extern const float SPECIES_KEEP_FACTOR;
    // File Extension
    extern const char* EXTENSION;

    // Total Population
    extern const int POPULATION;

    // Initial Neural Network configuration
    extern const int INPUTCOUNT;
        
    extern const int OUTPUTCOUNT;

    extern const int MAXGENS;

    // How many parents to keep from the last generation
    extern const int ELITISM;

    extern const char* SAVE_PATH;

    // Organism Parameters
    extern const int STEP;
    extern const float JUMPFORCE;
    extern const float A_PARAM; // <<<<< Parameter preference currently disabled
    extern const float B_PARAM; // <<<<< Parameter preference currently disabled
    extern const float DELTA;
    extern const float MAXHEIGHT;
    extern const float MAXWIDTH;
    extern const float JUMP_PREDICTION_THRES;

    // Pillar properties
    extern const float PILLAR_ACCEL; // <<<<< Acceleration currently disabled
    extern const float Y_BOUND_DISTANCE;
    extern const float X_RESPAWN_LOCATION;
    extern const float I_PILLAR_VELOCITY;
    extern const float PILLAR_WIDTH;
    extern const float PILLAR_HEIGHT;
    extern const float UPPER_LOWER_GAP;
    extern const int PILLAR_COUNT;
    extern const float PILLAR_SPAWN_TIME;
}

#endif



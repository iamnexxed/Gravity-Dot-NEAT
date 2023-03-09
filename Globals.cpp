#include "Globals.h"

namespace Globals {
    // GENERAL COLOR CONSTANTS

    extern const float kBG_COLOR_R = 1 / 255.0f;
    extern const float kBG_COLOR_G = 1 / 255.0f;
    extern const float kBG_COLOR_B = 2 / 255.0f;
    extern const float kBG_COLOR_A = 255 / 255.0f;

    // DEFAULT GENOME CONFIG VARIABLES:

    // Compatibility Calculation
    extern const float C1 = 1.0f;
    extern const float C2 = 1.0f;
    extern const float C3 = 0.25f;
    extern const float COMPATIBILITY_THRESHOLD = 3.0f;
    extern const int LEAST_BIG_GENOME_SIZE = 20;

    // Mutation Probabilities: Range( 0.0 - 1.0 )
    extern const float NODE_ADD_PROBABILITY = 0.1f;
    extern const float CONNECTION_ADD_PROBABILITY = 0.4f;
    extern const float CONNECTION_ENABLE_PROBABILITY = 0.2f;
    extern const float CONNECTION_DISABLE_PROBABILITY = 0.4f;
    extern const float CHANGE_WEIGHT_PROBABILITY = 0.7f;
    extern const float CONNECTION_SELECTION_PROBABILITY = 0.5f;
    extern const float WEIGHT_MUTATION_PROBABILITY = 0.7f;

    extern const float MAX_CONNECTION_WEIGHT = 1.0f;
    extern const float WEIGHT_MUTATION_FACTOR = 0.1f;

    // Speciation constants
    extern const float SPECIES_KEEP_FACTOR = 0.1f;

    // Genome Save File Extension
    const char* EXTENSION = ".genome";
    const char* SAVE_PATH = "Data/";    // Create a folder called Data in the project directory

    // Total Population
    extern const int POPULATION = 80;
    extern const int MAXGENS = 500;
    // How many parents to keep from the last generation
    extern const int ELITISM = 2;

    // Initial Neural Network configuration
    extern const int INPUTCOUNT = 5;
    extern const int OUTPUTCOUNT = 1;

    // Organism Parameters
    extern const int STEP = 10; // Angle steps for drawing circle
    extern const float JUMPFORCE = 0.045;
    extern const float A_PARAM = 3.0f; // <<<<< Parameter preference currently disabled
    extern const float B_PARAM = 1.0f; // <<<<< Parameter preference currently disabled
    extern const float DELTA = 1.0f;
    extern const float MAXHEIGHT = 720;
    extern const float MAXWIDTH = 480;
    extern const float JUMP_PREDICTION_THRES = 0.0f;

    // Pillar properties
    extern const float PILLAR_ACCEL = 0.001f;
    extern const float Y_BOUND_DISTANCE = 2.0f;
    extern const float X_RESPAWN_LOCATION = -5.0f;
    extern const float I_PILLAR_VELOCITY = -0.02f;
    extern const float PILLAR_WIDTH = 0.5f;
    extern const float PILLAR_HEIGHT = 4.5f;
    extern const float UPPER_LOWER_GAP = 1.2f;
    extern const int PILLAR_COUNT = 5;
    extern const float PILLAR_SPAWN_TIME = 2.0f;
}
#include "World.h"

World::World( GLFWwindow& window, int windowWidth, int windowHeight ) :
    window(window) {
    this->camera = new Camera( 
        windowWidth, 
        windowHeight, 
        glm::vec3( 0.0f, 0.0f, 5.0f ) 
    );
    this->shaderProgram = new Shader( "sprite.vert", "sprite.frag" );
    this->shaderProgram->Activate();
    this->shaderProgram->SetFloatVecUniform3fv( "baseColor", glm::vec3( 1.0f, 1.0f, 1.0f ) );
    
    this->selectShader = new Shader( "sprite.vert", "sprite.frag" );
    this->selectShader->Activate();
    this->selectShader->SetFloatVecUniform3fv( "baseColor", glm::vec3( 1.0f, 0.0f, 0.0f ) );

    this->shader1 = new Shader( "sprite.vert", "sprite.frag" );
    this->shader1->Activate();
    this->shader1->SetFloatVecUniform3fv( "baseColor", glm::vec3( 1.0f, 1.0f, 0.0f ) );
    
    this->shader2 = new Shader( "sprite.vert", "sprite.frag" );
    this->shader2->Activate();
    this->shader2->SetFloatVecUniform3fv( "baseColor", glm::vec3( 1.0f, 0.0f, 1.0f ) );

    this->shader3 = new Shader( "sprite.vert", "sprite.frag" );
    this->shader3->Activate();
    this->shader3->SetFloatVecUniform3fv( "baseColor", glm::vec3( 0.0f, 1.0f, 1.0f ) );
    
    this->primitives = new Primitives();

    this->groundRectangle = new Rectangle( *this->primitives, 10.0f, 0.4f );
    this->groundRectangle->Translate( glm::vec3( 0, -2.7f, 0 ) );

    this->ceilRectangle = new Rectangle( *this->primitives, 10.0f, 0.4f );
    this->ceilRectangle->Translate( glm::vec3( 0, 2.7f, 0 ) );

    this->pillarManager = new PillarManager( *this->primitives, glm::vec3 ( 5.0f, 0, 0 ) );
    this->rects = this->pillarManager->GetAllRectangles();

    // Construct NeuroEvolution Object
    this->neuroEvolution = new NeuroEvolution();
    this->ShouldPlayWorld = true;
    std::cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ World Constructed ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
}

void World::Start() {
    //std::cout << "\nWorld Start";
    this->neuroEvolution->Initiate();
    this->Initiate();
    // this->neuroEvolution->Initiate();
    // this->neuroEvolution->Speciate();
    // this->neuroEvolution->CrossOver();
    // this->neuroEvolution->SaveGenomesToJSON();
}

void World::Update() {
    if( 
        this->neuroEvolution->currentGeneration > this->neuroEvolution->MAXGENS 
    ) this->ShouldPlayWorld = false;

    //std::cout << "\nGen: " << this->neuroEvolution->currentGeneration;
    // Play the game

    // Check If all the organisms have collided
    if( this->IsDead() ) {
        this->neuroEvolution->SaveGenomesToJSON();
        // Perform Speciation 
        this->neuroEvolution->Speciate();
        // Perform crossover of the best parents
        this->neuroEvolution->CrossOver();
        // Restart the world with the  new offsprings
        this->Restart();
    }

    this->camera->UpdateMatrix( 60.0f, 0.1f, 100.0f );
    
    // Update Calls

    // Update PillarManager
    this->pillarManager->Update();

    // For each organism
    for( int i = 0; i < this->circles.size(); ++i ) {
        if( !this->circles[i]->isAlive ) continue;

        // Apply Gravity on all organisms
        this->circles[i]->ApplyForce( glm::vec3( 0, gravity, 0 ) );

        Pillar& pillar = this->pillarManager->GetNearestPillarTo( 
            this->circles[i]->translation
        );

        pillar.IsSelected = true;

        float xDistance = 
            pillar.GetXPos() -
            pillar.pillarWidth / 2 -
            this->circles[i]->translation.x;   

        if( ( xDistance + pillar.pillarWidth ) <= 0.1f ) {
            this->circles[i]->CrossedPillar();
        } 

        float yUpperPillarDistance = 
            pillar.GetYPos() - pillar.gapDistance / 2;

        yUpperPillarDistance = //std::abs(
            yUpperPillarDistance - this->circles[i]->translation.y ;
        //);

        float yLowerPillarDistance = 
            pillar.GetYPos() + pillar.gapDistance / 2;

        yLowerPillarDistance = //std::abs(
            yLowerPillarDistance - this->circles[i]->translation.y ;
        //);

        float yCeilDistance = std::abs(
            ( this->ceilRectangle->translation.x + 
            this->ceilRectangle->width / 2 ) -
            this->circles[i]->translation.y
        );

        float yGroundDistance = std::abs(
            ( this->groundRectangle->translation.x + 
            this->groundRectangle->width / 2 ) -
            this->circles[i]->translation.y
        );

        // make a decision as to jump or not
        if ( 
            this->circles[i]->Predict( 
                xDistance, 
                yUpperPillarDistance, 
                yLowerPillarDistance, 
                yCeilDistance,
                yGroundDistance,
                pillar.GetYPos()
            )
        ) {
            this->circles[i]->Jump();
        }

        // if ( 
        //     glfwGetKey( &this->window, GLFW_KEY_SPACE ) == GLFW_PRESS && 
        //     !this->circle->hasBrain 
        // ) {
        //     this->circle->Jump();
        // } 

        // Update all organisms
        this->circles[i]->Update();
        // Draw all organisms
        this->circles[i]->DrawInstance( *shaderProgram, *camera );
        this->circles[i]->DrawDebugView( *shader1, *shader2, *shader3, *camera );
    }
    
    // Draw ground
    this->groundRectangle->Draw( *shaderProgram, *camera );
    // Draw ceiling
    this->ceilRectangle->Draw( *shaderProgram, *camera );
    // Draw Pillars
    this->pillarManager->Draw( *shaderProgram, *selectShader, *camera );
}

void World::Destroy() {
    std::cout << "\nWorld Destroy\n";
}

void World::Restart() {
    // Reinitialize setup
    this->Initiate();
    // Reset Pillars
    this->pillarManager->Reset();
}

bool World::IsDead() {
    // For all organisms
    for( int i = 0; i < this->circles.size() && this->lifeCount > 0; ++i ) {
        if( this->circles[i]->isAlive ) {
            bool hasCollided = false;
            // if the organism collides 
            if( this->circles[i]->CheckCollision( *this->groundRectangle ) || 
                this->circles[i]->CheckCollision( *this->ceilRectangle ) 
            ) {
                //this->shaderProgram->SetFloatVecUniform3fv( "baseColor", glm::vec3( 1.0f, 0.0f, 0.0f ) );
                hasCollided = true;
            }

            for( int j = 0; j < this->rects.size() && !hasCollided ; ++j ) {
                if( this->circles[i]->CheckCollision( *this->rects[j] ) ) {
                    //this->shaderProgram->SetFloatVecUniform3fv( "baseColor", glm::vec3( 1.0f, 0.0f, 0.0f ) );
                    hasCollided = true;
                }
            }

            if( hasCollided ) {
                // Reduce the living count
                this->lifeCount--;
                // Evaluate the fitness of the organism based on the distance traveled, the energy spent and the brain size
                float fitness = this->circles[i]->CalculateFitness();
                // Set the genome index fitness
                this->neuroEvolution->SetGenomeFitness( 
                    this->circles[i]->id, fitness 
                );
                // Remove the organism from the scene
                this->circles[i]->isAlive = false;
            }       
        } 
    }
       
    // If living count is zero return true
    return this->lifeCount <= 0;
}

void World::Initiate() {
   
    int genomeSize = this->neuroEvolution->genomes.size();
    this->lifeCount = genomeSize;
    std::cout << "\nGen: " << this->neuroEvolution->currentGeneration << ", Life count: " << this->lifeCount;
    std::cout << "\nSpecies Count: " << this->neuroEvolution->SpeciesCount();
    this->clearCircles();
    // For each genome in the neuroevolution
    for( int i = 0; i < genomeSize; ++i ) {
        // Create a new circle with a brain and store it in the circle array
        Circle* circle = new Circle( 
            *this->neuroEvolution->genomes[i],
            this->organismRadius
        );
        // Reset the positions of all the organisms
        circle->ResetPosition();
        this->circles.push_back( circle );
    }
      
}

void World::clearCircles() {
    for(int i = 0; i < this->circles.size(); ++i ) {
        delete this->circles[i];
    } 
    this->circles.clear();
}

World::~World() {
    delete this->camera;
    delete this->shaderProgram;

    this->clearCircles();

    delete this->groundRectangle;
    delete this->ceilRectangle;
    delete this->primitives;
    delete this->pillarManager;
}
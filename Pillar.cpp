#include "Pillar.h"

Pillar::Pillar( const Primitives& primitives, glm::vec3 iPosition ) {

    this->upperRect = new Rectangle( 
        primitives, 
        Globals::PILLAR_WIDTH, 
        Globals::PILLAR_HEIGHT 
    );

    this->lowerRect = new Rectangle( 
        primitives, 
        Globals::PILLAR_WIDTH, 
        Globals::PILLAR_HEIGHT 
    );

    this->initialPosition = iPosition;

    this->Reset();
}

void Pillar::Spawn() {
    this->initialPosition.y = Mathematics::RandomInRange( 
        -Globals::Y_BOUND_DISTANCE, Globals::Y_BOUND_DISTANCE 
    );
    this->translation = this->initialPosition;
    this->shouldMove = true;
    //std::cout << "Spawn Time: " << this->spawnTime << std::endl;
}

void Pillar::Update() {
    
    //std::cout << "Time Difference: " << difftime( this->timer, this->startTime ) << std::endl; 
  
    if( this->shouldMove ) {
        this->translation += this->currentVelocity;
        this->MoveRectangles();
    }
        
    if( this->translation.x <= Globals::X_RESPAWN_LOCATION ) {
        this->shouldMove = false;
    }

    
}

void Pillar::Draw( Shader& shader, Camera& camera ) {
    if( this->shouldMove ) {
        this->upperRect->Draw( shader, camera );
        this->lowerRect->Draw( shader, camera );
    }
    if( this->IsSelected ) this->IsSelected = false;
}

void Pillar::Reset() {
    this->currentVelocity = glm::vec3( Globals::I_PILLAR_VELOCITY, 0, 0 );  
    this->translation = this->initialPosition;
    this->shouldMove = false;
    this->MoveRectangles();
}

void Pillar::MoveRectangles() {
    this->upperRect->MoveTo( 
        glm::vec3( 
            this->translation.x, 
            this->translation.y + 
                ( Globals::PILLAR_HEIGHT + Globals::UPPER_LOWER_GAP ) / 2, 
            0 
        ) 
    );
    this->lowerRect->MoveTo( 
        glm::vec3( 
            this->translation.x,
            this->translation.y +  
                -( Globals::PILLAR_HEIGHT + Globals::UPPER_LOWER_GAP ) / 2, 
            0 
        ) 
    );
}

void Pillar::IncreaseVelocity() {
    this->currentVelocity += glm::vec3( -Globals::PILLAR_ACCEL, 0, 0 );
}

float Pillar::GetXPos() {
    return this->translation.x;
}

float Pillar::GetYPos() {
    return this->translation.y;
}

bool Pillar::CanMove() {
    return this->shouldMove;
}

float Pillar::GetCurrentVelocity() {
     return -this->currentVelocity.x;
}

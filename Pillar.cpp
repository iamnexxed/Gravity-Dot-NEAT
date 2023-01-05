#include "Pillar.h"

Pillar::Pillar( const Primitives& primitives, glm::vec3 iPosition ) {

    this->upperRect = new 
    Rectangle( 
        primitives, 
        this->pillarWidth, 
        this->pillarHeight 
    );

    this->lowerRect = new
     Rectangle( 
        primitives, 
        this->pillarWidth, 
        this->pillarHeight 
    );

    this->initialPosition = iPosition;

    this->Reset();
}

void Pillar::Spawn() {
    this->initialPosition.y = Mathematics::RandomInRange( -yBoundDistance, yBoundDistance );
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
        
    if( this->translation.x <= this->respawnXLocation ) {
        this->shouldMove = false;
    }

    
}

void Pillar::Draw( Shader& shader, Camera& camera ) {
    if( this->shouldMove ) {
        this->upperRect->Draw( shader, camera );
        this->lowerRect->Draw( shader, camera );
    }

}

void Pillar::Reset() {
    this->currentVelocity = this->initialVelocity;    
    this->translation = this->initialPosition;
    this->shouldMove = false;
    this->MoveRectangles();
}

void Pillar::MoveRectangles() {
    this->upperRect->MoveTo( 
        glm::vec3( 
            this->translation.x, 
            this->translation.y + 
                ( this->pillarHeight + this->gapDistance ) / 2, 
            0 
        ) 
    );
    this->lowerRect->MoveTo( 
        glm::vec3( 
            this->translation.x,
            this->translation.y +  
                -( this->pillarHeight + this->gapDistance ) / 2, 
            0 
        ) 
    );
}

void Pillar::IncreaseVelocity() {
    this->currentVelocity += glm::vec3( -this->acceleration, 0, 0 );
}

float Pillar::GetXPos() {
    return this->translation.x;
}

bool Pillar::CanMove() {
    return this->shouldMove;
}

float Pillar::GetCurrentVelocity() {
     return -this->currentVelocity.x;
}

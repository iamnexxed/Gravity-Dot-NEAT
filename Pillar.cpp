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
    //std::cout << "Spawn Time: " << this->spawnTime << std::endl;
}

void Pillar::Update() {
    
    //std::cout << "Time Difference: " << difftime( this->timer, this->startTime ) << std::endl; 
  
    if( shouldMove ) {
        this->translation += this->currentVelocity;
        this->MoveRectangles();
    }
        
    

    
}

void Pillar::Draw( Shader& shader, Camera& camera ) {
    if( shouldMove ) {
        this->upperRect->Draw( shader, camera );
        this->lowerRect->Draw( shader, camera );
    }

}

void Pillar::Reset() {
    this->currentVelocity = this->initialVelocity;    
    this->shouldMove = false;
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
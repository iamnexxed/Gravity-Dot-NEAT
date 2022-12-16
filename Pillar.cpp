#include "Pillar.h"

Pillar::Pillar( 
        const Primitives& primitives, 
        float initialVelocity, 
        float gap
    ) : 
    initialVelocity( initialVelocity ), 
    gapDistance ( gap ) {

    this->upperRect = new Rectangle( primitives, this->pillarWidth, this->pillarHeight );
    this->upperRect->Translate( glm::vec3( 0, ( this->pillarHeight + this->gapDistance ) / 2, 0 ) );

    this->lowerRect = new Rectangle( primitives, this->pillarWidth, this->pillarHeight );
    this->lowerRect->Translate( glm::vec3( 0, -( this->pillarHeight + this->gapDistance ) / 2, 0 ) );
}

void Pillar::Spawn() {

}

void Pillar::Update() {

}

void Pillar::Draw( Shader& shader, Camera& camera ) {
    this->upperRect->Draw( shader, camera );
    this->lowerRect->Draw( shader, camera );
}

void Pillar::Reset() {
    
}
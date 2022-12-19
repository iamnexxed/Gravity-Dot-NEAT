#include "PillarManager.h"

PillarManager::PillarManager( const Primitives& primitives, glm::vec3 iPosition ) {
    for( int i = 0; i < this->numOfPillars; ++i ) {
        this->pillars.push_back(
            new Pillar( 
                primitives, 
                iPosition
            ) 
        );
        // Push all the pillars to the queue
        this->queue.push(this->pillars[i]);
    }

    
}

void PillarManager::Update() {
    time(&this->timer);
    if( difftime( this->timer, this->startTime ) >= this->spawnTime ) {
        // Pop front from queue and start moving
    }

    // If the pillar goes off screen push it back to the queue
    // if( this->translation.x <= this->respawnXLocation ) {
    //         this->Spawn();
    // }
}

void PillarManager::Draw( Shader& shader, Camera& camera ) {
    for( int i = 0; i < this->numOfPillars; ++i)
        this->pillars[i]->Draw( shader, camera );
}

void PillarManager::Reset() {
    time( &this->startTime ); 
    for( int i = 0; i < this->numOfPillars; ++i)
        this->pillars[i]->Reset();
}

PillarManager::~PillarManager() {
    for( int i = 0; i < this->numOfPillars; ++i )
        delete this->pillars[i];
}
#include "PillarManager.h"

PillarManager::PillarManager( const Primitives& primitives, glm::vec3 iPosition ) {
    for( int i = 0; i < Globals::PILLAR_COUNT; ++i ) {
        this->pillars.push_back(
            new Pillar( 
                primitives, 
                iPosition
            ) 
        );
        
    }
    this->Reset();
    
}

void PillarManager::Update() {
    time( &this->timer );
   
    // std::cout << "\nPillar Queue size: " << this->queue.size();
    
    if(
        difftime( this->timer, this->startTime ) >= 
        Globals::PILLAR_SPAWN_TIME 
    ) {
        if( !this->queue.empty() ) {
            this->pillars[this->queue.front()]->Spawn();
            this->pillars[this->queue.front()]->IsInQueue = false;
            this->queue.pop();
            time( &this->startTime ); 
            //this->IncreaseVelocity();
        }
    }

    for( int i = 0; i < this->pillars.size(); ++i ) {

        this->pillars[i]->Update();
        if( !this->pillars[i]->CanMove() && !this->pillars[i]->IsInQueue ) {
            this->queue.push( i );
            // std::cout << "\nPushed: " << i;
            this->pillars[i]->IsInQueue = true;
        }
        
    }

}

void PillarManager::Draw( Shader& shader, Camera& camera ) {
    for( int i = 0; i < Globals::PILLAR_COUNT; ++i ) 
            this->pillars[i]->Draw( shader, camera );
}

void PillarManager::Draw( Shader& shader1, Shader& shader2, Camera& camera ) {
    for( int i = 0; i < Globals::PILLAR_COUNT; ++i ) {
        if( this->pillars[i]->IsSelected ) {
            this->pillars[i]->Draw( shader2, camera );
        } else {
             this->pillars[i]->Draw( shader1, camera );
        }


    }
}

void PillarManager::Reset() {
    time( &this->startTime ); 
    for( int i = 0; i < Globals::PILLAR_COUNT; ++i ) {
        // Push all the pillars to the queue
        if( !this->pillars[i]->IsInQueue ) {
            this->queue.push( i );
            this->pillars[i]->IsInQueue = true;
        }
        this->pillars[i]->Reset();
    }
        
}

std::vector<Rectangle*> PillarManager::GetAllRectangles() {
    std::vector<Rectangle*> rects;
    for( int i = 0; i < Globals::PILLAR_COUNT; ++i ) {
        rects.push_back( pillars[i]->lowerRect );
        rects.push_back( pillars[i]->upperRect );
    }
    return rects;
}

void PillarManager::IncreaseVelocity() {
    for( int i = 0; i < Globals::PILLAR_COUNT; ++i ) {
        pillars[i]->IncreaseVelocity();
    }
}

float PillarManager::GetVelocity() {
    return pillars[0]->GetCurrentVelocity();
}

Pillar& PillarManager::GetNearestPillarTo( const glm::vec3& position ) {
    float xDist = INFINITY;
    Pillar* pillar = this->pillars[0];
    for( int i = 0; i < Globals::PILLAR_COUNT; ++i ) {
        float x = this->pillars[i]->GetXPos() +
                Globals::PILLAR_WIDTH / 2; 
        if( x > position.x ) {
            float dist = x - position.x;
            if( dist < xDist ) {
                xDist = dist;
                pillar = this->pillars[i];
            }
        }
    }
    return *pillar;
}

PillarManager::~PillarManager() {
    for( int i = 0; i < Globals::PILLAR_COUNT; ++i )
        delete this->pillars[i];
}
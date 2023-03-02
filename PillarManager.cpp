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
        this->queue.push( i );
        
    }
    this->Reset();
    
}

void PillarManager::Update() {
    time( &this->timer );
   
        
    
    if( difftime( this->timer, this->startTime ) >= 
        ( ( this->spawnTime ) ) ) {
        if( !this->queue.empty() ) {
            this->pillars[this->queue.front()]->Spawn();
            this->queue.pop();
            time( &this->startTime ); 
            //this->IncreaseVelocity();
        }
    }

    for( int i = 0; i < this->pillars.size(); ++i ) {

        this->pillars[i]->Update();
        if( !this->pillars[i]->CanMove() ) {
            this->queue.push( i );
        }
        
    }

}

void PillarManager::Draw( Shader& shader, Camera& camera ) {
    for( int i = 0; i < this->numOfPillars; ++i ) 
            this->pillars[i]->Draw( shader, camera );
}

void PillarManager::Draw( Shader& shader1, Shader& shader2, Camera& camera ) {
    for( int i = 0; i < this->numOfPillars; ++i ) {
        if( this->pillars[i]->IsSelected ) {
            this->pillars[i]->Draw( shader2, camera );
        } else {
             this->pillars[i]->Draw( shader1, camera );
        }


    }
}

void PillarManager::Reset() {
    time( &this->startTime ); 
    for( int i = 0; i < this->numOfPillars; ++i )
        this->pillars[i]->Reset();
}

std::vector<Rectangle*> PillarManager::GetAllRectangles() {
    std::vector<Rectangle*> rects;
    for( int i = 0; i < this->numOfPillars; ++i ) {
        rects.push_back( pillars[i]->lowerRect );
        rects.push_back( pillars[i]->upperRect );
    }
    return rects;
}

void PillarManager::IncreaseVelocity() {
    for( int i = 0; i < this->numOfPillars; ++i ) {
        pillars[i]->IncreaseVelocity();
    }
}

float PillarManager::GetVelocity() {
    return pillars[0]->GetCurrentVelocity();
}

Pillar& PillarManager::GetNearestPillarTo( const glm::vec3& position ) {
    float xDist = INFINITY;
    Pillar* pillar = this->pillars[0];
    for( int i = 0; i < this->numOfPillars; ++i ) {
        if( this->pillars[i]->GetXPos() > position.x ) {
            float dist = this->pillars[i]->GetXPos() - position.x;
            if( dist < xDist ) {
                xDist = dist;
                pillar = this->pillars[i];
            }
        }
    }
    return *pillar;
}

PillarManager::~PillarManager() {
    for( int i = 0; i < this->numOfPillars; ++i )
        delete this->pillars[i];
}
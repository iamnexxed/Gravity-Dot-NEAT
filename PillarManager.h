#ifndef PILLAR_MANAGER_CLASS_H
#define PILLAR_MANAGER_CLASS_H

#include "Pillar.h"
#include <time.h> 
#include <queue>

class PillarManager {
    private:
        std::vector<Pillar*> pillars;
        std::queue<int> queue;
        const int numOfPillars = 5;
        const float respawnXLocation = -5.0f;
        const float spawnTime = 2.0f;
        time_t startTime;
        time_t timer;

    public:
        PillarManager( const Primitives& primitives, glm::vec3 iPosition );
        void Update();
        void Draw( Shader& shader, Camera& camera );
        void Reset();
        ~PillarManager();

};


#endif

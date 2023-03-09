#ifndef PILLAR_MANAGER_CLASS_H
#define PILLAR_MANAGER_CLASS_H

#include "Pillar.h"
#include <time.h> 
#include <queue>

class PillarManager {
    private:
        std::vector<Pillar*> pillars;
        std::queue<int> queue;
        time_t startTime;
        time_t timer;

    public:
        PillarManager( const Primitives& primitives, glm::vec3 iPosition );
        void Update();
        void Draw( Shader& shader, Camera& camera );
        void Draw( Shader& shader1, Shader& shader2, Camera& camera );
        void Reset();
        ~PillarManager();
        std::vector<Rectangle*> GetAllRectangles();
        void IncreaseVelocity();
        float GetVelocity();
        float GetPillarPosX( int index );
        Pillar& GetNearestPillarTo( const glm::vec3& position );

};


#endif

#ifndef MATHEMATICS_CLASS_H
#define MATHEMATICS_CLASS_H

#include <glm/glm.hpp>
#include <stdlib.h>
#include <time.h>
#include <cmath>

#define PI 3.1415927
#define E 2.718281828

class Mathematics
{
    public:

    static glm::vec3 GetRandomPointOnSphere( float radius ) {
        int lon, lat;
        

        lat = rand() % 180;
        lon = rand() % 360;
        // Reference: https://stackoverflow.com/questions/39937628/howto-use-glm-constants-in-c-opengl
        float theta = lat * PI / 180.0f;
        float phi = lon * PI / 180.0f;
        float x = radius * std::sin( theta ) * std::cos( phi );
        float y = radius * std::sin( theta ) * std::sin( phi );
        float z = radius * std::cos( theta) ;

        return glm::vec3( x, y, z );
    }

    static float RandomInRange( float min, float max ) {
        if( min >= max ) return min;
        return min + 
            static_cast <float> ( rand() ) / 
                ( static_cast <float> ( RAND_MAX / ( max - min ) ) );
    }

    // Reference: https://www.simplilearn.com/tutorials/cpp-tutorial/random-number-generator-in-cpp
    static int RandomInRange( int min, int max ) {
        if( min >= max ) return min;
        return min + ( rand() % ( max - min + 1 ) );
    }

    static float Map(
        float currentVal, 
        float prevMin, 
        float prevMax, 
        float newMin, 
        float newMax
    ) {
        return (
            newMin + (newMax - newMin) / (prevMax - prevMin) * (
                currentVal - prevMin
            )
        );
    }

    static float Clamp( float value, float min, float max ) {
        if( value < min ) {
            return min;
        } else if( value > max ) {
            return max;
        }
        return value;
    }
};



#endif 

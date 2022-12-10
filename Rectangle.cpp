#include "Rectangle.h"

Rectangle::Rectangle( glm::vec3 min, glm::vec3 max ) {
    this->minBound = min;
    this->maxBound = max;
    this->center.x = ( min.x + max.x) / 2;
    this->center.y = ( min.y + max.y) / 2;
    this->width = max.x - min.x;
    this->height = max.y - min.y;


}

Rectangle::Rectangle( glm::vec3 center, float width, float height ) {
    this->center = center;
    this->width = width;
    this->height = height;

    this->minBound.x = center.x - width / 2;
    this->minBound.y = center.y - height / 2;

    this->maxBound.x = center.x + width / 2;
    this->maxBound.y = center.y + height / 2;
}

void Rectangle::Draw( Primitives& primitive, Shader& shader, Camera& camera ) {
    primitive.DrawRectangle( 
        shader, 
        camera, 
        this->matrix, 
        this->translation, 
        this->scale
    );
}
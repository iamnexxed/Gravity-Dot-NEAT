#include "Rectangle.h"

Rectangle::Rectangle( 
    const Primitives& primitives, 
    float width,
    float height ) : 
    primitives( primitives ), 
    width( width ), 
    height( height ) {
    this->scale.x = width / 2;
    this->scale.y = height / 2;
    this->UpdateBounds();
}

void Rectangle::UpdateBounds() {
    this->minBound.x = this->translation.x - this->width / 2;
    this->minBound.y = this->translation.y - this->height / 2;

    this->maxBound.x = this->translation.x + this->width / 2;
    this->maxBound.y = this->translation.y + this->height / 2;
}

void Rectangle::Draw( Shader& shader, Camera& camera ) {
    this->primitives.DrawRectangle( 
        shader, 
        camera, 
        this->matrix, 
        this->translation, 
        this->rotation,
        this->scale
    );
}

void Rectangle::Translate( glm::vec3 displacementVec ) {
    this->translation += displacementVec;
    this->UpdateBounds();
}
#include "blades.hpp"
#include <raylib.h>
#include <iostream>

Texture2D blades::sprite;
blades::blades(Vector2 position, float rotationAngle, Vector2 generalPos){
    this->position = position;
    this->rotationAngle = rotationAngle;
    this->GeneralPos = generalPos;
    rta = 0;
    if (sprite.id == 0){
        sprite = LoadTexture("sprites/blades.png");
    }
}

blades::~blades(){
    UnloadTexture(sprite);
}

void blades::draw(){
    Rectangle sourceRec = {0.0f, 0.0f, (float)sprite.width, (float)sprite.height};
    Vector2 origin = {(float)sprite.width/2, 0};
    Vector2 translatePos = Vector2Subtract(position, GeneralPos);
    Vector2 rposition = Vector2Rotate(translatePos, (rta)*(PI/180));
    Rectangle desRec = {GeneralPos.x+rposition.x, GeneralPos.y+rposition.y, (float)sprite.width, (float)sprite.height};
    DrawTexturePro(sprite, sourceRec, desRec, origin, rta+rotationAngle, WHITE);
}


void blades::setPosRelGeneral(Vector2 pos, Vector2 generalPos, float rotation){
    position = pos;
    GeneralPos = generalPos;
    rta = rotation;
}
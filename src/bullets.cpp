#include "bullets.h"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "game.hpp"
#include "explosion.hpp"

using namespace std;

Texture2D Bullets::sprites[5] = {};

Bullets::Bullets(Vector2 pos, int type, Vector2 bulletVelocity)
{
    this->destroyed = false;
    this->position = pos; // Set position to the passed parameter
    this->type = type;
    this->velocity = bulletVelocity; // Normalize the velocity
    this->rotation = atan2f(velocity.y, velocity.x) * (180 / PI); // Calculate rotation based on normalized velocity
    if (sprites[0].id == 0) {
        loadTexture();
    }

    if (type == 5) {
        explosive = true;
        explosionRadius = 500;
    } 
    else {
        explosive = false;
        explosionRadius = 0;
    }

    hitCircleCenter = {position.x + (float)sprites[type-1].width / 4, position.y + (float)sprites[type-1].height / 4};
}

Bullets::~Bullets()
{
}

void Bullets::loadTexture(){
    sprites[0] = LoadTexture("sprites/alienBullet-1.png");
    sprites[1] = LoadTexture("sprites/alienBullet-2.png");
    sprites[2] = LoadTexture("sprites/alienBullet-3.png"); 
    sprites[3] = LoadTexture("sprites/sentinal-bullet.png"); 
    sprites[4] = LoadTexture("sprites/spear.png"); 
}

void Bullets::draw(){
    DrawTexturePro(sprites[type-1], {0, 0, (float)sprites[type-1].width, (float)sprites[type-1].height}, {position.x, position.y, (float)sprites[type-1].width, (float)sprites[type-1].height}, {(float)sprites[type-1].width/2, (float)sprites[type-1].height/2}, this->rotation-90, WHITE);
    // DrawCircleV(position, 20, WHIsTE);
}

void Bullets::update(){
    this->position = Vector2Add(velocity, this->position);
    // if bullets are out of hte screen flag them destroyed;
    if (position.x < 0 || position.x > GetScreenWidth() || position.y < 0 || position.y > 800) {
        destroyed = true;
    }
}

void Bullets::collided() {
    if (type == 5){
        Game::addActiveExplosion(Explosion({this->position, 200}));
    }
}


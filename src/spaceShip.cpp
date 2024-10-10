#include "spaceShip.h"
#include "raylib.h"
#include "iostream"
#include "game.hpp"
#include "raymath.h"
#include "bullets.h"

using namespace std;

// Initialize the static member
Texture2D SpaceShip::sprites[] = {};

SpaceShip::SpaceShip(Vector2 pos, int t) { 
    direction = GetRandomValue(-1, 1) > 0 ? 1 : -1;
    hp = 3;
    wanderTime = 0;
    lastFireTime = 0;
    numberOfBullets = 10;
    bulletsLeft = 10;
    angle = 0;
    position = pos;
    type = t; // Default type
    switch (type) {
        case 1: 
            velocity = {2, 0};
            bulletdrection = {0, 4};
            numberOfBullets = 10;
            bulletsLeft = 10;
            break;
        case 2:
            velocity = {5, 0};
            numberOfBullets = 6;
            bulletsLeft = 6;
            bulletdrection = {0, 8};
            break;
        case 3:
            numberOfBullets = 6;
            bulletsLeft = 6;
            break;
    }
    if (sprites[0].id == 0) {
        LoadTextures();
    }    
}

SpaceShip::~SpaceShip(){
    for (Texture2D s : sprites) {
        UnloadTexture(s);
    }
}

void SpaceShip::LoadTextures() {
    sprites[0] = LoadTexture("sprites/basicAlien-1.png");
    sprites[1] = LoadTexture("sprites/basicAlien-2.png");
    sprites[2] = LoadTexture("sprites/Alien-3.png");
}

void SpaceShip::fire(){
    lastFireTime -= GetFrameTime();
    if (lastFireTime <= 0 && bulletsLeft != 0){
        if (type != 3){
            Game::addBullet(Bullets({position.x, position.y}, type, bulletdrection));  
        }
        if (type == 3){
            Vector2 sentinalPos = Game::getPlayerPosition();
            Vector2 bulletVelocity = Vector2Subtract(sentinalPos, {position.x, position.y});
            bulletVelocity = Vector2Normalize(bulletVelocity);
            bulletVelocity = Vector2Scale(bulletVelocity, 4);
            Game::addBullet(Bullets({position.x, position.y}, type, bulletVelocity));
        }
        bulletsLeft -= 1;
        lastFireTime = GetRandomValue(1, 2) * 60; // Set a random fire interval between 1 and 2 seconds
    }

    else if (bulletsLeft == 0) {
        // reload for 4 seconds
        lastFireTime = 3 * 60; // Set reload time to 4 seconds
        bulletsLeft = numberOfBullets;
    }
}

void SpaceShip::draw() {
    // Draw code here
    update();
    Rectangle sourcesRect = {0, 0, sprites[type-1].width, sprites[type-1].height};
    Rectangle destRect = {position.x, position.y, sprites[type-1].width, sprites[type-1].height};
    Vector2 origin = {sprites[type-1].width/2, sprites[type-1].height/2};
    if (type != 3) {
        DrawTexturePro(sprites[type-1], sourcesRect, destRect, origin, 0.0f, WHITE);
    }
    else {
        DrawTexturePro(sprites[type-1], sourcesRect, destRect, origin, angle-90, WHITE);
        DrawCircleV({position.x, position.y}, 50,ORANGE);
    }

    
}

void SpaceShip::unloadTextures() {
    cout << "unloading the textures" << endl;
}

void SpaceShip::wander(){
    wanderTime -= GetFrameTime();
    if(wanderTime <= 0){
        // cout << "direction changed" << endl;
        direction *= -1;
        wanderTime = GetRandomValue(3, 7);
        wanderTime = wanderTime * 60; // turn the time in seconds
    }
    position.x+= this->velocity.x * direction;
    if (position.x > GetScreenWidth() || position.x < 0) {
        wanderTime += 1;
        direction  *= -1;
    }
    // cout << wanderTime << endl;
}

void SpaceShip::freeWander() {
    wanderTime -= GetFrameTime();
    if (wanderTime <= 0) {
        // Change the velocity to be in a random direction
        // Vector2 direction = {(float)GetRandomValue(1, GetScreenWidth()), (float)GetRandomValue(1, 800)};
        float angle = GetRandomValue(0, 360) * (PI/180);
        velocity = {cosf(angle), sinf(angle)};
        velocity = Vector2Scale(velocity, 2);
        wanderTime = GetRandomValue(3, 5);
        wanderTime = wanderTime * 60;
    }
    position = Vector2Add(position, velocity);
    // If the spaceship is out of bounds, readjust its velocity to be within the screen
    if (position.x > GetScreenWidth() || position.x < 0 || position.y < 0 || position.y > 800) {
        // Adjust position to be within the screen
        // Change the direction and thus the velocity, within the screen
        Vector2 direction = {(float)GetRandomValue(GetScreenWidth()/4, (GetScreenWidth()*3)/4), (float)GetRandomValue(800/4, (800*3)/4)};
        velocity = Vector2Normalize(Vector2Subtract(direction, position));
        velocity = Vector2Scale(velocity, 4);
        wanderTime += 60;
    }
}

void SpaceShip::orientToPlayer(){
    Vector2 sentinalPos = Game::getPlayerPosition();
    // DrawCircleV({sentinalPos.x, sentinalPos.y}, 10, GREEN);
    Vector2 direction = Vector2Subtract(sentinalPos, position);
    angle = atan2f(direction.y, direction.x) * (180/PI);
}

void SpaceShip::update(){
    fire();
    if (type == 1 || type == 2){
        wander();
    }
    else{
        orientToPlayer();
        freeWander();
    }
}

Circle SpaceShip::getCollider() {
    Vector2 center;
    Circle collider;

    switch (type) {
    case 1:
        center = {position.x, position.y - 20};
        collider = {center, 50.0f};
        break;
    case 2:
        center = {position.x, position.y - 10};
        collider = {center, 40.0f};
        break;
    case 3:
        collider = {position, 50.0f};
        break;
    default:
        // Handle unexpected type values
        collider = {position, 0.0f}; // Default radius of 0.0f
        break;
    }
    return collider;
}

#pragma once
#include <raylib.h>
#include "blades.hpp"
#include <iostream>
#include "bullets.h"
#include <list>
#include <vector>

using namespace std;
class GeneralBlade {
private:
    Vector2 velocity;
    int Speed;
    int firedelay;
    static Texture2D bulletSprite;
    Vector2 sentinelPos;
    int totalWanderTime;
    float wanderTime;
    bool slash;
    Vector2 position;
    float rotationAngle;
    Vector2 normalVector;
    static Texture2D sprite;
    int rotationSpeed;
    int aimingTime;
    Vector2 slashDirection;
    void rotate();
    list<Bullets>bullets;
    void executeSlash();
    static void loadSprites();
public:
    blades* bladeOne;
    blades* bladeTwo;
    blades* bladeThree;
    blades* bladeFour;
    GeneralBlade(Vector2 position);
    ~GeneralBlade();
    void draw();
    void wander();
    void fireBullets();
    void beam();
    void update(Vector2 sentinelPos, float widthOffset, float heightOffset);
};
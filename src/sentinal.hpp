#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "spear.hpp"
using namespace std;
class sentinal
{
private:
    Rectangle hitbox;
    Vector2 velocity;
    Vector2 normalizedMouseDir;
    float orientation;
    unsigned short speed;
    float thrustSpeed;
    float thrustSpeedRetardation;
    bool thrustLeft;
    bool thrustRight;
    bool thrust;
    bool specialMoveOn;
    bool frenzy;
    Vector2 frenzyCenter;
    unsigned short frenzyRabius;
    float frenzyAngle;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    float frameTimer;
    Texture2D sentinalSprite;
    Texture2D sentinalThrustSprites;
    Texture2D sentinalSpear;
    vector<Vector2> bullets;
    vector<Spear*> spears;
    void orientToMouse();
public:
    int hp;
    Vector2 position;
    Texture2D sentinalIdleSprite;
    void draw();
    void update();
    sentinal(Vector2 pos);
    ~sentinal();
};

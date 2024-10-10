#pragma once
#include <iostream>
#include <raylib.h>

class Explosion {
private:
    Circle hitbox;
    static Texture2D spriteSheet;
    float frameTimer = 0.06f;
    int frameCount = 6;
    float activeFrame = 0.0f;
    int frameWidth;
    bool active;
public:
    Explosion(Circle hitbox);
    ~Explosion();
    static void LoadSprite();
    void draw();
    void update();
    bool isActive();
};

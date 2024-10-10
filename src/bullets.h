#pragma once
#include <raylib.h>
class Bullets
{
private:
    Vector2 velocity;
    float rotation;
    int explosionRadius;
    int type;
    Vector2 hitCircleCenter;
    static Texture2D sprites[5];
    static void loadTexture();
public:
    Vector2 position;
    Bullets(Vector2 position, int type, Vector2 bulletVelocity);
    ~Bullets();
    void draw();
    void collided();
    void update();
    bool destroyed;
    bool explosive;
};



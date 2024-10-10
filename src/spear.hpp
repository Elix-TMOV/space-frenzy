#pragma once
#include <raylib.h>
#include <raymath.h>
class Spear {
private:
    // Rectangle hitbox;
    Vector2 position;
    Vector2 velocity;
    Rectangle hitbox;
    Texture2D* sprite;
public:
    Spear(Vector2 position, Texture2D* sprite){
        this->position = position;
        this->sprite = sprite;
        velocity = {0, -15};
        hitbox = {position.x, position.y, (float)sprite->width, (float)sprite->height-30};
    }
    void update() {
        position = Vector2Add(position, velocity);
    }
    void draw() {
        // update();
        DrawRectangleRec(hitbox, WHITE);
        DrawTextureEx(*sprite, position, 0.0f, 1, WHITE);
    }
};
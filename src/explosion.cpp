#include "explosion.hpp"

// Define the static member variable
Texture2D Explosion::spriteSheet = {};

Explosion::Explosion(Circle hitbox) {
    this->hitbox = hitbox; // Assuming a radius of 10 for the hitbox
    if (spriteSheet.id == 0) {
        LoadSprite();
    }
    frameWidth = spriteSheet.width / frameCount;
    active = true;
}

Explosion::~Explosion() {
    // Destructor
}

void Explosion::LoadSprite() {
    spriteSheet = LoadTexture("sprites/explosion.png");
}

void Explosion::draw() {
    // Implement drawing logic here
    Rectangle source = { frameCount * frameWidth, 0, frameWidth, spriteSheet.height };
    Rectangle dest = { hitbox.center.x, hitbox.center.y, frameWidth, spriteSheet.height };
    Vector2 origin = { frameWidth / 2, spriteSheet.height / 2 };
    DrawTexturePro(spriteSheet, source, dest, origin, 0.0f, WHITE);
    activeFrame += GetFrameTime();
    if (activeFrame >= frameTimer) {
        // std::cout << "time to change" << std::endl;
        activeFrame = 0;
        if (frameCount != 5) {
            frameCount = (frameCount + 1) % 6;
        }
        else {
            active = false;
        }
    }
}

void Explosion::update() {
    // Implement update logic here
}

bool Explosion::isActive() {
    return active;
}

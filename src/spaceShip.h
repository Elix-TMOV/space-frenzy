#pragma once
#include <raylib.h>


class SpaceShip {
private:
    int type;
    int numberOfBullets;
    int bulletsLeft;
    int wanderTime;
    int direction;
    int lastFireTime;
    float angle;
    bool freeMovement;
    Vector2 bulletdrection;
    Vector2 position;
    Vector2 velocity;
    Rectangle hitbox;
    Texture2D* sprite;
    static Texture2D sprites[];
    static void LoadTextures();
    static void unloadTextures();
public:
    SpaceShip(Vector2 pos, int type); // Constructor without type parameter
    ~SpaceShip();
    int hp;
    void freeWander();
    void wander();
    Circle getCollider();
    void draw();
    void update();
    void fire();
    void orientToPlayer();
};

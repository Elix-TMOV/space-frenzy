#pragma once
#include "sentinal.hpp"
#include "generalBlade.hpp"
#include "bullets.h"
#include "spaceShip.h"
#include <iostream>
#include <vector>
#include <list>
#include <raylib.h>
#include "bullets.h"
#include "explosion.hpp"
using namespace std;

class Game {
public:
    sentinal player;
    static vector<SpaceShip> aliens;
    static list<Bullets> bullets;
    static list<Bullets> playerBullets;
    static list<Explosion> activeExplosions;
    static Game& getInstance();
    static void addBullet(Bullets baullet);
    static void addPlayerBullet(Bullets bullet);
    static Vector2 getPlayerPosition();
    void update();
    void draw();
    static void addActiveExplosion(Explosion ex);
private:
    Game();
};
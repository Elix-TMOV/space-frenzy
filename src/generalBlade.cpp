#include "generalBlade.hpp"
#include <raylib.h>
#include <raymath.h>
#include <iostream>

using namespace std;

Texture2D GeneralBlade::sprite;

Texture2D GeneralBlade::bulletSprite;

GeneralBlade::GeneralBlade(Vector2 position){
    this->rotationAngle = 0;
    this->position = position;
    this->velocity = {0, 0};
    this->slashDirection = {200, 200};
    bullets = {};
    totalWanderTime = 12;
    rotationSpeed = 1;
    firedelay = 20;
    aimingTime = 30;
    slash = false;
    Speed = 5;
    if (sprite.id == 0) {
        loadSprites();
    }
    rotationAngle = 0.0f;
    bladeOne = new blades({this->position.x, this->position.y+50}, 0, {this->position.x, this->position.y});
    bladeTwo = new blades({this->position.x-50, this->position.y}, 90, {this->position.x, this->position.y});
    bladeThree = new blades({this->position.x, this->position.y-50}, 180, {this->position.x, this->position.y});
    bladeFour = new blades({this->position.x+50, this->position.y}, 270, {this->position.x, this->position.y});
}

GeneralBlade::~GeneralBlade() {}

void GeneralBlade::rotate() {}

void GeneralBlade::beam() {
    Vector2 cannon1 = Vector2Rotate({0,100}, (45+rotationAngle)*(PI/180));
    // cannon1 = Vector2Normalize(cannon1);
    // Vector2 cannon2 = Vector2Rotate({-100, 0}, (135+rotationAngle)*(PI/180));
    // Vector2 cannon3 = Vector2Rotate({0,-100}, (315+rotationAngle)*(PI/180));
    // Vector2 cannon4 = Vector2Rotate({100,0}, (45+rotationAngle)*(PI/180));

    int maxDimension = fmax(GetScreenWidth(), 800);
    for (int i = 1; i < maxDimension; i++) {
        Vector2 scaledDirection = Vector2Scale(cannon1, i);
        Vector2 beamHitBoxPos = Vector2Add(position, scaledDirection);
        DrawCircleV(beamHitBoxPos, 40, RED);
    }
}

void GeneralBlade::wander() {
    // Decrease wander time
    wanderTime -= GetFrameTime();
    if (wanderTime <= 0) {
        // Get a random direction vector
        float angle = GetRandomValue(0, 360) * (PI/180);
        Vector2 directionVector = {cosf(angle), sinf(angle)};
        this->velocity = Vector2Scale(Vector2Normalize(directionVector), Speed);
        // Compute the new wander time
        wanderTime = GetRandomValue(4, 6);
        totalWanderTime -= wanderTime;
    }
    // // Update position
    position = Vector2Add(position, velocity);
    // // Check boundaries
    if (position.x - (sprite.width / 2 + 10) < 0 || position.x + (sprite.width / 2 + 10) > GetScreenWidth() ||
        position.y - (sprite.height / 2 + 10) < 0 || position.y + (sprite.height / 2 + 10) > 800) {
        // Choose a random position within the inner window
        Vector2 randomPointInWindow = {GetRandomValue(GetScreenWidth() / 4, (GetScreenWidth() * 3) / 4),
                                       GetRandomValue(800 / 4, (800 * 3) / 4)};
        Vector2 direction = Vector2Subtract(randomPointInWindow, position);
        velocity = Vector2Scale(Vector2Normalize(direction), Speed);
    }
}

void GeneralBlade::loadSprites() {
    sprite = LoadTexture("sprites/boss-1.png");
    bulletSprite = LoadTexture("sprites/bossBullet-1.png");
}

void GeneralBlade::fireBullets(){
    firedelay -= GetFrameTime();
    if (firedelay <= 0){
        Vector2 cannon1 = Vector2Rotate({0,100}, (45+rotationAngle)*(PI/180));
        Vector2 cannon2 = Vector2Rotate({-100, 0}, (135+rotationAngle)*(PI/180));
        Vector2 cannon3 = Vector2Rotate({0,-100}, (315+rotationAngle)*(PI/180));
        Vector2 cannon4 = Vector2Rotate({100,0}, (45+rotationAngle)*(PI/180));
        // DrawCircleV(Vector2Add(position, cannon1), 10, BLUE);
        // DrawCircleV(Vector2Add(position, cannon2), 10, ORANGE);
        // DrawCircleV(Vector2Add(position, cannon3), 10, GREEN);
        // DrawCircleV(Vector2Add(position, cannon4), 10, PURPLE);
        Vector2 bullet1Velocity = Vector2Normalize(cannon1);
        bullet1Velocity = Vector2Scale(bullet1Velocity, 10);
        bullets.push_back(Bullets(Vector2Add(position, cannon1), 2, bullet1Velocity));

        Vector2 bullet2Velocity = Vector2Normalize(cannon2);
        bullet2Velocity = Vector2Scale(bullet2Velocity, 10);
        bullets.push_back(Bullets(Vector2Add(position, cannon2), 2, bullet2Velocity));

        Vector2 bullet3Velocity = Vector2Normalize(cannon3);
        bullet3Velocity = Vector2Scale(bullet3Velocity, 10);
        bullets.push_back(Bullets(Vector2Add(position, cannon3), 2, bullet3Velocity));

        Vector2 bullet4Velocity = Vector2Normalize(cannon4);
        bullet4Velocity = Vector2Scale(bullet4Velocity, 10);
        bullets.push_back(Bullets(Vector2Add(position, cannon4), 2, bullet4Velocity));
        firedelay = 20;
    }
    
}

void GeneralBlade::update(Vector2 sentPos, float widthOffset, float heightOffset) {
    sentinelPos = sentPos;
    Vector2 postoSentinal = Vector2Subtract(sentinelPos, position);
    float length = Vector2Length(postoSentinal);

    if (length <300){
        rotationSpeed = 20;
    }
    else {
        rotationSpeed = 1;
    }

    if (totalWanderTime > 0){
        if (slash == false){
            wander();
        }
    }
    else{
        totalWanderTime = 8;
        slash = true;
    }

    if (slash) {
        executeSlash();
    }
    // sentinelPos = {sentinelPos.x + widthOffset, sentinelPos.y + heightOffset};
    // Vector2 sentinelVector = Vector2Subtract(sentinelPos, position);
    // float angleBetween = atan2f(sentinelVector.y, sentinelVector.x) * (180.0f / PI);
    // float rotationSpeed = 4.0f * GetFrameTime();
    // rotationAngle = rotationAngle + rotationSpeed * (angleBetween - rotationAngle);
    
    rotationAngle = fmod(rotationAngle + rotationSpeed, 360.0f);
    bladeOne->setPosRelGeneral({position.x, position.y+50}, position, rotationAngle);
    bladeTwo->setPosRelGeneral({position.x-50, position.y}, position, rotationAngle);
    bladeThree->setPosRelGeneral({position.x, position.y-50}, position, rotationAngle);
    bladeFour->setPosRelGeneral({position.x+50, position.y}, position, rotationAngle);
    if (bullets.size() > 0){
        for (auto& bullet: bullets){
            bullet.update();
        }
    }
    fireBullets();
    // beam();
}

void GeneralBlade::draw() {
    Rectangle sourceRec = {0.0f, 0.0f, (float)sprite.width, (float)sprite.height};
    Rectangle desRec = {position.x, position.y, (float)sprite.width, (float)sprite.height};
    Vector2 origin = {(float)sprite.width / 2, (float)sprite.height / 2};
    DrawTexturePro(sprite, sourceRec, desRec, origin, rotationAngle, WHITE);
    bladeOne->draw();
    bladeTwo->draw();
    bladeThree->draw();
    bladeFour->draw();

    if (bullets.size() > 0){
        for (auto& bullet: bullets){
            bullet.draw();
        }
    }
}

void GeneralBlade::executeSlash(){
    rotationSpeed = 20;
    if (aimingTime > 0){
        aimingTime -= GetFrameTime();
        slashDirection = Vector2Subtract(sentinelPos, position);
        slashDirection = Vector2Normalize(slashDirection);
    }
    else if (slashDirection.x != 200){
        velocity = Vector2Scale(slashDirection, 20);
        position = Vector2Add(position, velocity);
    }
    if (position.x < 0 || position.x > GetScreenWidth() || position.y < 0 || position.y > 800){
        slash = false;
        aimingTime = 30;
        rotationSpeed = 2;
    }
}

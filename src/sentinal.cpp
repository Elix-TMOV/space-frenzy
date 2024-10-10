#include "sentinal.hpp"
#include "spear.hpp"
#include "game.hpp"
const short frameCount = 6;
const float frameTime = 0.1f;

sentinal::sentinal(Vector2 pos) {
    hp = 100;
    velocity = {0, 0};
    orientation = 0;
    position = pos;
    speed = 5;
    thrustSpeed = 12.0f;
    thrustSpeedRetardation = 1.4f;
    thrust = false;
    specialMoveOn = false;
    frenzy = false;
    frenzyCenter = {pos.x, pos.y - 100};
    frenzyRabius = 120;
    frenzyAngle = 90.0f;
    currentFrame = 0;
    frameTimer = 0.0f;
    sentinalSprite = LoadTexture("sprites/sentinalSpriteSheet.png");
    sentinalIdleSprite = LoadTexture("sprites/sentinalBasics.png");
    sentinalThrustSprites = LoadTexture("sprites/sentinalThrust.png");
    sentinalSpear = LoadTexture("sprites/spear.png");
    frameWidth = sentinalSprite.width / frameCount;
    frameHeight = sentinalSprite.height;
    // hitbox = {position.x - frameWidth/2, position.y - frameHeight/2, (float)(*frameWidth)/4, (float)frameHeight-20};
}

sentinal::~sentinal() {
        UnloadTexture(sentinalSprite);
        UnloadTexture(sentinalIdleSprite);
        UnloadTexture(sentinalThrustSprites);
        for (auto spear: spears){
            delete spear;
        }
    }

void sentinal::update() {
    // hitbox = {position.x - frameWidth/2, position.y - frameHeight/2, (float)(3*frameWidth)/4, (float)frameHeight-20};
    // DrawCircleV(position, 50, GREEN);
    Vector2 mousePosition = GetMousePosition();
    Vector2 mouseDirection = Vector2Subtract(mousePosition, position);
    normalizedMouseDir = Vector2Normalize(mouseDirection);
    orientToMouse();

    if (!specialMoveOn) {
        if (IsKeyDown(KEY_W)) {
            velocity = Vector2Scale(normalizedMouseDir, speed);
            position = Vector2Add(velocity, position);
        }
        if (IsKeyDown(KEY_S)) {
            position.y += speed;
        }
        if (IsKeyDown(KEY_A)) {
            position.x -= speed;
        }
        if (IsKeyDown(KEY_D)) {
            position.x += speed;
        }

        if (IsKeyPressed(KEY_J)) {
            velocity = Vector2Rotate(velocity, -90*(PI/180));
            specialMoveOn = true;
            thrust = true;
        }
        if (IsKeyPressed(KEY_F)) {
            velocity = Vector2Rotate(velocity, 90*(PI/180));
            specialMoveOn = true;
            thrust = true;
            Vector2 bulletposition = {position.x + 5, position.y + sentinalIdleSprite.height / 4 + 10};
            bullets.push_back(bulletposition);
        }
        if (IsKeyPressed(KEY_C)) {
            specialMoveOn = true;
            frenzy = true;
            frenzyCenter.x = position.x;
            frenzyCenter.y = position.y - frenzyRabius;
        }
        
        if (IsKeyPressed(KEY_U) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            Game::addPlayerBullet(Bullets(position, 5, Vector2Scale(normalizedMouseDir, 12)));
        }

        if (IsKeyPressed(KEY_I) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Game::addPlayerBullet(Bullets(position, 4, Vector2Scale(normalizedMouseDir, 8)));
        }
    }

    if (IsKeyDown(KEY_W)) {
        frameTimer += GetFrameTime();
        if (frameTimer >= frameTime) {
            frameTimer = 0.0f;
            currentFrame = (currentFrame + 1) % frameCount;
        }
    } else {
        currentFrame = 0;
    }

    if (thrust) {
        Vector2 thrustVelocity = Vector2Scale(velocity, thrustSpeed);
        position = Vector2Add(thrustVelocity, position);
        thrustSpeed /= thrustSpeedRetardation;
        if (thrustSpeed < 1) {
            thrust = false;
            thrustSpeed = 12.0f;
            specialMoveOn = false;  
            velocity = Vector2Scale(normalizedMouseDir, speed);
        }
    }
}

void sentinal::orientToMouse(){
    
    orientation = atan2f(normalizedMouseDir.y, normalizedMouseDir.x) * (180/PI);
}


void sentinal::draw() {
    // DrawRectanglePro(hitbox, {0, 0}, 0.0f, GREEN);
    update();
    for (int i = 0; i < bullets.size(); i++) {
        DrawEllipse(bullets[i].x, bullets[i].y, 15, 15, YELLOW);
        bullets[i].x -= 20;
    }
    if (IsKeyDown(KEY_W)) {
        Rectangle sourceRec = {frameWidth * currentFrame, 0, frameWidth, frameHeight};
        Rectangle destRec = {position.x, position.y, frameWidth, frameHeight};
        DrawTexturePro(sentinalSprite, sourceRec, destRec, {frameWidth/ 2, frameHeight/ 2}, orientation + 90, WHITE);
    } else if (IsKeyDown(KEY_A)) {
        Rectangle sourceRec = {2 * (sentinalIdleSprite.width / 3), 0, sentinalIdleSprite.width / 3, sentinalIdleSprite.height};
        Rectangle destRec = {position.x, position.y, (sentinalIdleSprite.width / 3), sentinalIdleSprite.height};
        DrawTexturePro(sentinalIdleSprite, sourceRec, destRec, {sentinalIdleSprite.width / 6, sentinalIdleSprite.height / 2}, orientation + 90, WHITE);
    } else if (IsKeyDown(KEY_F)) {
        Rectangle sourceRec = {1 * (sentinalIdleSprite.width / 3), 0, sentinalIdleSprite.width / 3, sentinalIdleSprite.height};
        Rectangle destRec = {position.x, position.y, (sentinalIdleSprite.width / 3), sentinalIdleSprite.height};
        DrawTexturePro(sentinalIdleSprite, sourceRec, destRec, {sentinalIdleSprite.width / 6, sentinalIdleSprite.height / 2}, orientation + 90, WHITE);
    } else {
        Rectangle sourceRec = {0 * (sentinalIdleSprite.width / 3), 0, sentinalIdleSprite.width / 3, sentinalIdleSprite.height};
        Rectangle destRec = {position.x, position.y, (sentinalIdleSprite.width / 3), sentinalIdleSprite.height};
        DrawTexturePro(sentinalIdleSprite, sourceRec, destRec, {sentinalIdleSprite.width / 6, sentinalIdleSprite.height / 2}, orientation + 90, WHITE);
    }

    if (IsKeyPressed(KEY_J)) {
        Rectangle sourceRec = {1 * (sentinalThrustSprites.width / 2), 0, sentinalThrustSprites.width / 2, sentinalThrustSprites.height};
        Rectangle destRec = {position.x, position.y, (sentinalThrustSprites.width / 2), sentinalThrustSprites.height};
        DrawTexturePro(sentinalThrustSprites, sourceRec, destRec, {sentinalIdleSprite.width / 4, sentinalIdleSprite.height / 2}, orientation + 90, WHITE);
    }

    if (IsKeyPressed(KEY_K)) {
        Rectangle sourceRec = {0 * (sentinalThrustSprites.width / 2), 0, sentinalThrustSprites.width / 2, sentinalThrustSprites.height};
        Rectangle destRec = {position.x, position.y, (sentinalThrustSprites.width / 2), sentinalThrustSprites.height};
        DrawTexturePro(sentinalThrustSprites, sourceRec, destRec, {sentinalIdleSprite.width / 4, sentinalIdleSprite.height / 2}, orientation + 90, WHITE);
    }
}
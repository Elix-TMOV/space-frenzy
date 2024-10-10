#pragma once
#include <raylib.h>
#include <raymath.h>


class blades
{
private:
    static Texture2D sprite;
    int wanderTime;
public:
    float rotationAngle;
    float rta;
    Vector2 GeneralPos;
    Vector2 position;
    blades(Vector2 position, float rotationAngle, Vector2 generalPos);
    ~blades();
    void slash();
    void wander();
    void draw();
    void rotateWithGeneral(Vector2 generlPos);
    void deattach();
    void setPosRelGeneral(Vector2 pos, Vector2 generalPos, float rotationAngle);
};






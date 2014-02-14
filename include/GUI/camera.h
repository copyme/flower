#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/core/type_vec3.hpp>

class Camera
{
private:
static const float MOUSE_PAN_SPEED;
static const float MOUSE_ZOOM_SPEED;
static const float MOUSE_TURN_SPEED;
    float radius;
    float theta;
    float phi;
    void compute();
public:
    Camera();
    glm::vec3 o;
    glm::vec3 eye;
    glm::vec3 up;
    void zoom ( float factor );
    void turn(float phi, float theta);
    void pan(float x, float y);

};

#endif // CAMERA_H

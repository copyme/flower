#include <cmath>
#include "camera.h"

const float Camera::MOUSE_PAN_SPEED = 0.001f;
const float Camera::MOUSE_ZOOM_SPEED = 0.05f;
const float Camera::MOUSE_TURN_SPEED = 0.005f;

Camera::Camera()
{
    phi = M_PI_2;
    theta = M_PI_2;
    radius = 10.f;
    compute();
}

void Camera::zoom ( float factor )
{
    factor *= MOUSE_ZOOM_SPEED;
    radius += factor * radius ;
    if ( radius < 0.1 )
    {
        radius = 10.f;
        o = eye + glm::normalize(o - eye) * radius;
    }
    compute();
}

void Camera::turn(float phi, float theta)
{
    phi *= MOUSE_TURN_SPEED;
    theta *= MOUSE_TURN_SPEED;
    this->theta += 1.f * theta;
    this->phi   -= 1.f * phi;
    if ( this->phi >= ( 2. * M_PI ) - 0.1 )
        phi = 0.00001;
    else if ( this->phi <= 0 )
        this->phi = 2. * M_PI - 0.1;
    compute();
}

void Camera::pan(float x, float y)
{
    x *= MOUSE_PAN_SPEED;
    y *= MOUSE_PAN_SPEED;
    glm::vec3 up ( 0.f, phi < M_PI ? 1.f : -1.f, 0.f );
    glm::vec3 fwd = glm::normalize ( o - eye );
    glm::vec3 side = glm::normalize ( glm::cross ( fwd, up ) );
    up = glm::normalize ( glm::cross ( side, fwd ) );
    o[0] += up[0] * y * radius * 2.;
    o[1] += up[1] * y * radius * 2.;
    o[2] += up[2] * y * radius * 2.;
    o[0] -= side[0] * x * radius * 2.;
    o[1] -= side[1] * x * radius * 2.;
    o[2] -= side[2] * x * radius * 2.;
    compute();
}

void Camera::compute()
{
    eye.x = cos ( theta ) * sin ( phi ) * radius + o.x;
    eye.y = cos ( phi ) * radius + o.y ;
    eye.z = sin ( theta ) * sin ( phi ) * radius + o.z;
    up = glm::vec3 ( 0.f, phi < M_PI ? 1.f: -1.f, 0.f );
}

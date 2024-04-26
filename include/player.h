#pragma once

#include <glm/glm.hpp>
#include <sphere.h>

class Player {
public:
    glm::vec3 Position;
    glm::vec3 Direction;
    glm::vec3 Velocity;
    
    float radius;
    float Rotation;
    float Speed;
    float MaxSpeed;
    float Acceleration;
    float Friction;
    float JumpStrength;

    bool IsGrounded;


    Player(glm::vec3 position, Shader sphereShader);

    float GetSpeed();

    void MoveForward();
    void MoveBackward();
    void StrafeLeft();
    void StrafeRight();

    void Jump();

    void Update(float deltaTime);

    void Draw();

private:
    int RotationDirection = 1;
    Shader sphereShader;
    Sphere* sphere;
};

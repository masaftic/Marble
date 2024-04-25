#pragma once

#include <glm/glm.hpp>

class Player {
public:
    glm::vec3 Position;
    glm::vec3 Direction;
    glm::vec3 Velocity;
    
    float Rotation;
    float Speed;
    float MaxSpeed;
    float Acceleration;
    float Friction;
    float JumpStrength;

    bool IsGrounded;


    Player(glm::vec3 position);

    float GetSpeed();

    void MoveForward();
    void MoveBackward();
    void StrafeLeft();
    void StrafeRight();

    void Jump();

    void Update(float deltaTime);

private:
    int RotationDirection = 1;

};

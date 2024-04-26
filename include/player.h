#pragma once

#include <glm/glm.hpp>
#include <sphere.h>
#include <texture.h>

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


    Player(glm::vec3 position, Shader sphereShader);

    float GetSpeed();

    void MoveForward();
    void MoveBackward();
    void StrafeLeft();
    void StrafeRight();

    void Jump();

    void Update(float deltaTime);

    void Draw(Texture& texture);

private:
    Shader sphereShader;
    Sphere* sphere;
};

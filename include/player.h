#pragma once

#include <glm/glm.hpp>
#include <sphere.h>
#include <texture.h>

class Player {
public:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 velocity;
    
    float rotation;
    float speed;
    float maxSpeed;
    float acceleration;
    float friction;
    float jumpStrength;

    bool isGrounded;


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

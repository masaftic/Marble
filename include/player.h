#pragma once

#include <glm/glm.hpp>
#include <sphere.h>
#include <texture.h>
#include <cube.h>

class Player {
public:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 velocity;
    glm::vec3 rotationVec;
    
    float radius;
    float rotation;
    float speed;
    float maxSpeed;
    float acceleration;
    float friction;
    float jumpStrength;

    bool isGrounded;


    Player(glm::vec3 position);

    float GetSpeed();

    void MoveForward(float dt);
    void MoveBackward(float dt);
    void StrafeLeft(float dt);
    void StrafeRight(float dt);

    void Jump();

    void Update(float deltaTime, std::vector<Cube>& cubes);




    void Draw(Shader& shader, Texture& texture);

    std::pair<bool, glm::vec3> CheckCollision(Cube& cube);

    void ResolveCollision(glm::vec3 closestPoint);

    Sphere* sphere;
};

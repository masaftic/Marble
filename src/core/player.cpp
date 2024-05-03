#include "player.h"
#include <glm/glm.hpp>


Player::Player(glm::vec3 position) : speed(0.0f), maxSpeed(10.0f), acceleration(0.015f), friction(0.999f), jumpStrength(10.0f), isGrounded(false), rotation(0.0f)
{
    this->position = position;
    this->direction = glm::vec3(1.0f, 0, 1.0f);
    this->velocity = glm::vec3(1.0f, 0.0f, 1.0f);
    sphere = new Sphere();
}

float Player::GetSpeed()
{
    return glm::length(this->velocity);
}

void Player::MoveForward() 
{
    velocity += direction * acceleration;
}

void Player::MoveBackward() 
{
    velocity -= direction * acceleration;
}

void Player::StrafeLeft() 
{
    glm::vec3 right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));
    velocity -= glm::normalize(right) * acceleration;
}

void Player::StrafeRight() 
{
    glm::vec3 right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));
    velocity += glm::normalize(right) * acceleration;
}

void Player::Jump() 
{
    if (isGrounded) {
        velocity.y += jumpStrength;
        isGrounded = false;
    }
}

void Player::Update(float deltaTime) 
{
    // Apply friction
    velocity *= friction;

    // Clamp velocity to max speed
    if (glm::length(velocity) > maxSpeed) {
        velocity = glm::normalize(velocity) * maxSpeed;
    }

    // Update position based on velocity
    position += velocity * deltaTime;

    rotation -= this->GetSpeed() * deltaTime;

    // making sure rotation doesn't get too big to overflow
    rotation = fmod(rotation, 2 * 3.14159f);
    if (rotation < -3.14159f) rotation += 2 * 3.14159f;

    // Simulate gravity (optional)
    //if (!IsGrounded) {
    //    Velocity.y -= 9.81f * deltaTime; // Apply gravity
    //}
}

void Player::Draw(Shader& shader, Texture& texture)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, this->position);
    model = glm::rotate(model, this->rotation, glm::cross(glm::normalize(this->velocity), glm::vec3(0.0f, 1.0f, 0.0f)));

    shader.Use();
    shader.setMat4("model", model);
    shader.setVec3("color", glm::vec3(1.0f));


    sphere->Draw(shader, texture);
}

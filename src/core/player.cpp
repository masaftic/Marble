#include "player.h"
//#include "player.h"
//
//Player::Player(glm::vec3 pos) : Position(pos)
//{
//}

Player::Player(glm::vec3 position) : Speed(0.0f), MaxSpeed(20.0f), Acceleration(10.0f), Friction(0.8f), JumpStrength(10.0f), IsGrounded(false)
{
    this->Position = position;
    this->Direction = glm::vec3(1.0f, 0, 1.0f);
    this->Velocity = glm::vec3(1.0f, 0.0f, 1.0f);
}

void Player::MoveForward() {
    Velocity += Direction * Acceleration;
}

void Player::MoveBackward() {
    Velocity -= Direction * Acceleration;
}

void Player::StrafeLeft() {
    glm::vec3 right = glm::cross(Direction, glm::vec3(0.0f, 1.0f, 0.0f));
    Velocity -= glm::normalize(right) * Acceleration;
}

void Player::StrafeRight() {
    glm::vec3 right = glm::cross(Direction, glm::vec3(0.0f, 1.0f, 0.0f));
    Velocity += glm::normalize(right) * Acceleration;
}

void Player::Jump() {
    if (IsGrounded) {
        Velocity.y += JumpStrength;
        IsGrounded = false;
    }
}

void Player::Update(float deltaTime) {
    // Apply friction
    Velocity *= Friction;

    // Clamp velocity to max speed
    if (glm::length(Velocity) > MaxSpeed) {
        Velocity = glm::normalize(Velocity) * MaxSpeed;
    }

    // Update position based on velocity
    Position += Velocity * deltaTime;

    // Simulate gravity (optional)
    //if (!IsGrounded) {
    //    Velocity.y -= 9.81f * deltaTime; // Apply gravity
    //}
}

#include "player.h"
#include <glm/glm.hpp>


Player::Player(glm::vec3 position) : Speed(0.0f), MaxSpeed(20.0f), Acceleration(0.06f), Friction(0.999f), JumpStrength(10.0f), IsGrounded(false), Rotation(0.0f)
{
    this->Position = position;
    this->Direction = glm::vec3(1.0f, 0, 1.0f);
    this->Velocity = glm::vec3(1.0f, 0.0f, 1.0f);
}

float Player::GetSpeed()
{
    return glm::length(this->Velocity);
}

void Player::MoveForward() 
{
    RotationDirection = 1;

    Velocity += Direction * Acceleration;
}

void Player::MoveBackward() 
{
    RotationDirection = -1;
    Velocity -= Direction * Acceleration;
}

void Player::StrafeLeft() 
{
    RotationDirection = 1;
    glm::vec3 right = glm::cross(Direction, glm::vec3(0.0f, 1.0f, 0.0f));
    Velocity -= glm::normalize(right) * Acceleration;
    this->Direction = -right;
}

void Player::StrafeRight() 
{
    RotationDirection = 1;

    glm::vec3 right = glm::cross(Direction, glm::vec3(0.0f, 1.0f, 0.0f));
    Velocity += glm::normalize(right) * Acceleration;
    this->Direction = right;

}

void Player::Jump() 
{
    if (IsGrounded) {
        Velocity.y += JumpStrength;
        IsGrounded = false;
    }
}

void Player::Update(float deltaTime) 
{
    // Apply friction
    Velocity *= Friction;

    // Clamp velocity to max speed
    if (glm::length(Velocity) > MaxSpeed) {
        Velocity = glm::normalize(Velocity) * MaxSpeed;
    }

    // Update position based on velocity
    Position += Velocity * deltaTime;

    if (this->GetSpeed() > 0) Rotation -= RotationDirection * this->GetSpeed() * deltaTime;
    
    // Rotation *= Friction;

    // Simulate gravity (optional)
    //if (!IsGrounded) {
    //    Velocity.y -= 9.81f * deltaTime; // Apply gravity
    //}
}

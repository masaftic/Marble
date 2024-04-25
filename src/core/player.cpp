#include "player.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
//#include "player.h"
//
//Player::Player(glm::vec3 pos) : Position(pos)
//{
//}

int dir = 1;

Player::Player(glm::vec3 position) : Speed(0.0f), MaxSpeed(20.0f), Acceleration(10.0f), Friction(0.8f), JumpStrength(10.0f), IsGrounded(false), Rotation(0.0f)
{
    this->Position = position;
    this->Direction = glm::vec3(1.0f, 0, 1.0f);
    this->Velocity = glm::vec3(1.0f, 0.0f, 1.0f);
}

float Player::GetSpeed()
{
    return glm::length(this->Velocity);
}

void Player::MoveForward() {
    dir = 1;

    Velocity += Direction * Acceleration;
}

void Player::MoveBackward() {
    dir = -1;
    Velocity -= Direction * Acceleration;
}

void Player::StrafeLeft() {
    dir = 1;
    glm::vec3 right = glm::cross(Direction, glm::vec3(0.0f, 1.0f, 0.0f));
    Velocity -= glm::normalize(right) * Acceleration;
    this->Direction = -right;
}

void Player::StrafeRight() {
    dir = 1;

    glm::vec3 right = glm::cross(Direction, glm::vec3(0.0f, 1.0f, 0.0f));
    Velocity += glm::normalize(right) * Acceleration;
    this->Direction = right;

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

    if (this->GetSpeed() > 0) Rotation -= dir * this->GetSpeed() * deltaTime;
    
    // Rotation *= Friction;

    // Simulate gravity (optional)
    //if (!IsGrounded) {
    //    Velocity.y -= 9.81f * deltaTime; // Apply gravity
    //}
}

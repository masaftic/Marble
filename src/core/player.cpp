#include "player.h"
#include <glm/glm.hpp>


Player::Player(glm::vec3 position, Shader sphereShader) : Speed(0.0f), MaxSpeed(10.0f), Acceleration(0.02f), Friction(0.999f), JumpStrength(10.0f), IsGrounded(false), Rotation(0.0f)
{
    this->Position = position;
    this->Direction = glm::vec3(1.0f, 0, 1.0f);
    this->Velocity = glm::vec3(1.0f, 0.0f, 1.0f);
    this->sphereShader = sphereShader;
    sphere = new Sphere(sphereShader);
}

float Player::GetSpeed()
{
    return glm::length(this->Velocity);
}

void Player::MoveForward() 
{
    Velocity += Direction * Acceleration;
}

void Player::MoveBackward() 
{
    Velocity -= Direction * Acceleration;
}

void Player::StrafeLeft() 
{
    glm::vec3 right = glm::cross(Direction, glm::vec3(0.0f, 1.0f, 0.0f));
    Velocity -= glm::normalize(right) * Acceleration;
}

void Player::StrafeRight() 
{
    glm::vec3 right = glm::cross(Direction, glm::vec3(0.0f, 1.0f, 0.0f));
    Velocity += glm::normalize(right) * Acceleration;
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

    if (this->GetSpeed() > 0) Rotation -= this->GetSpeed() * deltaTime;

    // making sure rotation doesn't get too big to overflow
    Rotation = fmod(Rotation, 2 * 3.14159f);
    if (Rotation < -3.14159f) Rotation += 2 * 3.14159f;

    // Simulate gravity (optional)
    //if (!IsGrounded) {
    //    Velocity.y -= 9.81f * deltaTime; // Apply gravity
    //}
}

void Player::Draw(Texture& texture)
{
    this->sphereShader.Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, this->Position);
    model = glm::rotate(model, this->Rotation, glm::cross(glm::normalize(this->Velocity), glm::vec3(0.0f, 1.0f, 0.0f)));
    // model = glm::scale(model, this->sphere->radius);

    this->sphereShader.setMat4("model", model);
    this->sphereShader.setVec3("color", glm::vec3(0.8f, 0.2f, 0.4f));


    glActiveTexture(GL_TEXTURE0);
    // texture.Bind();


    sphere->Draw();
}

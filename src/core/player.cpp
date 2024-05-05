#include "player.h"
#include <glm/glm.hpp>


Player::Player(glm::vec3 position) : speed(0.0f), maxSpeed(10.0f), acceleration(15.015f), friction(0.01f), jumpStrength(7.0f), isGrounded(false), rotation(0.0f)
{
    this->position = position;
    this->lastPosition = this->position;
    this->direction = glm::vec3(1.0f, 0, 1.0f);
    this->velocity = glm::vec3(1.0f, 0.0f, 1.0f);
    sphere = new Sphere();
    this->radius = sphere->radius;
}

float Player::GetSpeed()
{
    return glm::length(glm::vec3(this->velocity.x, 0, this->velocity.z));
}

void Player::MoveForward(float dt) 
{
    velocity += direction * acceleration * dt;
}

void Player::MoveBackward(float dt) 
{
    velocity -= direction * acceleration * dt;
}

void Player::StrafeLeft(float dt) 
{
    glm::vec3 right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));
    velocity -= glm::normalize(right) * acceleration * dt;
}

void Player::StrafeRight(float dt) 
{
    glm::vec3 right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));
    velocity += glm::normalize(right) * acceleration * dt;
}

void Player::Jump() 
{
    if (isGrounded) {
        velocity.y += jumpStrength;
        isGrounded = false;
    }
}

void Player::Update(float deltaTime, std::vector<Cube>& cubes)
{
    // Apply friction
    velocity.x *= (1 - friction);
    velocity.z *= (1 - friction);

    // Clamp velocity to max speed
    float currentSpeed = GetSpeed();
    if (currentSpeed > maxSpeed) {
        velocity.x = (velocity.x / currentSpeed) * maxSpeed;
        velocity.z = (velocity.z / currentSpeed) * maxSpeed;
    }

    // Reset isGrounded to false at the start of each update
    isGrounded = false;

    for (int i = 0; i < cubes.size(); i++) {
        auto collision = CheckCollision(cubes[i]);
        if (collision.first) {
            // Check if the player is on top of the cube
            float cubeTop = cubes[i].position.y + cubes[i].size.y / 2;
            float cubeLeft = cubes[i].position.x - cubes[i].size.x / 2;
            float cubeRight = cubes[i].position.x + cubes[i].size.x / 2;
            float cubeFront = cubes[i].position.z - cubes[i].size.z / 2;
            float cubeBack = cubes[i].position.z + cubes[i].size.z / 2;

            bool isCenterInsideCube = this->position.x > cubeLeft && this->position.x < cubeRight &&
                this->position.z > cubeFront && this->position.z < cubeBack;


            if (this->position.y >= cubeTop && velocity.y <= 0 && isCenterInsideCube) {
                this->position.y = cubeTop + this->radius; // Adjust position to be on top of the cube
                this->velocity.y = 0; // Player is grounded
                isGrounded = true;
            }
            ResolveCollision(collision.second);
        }
    }

    // Apply gravity if not grounded
    if (!isGrounded) {
        velocity.y -= 9.81f * deltaTime; // Apply gravity
    }

    // Update position based on velocity
    position += velocity * deltaTime;

    // Update rotation
    rotation -= currentSpeed * deltaTime;

    // making sure rotation doesn't get too big to overflow
    rotation = fmod(rotation, 2 * glm::pi<float>());
    if (rotation < -glm::pi<float>()) rotation += 2 * glm::pi<float>();
}



void Player::Draw(Shader& shader, Texture& texture)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, this->position);

    glm::vec3 directionRotation = this->velocity;
    directionRotation.y = 0;
    directionRotation = glm::normalize(directionRotation);

    model = glm::rotate(model, this->rotation, glm::cross(directionRotation, glm::vec3(0.0f, 1.0f, 0.0f)));

    shader.Use();
    shader.setMat4("model", model);
    shader.setVec3("color", glm::vec3(1.0f));


    sphere->Draw(shader, texture);
}


std::pair<bool, glm::vec3> Player::CheckCollision(Cube cube)
{
    glm::vec3 closestPoint;
    glm::vec3 halfSize = cube.size * 0.5f;

    for (int i = 0; i < 3; ++i) {  // For each x, y, z coordinate
        float v = this->position[i];
        v = std::max(cube.position[i] - halfSize[i], v);
        v = std::min(cube.position[i] + halfSize[i], v);
        closestPoint[i] = v;
    }

    float distance = glm::distance(this->position, closestPoint);
    return { distance < this->radius, closestPoint };
}


void Player::ResolveCollision(glm::vec3 closestPoint) {
    glm::vec3 collisionNormal = this->position - closestPoint;
    float distance = glm::length(collisionNormal);
    float collisionDepth = this->radius - distance + 0.01f;

    if (collisionDepth > 0) {
        // Normalize the collision normal
        if (glm::length(collisionNormal) == 0.0f) {
            collisionNormal = glm::vec3(0, 1, 0);
        }
        else collisionNormal = glm::normalize(collisionNormal);

        // Move the sphere out of the cube along the collision normal
        this->position += collisionDepth * collisionNormal;
    }
}


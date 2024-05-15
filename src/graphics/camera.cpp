#include "camera.h"

Camera::Camera(int width, int height, Player* player)
{
	this->width    = width;
	this->height   = height;
	this->player   = player;
}

void Camera::SetMatrix(Shader& shader, const char* uniform)
{
	shader.setMat4(uniform, camMatrix);
}


void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	view = glm::lookAt(position, player->position, up);

	proj = glm::perspective(glm::radians(FOVdeg), ((float)width / height), nearPlane, farPlane);

	camMatrix = proj * view;
}

void Camera::Inputs(GLFWwindow* window, float dt)
{	
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		if (this->distanceFromPlayer < 17)
			this->distanceFromPlayer += this->speed;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		if (this->distanceFromPlayer > 3)
			this->distanceFromPlayer -= this->speed;
	}
	
	// Handles mouse inputs
	// Stores the coordinates of the cursor
	double mouseX;
	double mouseY;
	// Fetches the coordinates of the cursor
	glfwGetCursorPos(window, &mouseX, &mouseY);

	float rotY = sensitivity * (float)(mouseY - (height / 2)) / height;
	float rotX = sensitivity * (float)(mouseX - (width / 2)) / width;

	if (abs(this->pitch + rotY) <= 85) {
		this->pitch += rotY;
	}
	this->angleAroundPlayer += -rotX * speed * 0.7f;

	// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
	glfwSetCursorPos(window, (width / 2), (height / 2));
	
	float horizontalDistance = CalculateHorizontalDistance();
	float verticalDistance = CalculateVerticalDistance();
	CalculateCameraPos(horizontalDistance, verticalDistance);
}

float Camera::CalculateHorizontalDistance()
{
	return this->distanceFromPlayer * glm::cos(glm::radians(pitch));
}

float Camera::CalculateVerticalDistance()
{
	return this->distanceFromPlayer * glm::sin(glm::radians(pitch));
}



void Camera::CalculateCameraPos(float horizontalDistance, float verticalDistance)
{
	float theta = this->angleAroundPlayer;

	float offsetX = horizontalDistance * glm::sin(theta);
	float offsetZ = horizontalDistance * glm::cos(theta);

	glm::vec3 targetPosition = player->position + glm::vec3(-offsetX, verticalDistance, -offsetZ);
	position = targetPosition;
}


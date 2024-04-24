#include "camera.h"

Camera::Camera(int width, int height, glm::vec3 position, Player* player)
{
	this->width    = width;
	this->height   = height;
	this->Position = position;
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

	view = glm::lookAt(Position, player->Position, Up);

	proj = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	camMatrix = proj * view;
}

void Camera::Inputs(GLFWwindow* window, float dt)
{	
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		this->distanceFromPlayer += this->speed;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		this->distanceFromPlayer -= this->speed;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.04f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.01f;
	}
	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotY = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotX = sensitivity * (float)(mouseX - (width / 2)) / width;

		if (abs(this->pitch + rotY) <= 85) {
			this->pitch += rotY;
		}
		this->angleAroundPlayer += -rotX * speed * 0.7f;

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
	
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
	Position.x = player->Position.x - offsetX;
	Position.z = player->Position.z - offsetZ;
	Position.y = player->Position.y + verticalDistance;
}


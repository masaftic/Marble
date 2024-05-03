#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shader.h"
#include <player.h>

class Camera
{
public:
	Player* player;
	glm::vec3 position;
	float pitch = 20;
	float yaw = -90;
	float distanceFromPlayer = 10;
	float angleAroundPlayer = 0;

	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 camMatrix = glm::mat4(1.0f);

	bool firstClick = true;

	int width;
	int height;

	float speed = 0.01f;
	float sensitivity = 100.0f;


	Camera(int width, int height, Player* player);

	void SetMatrix(Shader& shader, const char* uniform);
	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Inputs(GLFWwindow* window, float dt);

	float CalculateHorizontalDistance();
	float CalculateVerticalDistance();
	void CalculateCameraPos(float horizontalDistance, float verticalDistance);
};

#pragma once

class Game;
class GameObject;

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>



#include<cmath>
#include"ROML.h"
#include"shaderclass.h"

class Camera : public GameObject {
	public:	
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f); //Orientation == Direction
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 cameraMatrix = glm::mat4(1.0f);
		int width;
		int height;

		//Prevents camera from jumping when clicking
		bool firstClick = true;

		float speed = 0.1f;
		float sensitivity = 100.0f;

		Camera(int width, int height, glm::vec3 position);
		void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void Matrix(Shader& shader, const char* uniform);
		//Handles camera inputs
		void Inputs(GLFWwindow* window);
};


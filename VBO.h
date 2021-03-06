#pragma once

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>


struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};
class VBO {
	public:
		//ID reference for VBO
		GLuint ID;
		//makes the VBO
		VBO(std::vector<Vertex>& vertices);
		VBO();

		void Bind();
		void Unbind();
		void Delete();
};

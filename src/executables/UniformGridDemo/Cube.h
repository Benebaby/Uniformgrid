#pragma once
#include <Tools/Defs.h>

class Cube
{
public:
	Cube();
	Cube(glm::vec3 center, float sideLength, glm::vec3 color);
	~Cube();
	void render();
	glm::vec3 m_center;
private:
	GLuint VertexArray;
	GLuint VertexBuffer[3];
	GLuint IndexBuffer;

	int  _points = 24;
	int _indices = 36;
	float m_halfSide;
	glm::vec3 m_color;

	void fillBuffers();

	GLfloat _v[72];

	GLfloat _n[72];

	GLfloat _c[72];

	GLuint _index[36];
};

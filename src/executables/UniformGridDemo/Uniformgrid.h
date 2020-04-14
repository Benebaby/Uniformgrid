#pragma once
#include <Tools/Defs.h>
#include <vector>
#include "Cube.h"

class Uniformgrid
{
public:
	Uniformgrid(glm::vec3 center, glm::vec3 extents, float voxelSize);
	void render();
	glm::ivec2 setCandidate(int i, int x);
	void removeCandidate(int i, int pos);
	void createCandidates();
	void renderCandidates();
    glm::vec3 m_center;
	glm::vec3 m_extents;
	float m_voxelSize;
	glm::vec3 m_min;
	glm::vec3 m_max;
	std::vector<std::vector<int>> objects;
private:
	void createBuffersVector();
	GLuint VertexArray;
	GLuint VertexBuffer[1];
    std::vector<GLfloat> points;
	std::vector<Cube> candidates;
};
#pragma once
#include <Tools/Defs.h>
#include <vector>
#include "Uniformgrid.h"

class Sphere
{
    
public:
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec3> m_colors;
    std::vector<GLuint> m_index;

    GLuint m_VertexArray;
    GLuint m_VertexBuffer[3];
    GLuint m_IndexBuffer;

    int m_indices, m_points;
    float m_radius = 0;
    int m_resolution = 0;
    glm::vec3 m_center;

    Sphere( glm::vec3 center, float radius, int resolution);
    void create(  glm::vec3 center, float radius, int resolution);
    void intersectVoxel(Uniformgrid* grid);
    bool sphereBoxOverlap(glm::vec3 C1, glm::vec3 C2, glm::vec3 S, float R);
    void render();
};

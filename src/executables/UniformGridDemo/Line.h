#include <Tools/Defs.h>
#include <vector>
#include "Uniformgrid.h"

class Line
{
public:
	Line(glm::vec3 pos, glm::vec3 dir, float length);
    void render();
    void intersectVoxel(Uniformgrid* grid);
private:
    GLuint VertexArray;
    GLuint VertexBuffer[1];
    std::vector<glm::vec3> points;
    glm::vec3 m_ray_pos;
    glm::vec3 m_ray_dir;
    float m_ray_length;
};
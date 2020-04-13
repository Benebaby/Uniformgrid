#include <Tools/Defs.h>
#include <vector>
#include <math.h>
#include "Cube.h"
#include "Uniformgrid.h"

class Triangle
{
public:
	Triangle(glm::vec3 A, glm::vec3 B, glm::vec3 C);
    void intersectVoxel(Uniformgrid* grid);
    void render();
private:
    GLuint VertexArray;
    GLuint VertexBuffer[1];
	glm::vec3 m_A,m_B,m_C;
    std::vector<glm::vec3> points;
    void findMinMax(float x0, float x1, float x2, float &min,float &max);
    int planeBoxOverlap(glm::vec3 normal, glm::vec3 vert, glm::vec3 maxbox);
    int triBoxOverlap(glm::vec3 boxcenter,glm::vec3 boxhalfsize,glm::mat3 triverts);
};
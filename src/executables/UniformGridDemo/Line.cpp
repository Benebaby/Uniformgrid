#include "Line.h"

Line::Line(glm::vec3 pos, glm::vec3 dir, float length){
    m_ray_length = length;
    m_ray_dir = glm::normalize(dir);
    m_ray_pos = pos;
    points.push_back(m_ray_pos);
    points.push_back(m_ray_pos + m_ray_length * m_ray_dir);
    intersectedVoxel.resize(0);

    glGenVertexArrays(1, &VertexArray);
    glBindVertexArray(VertexArray);

    glGenBuffers(1, VertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), &points[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Line::render(){
    glBindVertexArray(VertexArray);
    glDrawArrays(GL_LINES, 0, (GLint) points.size() * 3);
}
void Line::intersectVoxel(Uniformgrid* grid){

    for(int i = 0; i < intersectedVoxel.size(); i++){
		grid->removeCandidate(intersectedVoxel[i].x, intersectedVoxel[i].y); 
	}

    double m_InvVoxelSize = 1.0f / grid->m_voxelSize;
    glm::vec3 direction = m_ray_dir;
    glm::vec3 origin = m_ray_pos;
    glm::ivec3 step( (direction.x<0) ? -1 : 1, (direction.y<0) ? -1 : 1, (direction.z<0) ? -1 : 1);
    glm::vec3 delta = glm::vec3(step) / direction * grid->m_voxelSize;
    glm::vec3 posVec = (origin - grid->m_min) * m_InvVoxelSize;
    glm::ivec3 index;
    glm::ivec3 m_maxIndex = grid->m_extents * m_InvVoxelSize - 1.0f;
    index.x = glm::min((unsigned int)(glm::max(posVec.x, 0.0f)), (unsigned int) (m_maxIndex.x));
    index.y = glm::min((unsigned int)(glm::max(posVec.y, 0.0f)), (unsigned int) (m_maxIndex.y));
    index.z = glm::min((unsigned int)(glm::max(posVec.z, 0.0f)), (unsigned int) (m_maxIndex.z));
    
    glm::ivec3 indexExtent = grid->m_extents / grid->m_voxelSize;

    glm::vec3 tnext;
    if (step.x < 0)
        tnext.x = (posVec.x - index.x) * delta.x;
    else
        tnext.x = (1 - posVec.x + index.x) * delta.x;
    if (step.y < 0)
        tnext.y = (posVec.y - index.y) * delta.y;
    else
        tnext.y = (1 - posVec.y + index.y) * delta.y;
    if (step.z < 0)
        tnext.z = (posVec.z - index.z) * delta.z;
    else
        tnext.z = (1 - posVec.z + index.z) * delta.z;
    if (step.z < 0)
        tnext.z = (posVec.z - index.z) * delta.z;
    else
        tnext.z = (1 - posVec.z + index.z) * delta.z;

    unsigned int OneDIndex = static_cast<unsigned int>(index.z*indexExtent.x*indexExtent.y + index.y * indexExtent.x + index.x);
    intersectedVoxel.push_back(grid->setCandidate(OneDIndex, 2));
   

    for(;;){
        if (tnext.x < tnext.y){
            if (tnext.x < tnext.z) {
                index.x += step.x;
                if ((index.x < 0) || (index.x > m_maxIndex.x)) break;
                tnext.x += delta.x;
            }
            else {
                index.z += step.z;
                if ((index.z < 0) || (index.z > m_maxIndex.z)) break;
                tnext.z += delta.z;
            }
        }else{
            if (tnext.y < tnext.z) {
                index.y += step.y;
                if ((index.y < 0) || (index.y > m_maxIndex.y)) break;
                tnext.y += delta.y;
            }
            else {
                index.z += step.z;
                if ((index.z < 0) || (index.z > m_maxIndex.z)) break;
                tnext.z += delta.z;
            }
        }
        OneDIndex = static_cast<unsigned int>(index.z*indexExtent.x*indexExtent.y + index.y * indexExtent.x + index.x);

        intersectedVoxel.push_back(grid->setCandidate(OneDIndex, 2));

        for(int i = 0; i < 100; i++){
            if(grid->objects[OneDIndex][i] != 0 && grid->objects[OneDIndex][i] != 2){
                intersectedVoxel.push_back(grid->setCandidate(OneDIndex, 4));
                break;
            }
        }
    }
}
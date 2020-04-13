#include "Uniformgrid.h"

Uniformgrid::Uniformgrid(glm::vec3 center, glm::vec3 extents, float voxelSize)
{
    m_center = center;
    m_extents = extents;
    m_min = center - m_extents / 2.0f;
    m_max = center + m_extents / 2.0f;
    m_voxelSize = voxelSize;
    objects.resize(static_cast<int> ((extents.x / m_voxelSize) * (extents.y / m_voxelSize) * (extents.z / m_voxelSize)));

    for (float x = 0; x <= extents.x; x += m_voxelSize)
    {
        for (float y = 0; y <= extents.y; y += m_voxelSize)
        {
            points.push_back(m_min.x + x);
            points.push_back(m_min.y + y);
            points.push_back(m_min.z);
            points.push_back(m_min.x + x);
            points.push_back(m_min.y + y);
            points.push_back(m_min.z + m_extents.z);
        }
    }
    for (float z = 0; z <= extents.z; z += m_voxelSize)
    {
        for (float x = 0; x <= extents.x; x += m_voxelSize)
        {
            points.push_back(m_min.x + x);
            points.push_back(m_min.y);
            points.push_back(m_min.z + z);
            points.push_back(m_min.x + x);
            points.push_back(m_min.y + m_extents.y);
            points.push_back(m_min.z + z);
        }
    }
    for (float y = 0; y <= extents.y; y += m_voxelSize)
    {
        for (float z = 0; z <= extents.z; z += m_voxelSize)
        {
            points.push_back(m_min.x);
            points.push_back(m_min.y + y);
            points.push_back(m_min.z + z);
            points.push_back(m_min.x + m_extents.x);
            points.push_back(m_min.y + y);
            points.push_back(m_min.z + z);
        }
    }

    glGenVertexArrays(1, &VertexArray);
    glBindVertexArray(VertexArray);

    glGenBuffers(1, VertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GL_FLOAT), &points[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Uniformgrid::render()
{
    glBindVertexArray(VertexArray);
    glDrawArrays(GL_LINES, 0, (GLint)points.size());
}

void Uniformgrid::createCandidates()
{
    
    glm::vec3 indexExtent = m_extents / m_voxelSize;
    for(int i = 0; i < objects.size(); i++){
        if(objects[i].size() > 0){
            glm::vec3 color = glm::vec3(0.0f);
            for(int j = 0; j < objects[i].size(); j++){
                if(objects[i][j] == 1)
                    color = glm::vec3(0.0f, 1.0f, 0.0f);
                if(objects[i][j] == 2)
                    color = glm::vec3(0.0f, 0.0f, 1.0f);
                if(objects[i][j] == 4)
                    color = glm::vec3(1.0f, 0.0f, 1.0f);
                if(objects[i][j] == 3)
                    color = glm::vec3(1.0f, 0.0f, 0.0f);
            }
            glm::vec3 tempIndex;
            tempIndex.z = (int) (i / (indexExtent.x * indexExtent.y));
            tempIndex.y = (int) ((i - (tempIndex.z * indexExtent.x * indexExtent.y)) / indexExtent.x);
            tempIndex.x = (int) (i - (tempIndex.z * indexExtent.x * indexExtent.y) - (tempIndex.y * indexExtent.x));
            candidates.push_back(Cube(m_min + glm::vec3(m_voxelSize / 2.0) + (tempIndex * m_voxelSize), m_voxelSize, color));
        }
    }
}

void Uniformgrid::renderCandidates()
{
    for(Cube c: candidates)
        c.render();
}

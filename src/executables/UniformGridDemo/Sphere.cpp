#include "Sphere.h"

Sphere::Sphere(glm::vec3 center, float radius, int resolution)
{
	m_radius = radius;
	m_resolution = resolution;
	m_center = center;
	intersectedVoxel.resize(0);
	Sphere::create( m_center,  m_radius, m_resolution);
}

void Sphere::create(glm::vec3 center, float radius, int resolution)
{
	// iniatialize the variable we are going to use
	float u, v;
	float phi, theta;
	float x, y, z;
	int offset = 0, i, j;

	// create points
	for ( j = 0; j <= resolution; j++)  //theta
		for ( i = 0; i <= resolution; i++) //phi
		{
			u = i /(float)resolution;		phi   = 2* glm::pi<float>() * u;
			v = j /(float)resolution;		theta =    glm::pi<float>() * v;

			x = m_center.x + radius * sin(theta) * sin(phi);
			y = m_center.y + radius * cos(theta);
			z = m_center.z + radius * sin(theta) * cos(phi);

			m_vertices.push_back(glm::vec3( x, y, z));
			m_normals.push_back((glm::vec3( x, y, z) - m_center) / radius);
			m_colors.push_back((glm::vec3( x, y, z) - m_center) / radius);
		}
        m_points = m_vertices.size();

	// create index list
	for ( j = 0; j < resolution; j++)
	{
		for ( i = 0; i < resolution; i++)
		{
			// 1. Triangle
			m_index.push_back( offset + i );
			m_index.push_back( offset + i + resolution+1);
			m_index.push_back( offset + i + resolution+1 + 1);

			// 2. Triangle
			m_index.push_back( offset + i + resolution+1 + 1);
			m_index.push_back( offset + i + 1);
			m_index.push_back( offset + i );
		}
		offset += resolution+1;
	}
    m_indices = m_index.size();

    glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);

	glGenBuffers(3, m_VertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, m_points * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, m_points * sizeof(glm::vec3), &m_normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer[2]);
	glBufferData(GL_ARRAY_BUFFER, m_points * sizeof(glm::vec3), &m_colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &m_IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices * sizeof(GL_UNSIGNED_INT), &m_index[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sphere::intersectVoxel(Uniformgrid* grid){
	//remove old intersects
	for(int i = 0; i < intersectedVoxel.size(); i++){
		grid->removeCandidate(intersectedVoxel[i].x, intersectedVoxel[i].y);
	}

	glm::vec3 max = m_center + glm::vec3(m_radius);
	glm::vec3 min = m_center - glm::vec3(m_radius);
	max = glm::ceil(max / grid->m_voxelSize) * grid->m_voxelSize;
    min = glm::floor(min / grid->m_voxelSize) * grid->m_voxelSize;

    glm::vec3 indexExtent = grid->m_extents / grid->m_voxelSize;

    for(float x = min.x; x <= max.x; x+= grid->m_voxelSize)
        for(float y = min.y; y <= max.y; y+= grid->m_voxelSize)
            for(float z = min.z; z <= max.z; z+= grid->m_voxelSize)
                {
                    glm::vec3 temp = glm::vec3(x,y,z) + glm::vec3(0.5f * grid->m_voxelSize);
                    glm::ivec3 index = glm::ivec3((temp - grid->m_min) / grid->m_voxelSize);
					glm::vec3 C1 = glm::vec3(x,y,z);
					glm::vec3 C2 = glm::vec3(x,y,z) + glm::vec3(grid->m_voxelSize);
                    if(Sphere::sphereBoxOverlap(C1, C2, m_center, m_radius)){
						int objectsIndex = static_cast<unsigned int>(index.z * indexExtent.x * indexExtent.y + index.y * indexExtent.x + index.x);
						intersectedVoxel.push_back(grid->setCandidate(objectsIndex, 3));
                    }
                }               
}

bool Sphere::sphereBoxOverlap(glm::vec3 C1, glm::vec3 C2, glm::vec3 S, float R){
	float dist_squared = R * R;
	if(glm::length(((C1 + C2) * 0.5f) - S) < R - 1.5f * abs(C2.x - C1.x))
		return false;
    if (S.x < C1.x) 
		dist_squared -= (S.x - C1.x) * (S.x - C1.x);
    else if (S.x > C2.x) 
		dist_squared -= (S.x - C2.x) * (S.x - C2.x);
    if (S.y < C1.y) 
		dist_squared -= (S.y - C1.y) * (S.y - C1.y);
    else if (S.y > C2.y)
		dist_squared -= (S.y - C2.y) * (S.y - C2.y);
    if (S.z < C1.z) 
		dist_squared -= (S.z - C1.z) * (S.z - C1.z);
    else if (S.z > C2.z)
		dist_squared -= (S.z - C2.z) * (S.z - C2.z);
    return dist_squared > 0;
}

void Sphere::render() 
{
	glBindVertexArray(m_VertexArray);
	glDrawElements(GL_TRIANGLES, m_indices, GL_UNSIGNED_INT, 0);
}
#include "Triangle.h"

Triangle::Triangle(glm::vec3 A, glm::vec3 B, glm::vec3 C){
    points.resize(0);
    points.push_back(A);
    points.push_back(B);
    points.push_back(C);
    m_A = A;
    m_B = B;
    m_C = C;
    glGenVertexArrays(1, &VertexArray);
    glBindVertexArray(VertexArray);

    glGenBuffers(1, VertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), &points[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Triangle::intersectVoxel(Uniformgrid* grid){

    for(int i = 0; i < intersectedVoxel.size(); i++){
		grid->removeCandidate(intersectedVoxel[i].x, intersectedVoxel[i].y); 
	}
    
    glm::vec3 max = glm::max(glm::max(m_A, m_B), m_C);
    glm::vec3 min = glm::min(glm::min(m_A, m_B), m_C);
    max = glm::ceil(max / grid->m_voxelSize) * grid->m_voxelSize;
    min = glm::floor(min / grid->m_voxelSize) * grid->m_voxelSize;

    glm::vec3 indexExtent = grid->m_extents / grid->m_voxelSize;

    glm::mat3 Temptriverts;
    Temptriverts[0] = m_A;
    Temptriverts[1] = m_B;
    Temptriverts[2] = m_C;
    for(float x = min.x; x <= max.x; x+= grid->m_voxelSize)
        for(float y = min.y; y <= max.y; y+= grid->m_voxelSize)
            for(float z = min.z; z <= max.z; z+= grid->m_voxelSize)
                {
                    glm::vec3 temp = glm::vec3(x,y,z) + glm::vec3(0.5f * grid->m_voxelSize);
                    glm::ivec3 index = glm::ivec3((temp - grid->m_min) / grid->m_voxelSize);
                    glm::vec3 halfSize(grid->m_voxelSize / 2.0f);
                    if(triBoxOverlap(temp, halfSize, Temptriverts)){
                        int objectsIndex = static_cast<unsigned int>(index.z * indexExtent.x * indexExtent.y + index.y * indexExtent.x + index.x);
                        intersectedVoxel.push_back(grid->setCandidate(objectsIndex, 1));
                    }
                }               
}
void Triangle::render(){
    glBindVertexArray(VertexArray);
    glDrawArrays(GL_TRIANGLES, 0, (GLint) points.size() * 3);
}
void Triangle::findMinMax(float x0, float x1, float x2, float &min,float &max){
    min = max = x0;   
    if(x1 < min) min = x1;
    if(x1 > max) max = x1;
    if(x2 < min) min = x2;
    if(x2 > max) max = x2;
}
int Triangle::planeBoxOverlap(glm::vec3 normal, glm::vec3 vert, glm::vec3 maxbox)
{
  glm::vec3 vmin,vmax;
  float v;
  int q;
  for(q = 0; q <= 2; q++){
    v=vert[q];
    if(normal[q]>0.0f){
        vmin[q]=-maxbox[q] - v;
        vmax[q]= maxbox[q] - v;
    }else{
        vmin[q]= maxbox[q] - v;
        vmax[q]=-maxbox[q] - v;
    }
  }
  if(glm::dot(normal,vmin)>0.0f) 
        return 0;
  if(glm::dot(normal,vmax)>=0.0f) 
        return 1;
  return 0;
}
int Triangle::triBoxOverlap(glm::vec3 boxcenter,glm::vec3 boxhalfsize,glm::mat3 triverts)
{
    glm::vec3 v0,v1,v2;
    float min,max,p0,p1,p2,rad,fex,fey,fez;
    glm::vec3 normal,e0,e1,e2;
    v0 = triverts[0] - boxcenter;
    v1 = triverts[1] - boxcenter;
    v2 = triverts[2] - boxcenter;
    e0 = v1 - v0;
    e1 = v2 - v1;
    e2 = v0 - v2;

    fex = fabsf(e0[0]);
    fey = fabsf(e0[1]);
    fez = fabsf(e0[2]);

    p0 = e0[2]*v0[1] - e0[1]*v0[2];
    p2 = e0[2]*v2[1] - e0[1]*v2[2];
    if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;}
    rad = fez * boxhalfsize[1] + fey * boxhalfsize[2];
    if(min>rad || max<-rad) return 0;

	p0 = -e0[2]*v0[0] + e0[0]*v0[2];
	p2 = -e0[2]*v2[0] + e0[0]*v2[2];
    if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;}
	rad = fez * boxhalfsize[0] + fex * boxhalfsize[2];
	if(min>rad || max<-rad) return 0;

	p1 = e0[1]*v1[0] - e0[0]*v1[1];
	p2 = e0[1]*v2[0] - e0[0]*v2[1];
    if(p2<p1) {min=p2; max=p1;} else {min=p1; max=p2;}
	rad = fey * boxhalfsize[0] + fex * boxhalfsize[1];
	if(min>rad || max<-rad) return 0;

    fex = fabsf(e1[0]);
    fey = fabsf(e1[1]);
    fez = fabsf(e1[2]);

    p0 = e1[2]*v0[1] - e1[1]*v0[2];
    p2 = e1[2]*v2[1] - e1[1]*v2[2];
    if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;}
    rad = fez * boxhalfsize[1] + fey * boxhalfsize[2];
    if(min>rad || max<-rad) return 0;

    p0 = -e1[2]*v0[0] + e1[0]*v0[2];
    p2 = -e1[2]*v2[0] + e1[0]*v2[2];
    if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;}
    rad = fez * boxhalfsize[0] + fex * boxhalfsize[2];
    if(min>rad || max<-rad) return 0;

    p0 = e1[1]*v0[0] - e1[0]*v0[1];
    p1 = e1[1]*v1[0] - e1[0]*v1[1];
    if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;}
    rad = fey * boxhalfsize[0] + fex * boxhalfsize[1];
    if(min>rad || max<-rad) return 0;

    fex = fabsf(e2[0]);
    fey = fabsf(e2[1]);
    fez = fabsf(e2[2]);

    p0 = e2[2]*v0[1] - e2[1]*v0[2];
    p1 = e2[2]*v1[1] - e2[1]*v1[2];
    if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;}
    rad = fez * boxhalfsize[1] + fey * boxhalfsize[2];
    if(min>rad || max<-rad) return 0;

    p0 = -e2[2]*v0[0] + e2[0]*v0[2];
    p1 = -e2[2]*v1[0] + e2[0]*v1[2];
    if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;}
    rad = fez * boxhalfsize[0] + fex * boxhalfsize[2];
    if(min>rad || max<-rad) return 0;

    p1 = e2[1]*v1[0] - e2[0]*v1[1];
    p2 = e2[1]*v2[0] - e2[0]*v2[1];
    if(p2<p1) {min=p2; max=p1;} else {min=p1; max=p2;}
    rad = fey * boxhalfsize[0] + fex * boxhalfsize[1];
    if(min>rad || max<-rad) return 0;

    findMinMax(v0[0],v1[0],v2[0],min,max);
    if(min>boxhalfsize[0] || max<-boxhalfsize[0]) return 0;

    findMinMax(v0[1],v1[1],v2[1],min,max);
    if(min>boxhalfsize[1] || max<-boxhalfsize[1]) return 0;

    findMinMax(v0[2],v1[2],v2[2],min,max);
    if(min>boxhalfsize[2] || max<-boxhalfsize[2]) return 0;
    
    normal = glm::cross(e0,e1);

    if(!planeBoxOverlap(normal,v0,boxhalfsize)) return 0;
    return 1;
}
#pragma once
#include <Tools/Defs.h>

class Camera
{
public:
	Camera(int width, int height, float fov);
	~Camera();
	void getView(glm::vec3* x, glm::vec3* y, glm::vec3* z, glm::vec3* pos) const;
	glm::mat4 getViewMatrix();
	glm::vec3 getEye();
	float getFov();
	void setResolution(unsigned int w, unsigned int h);
	void updateCamPos(double xpos, double ypos, bool active);
	void updateRadius(double yoffset);
private:
	float Pi = 3.141592f;
	float radius;
	glm::vec2 Angle;
	glm::vec2 Oldpos;
	glm::vec2 Newpos;
	int m_width;
	int m_height;
	void updateMatrix();
	float m_fov;
	glm::mat4 m_viewMatrix;
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;
};


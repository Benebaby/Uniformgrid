#include <Tools/Defs.h>
#include <Tools/ShaderSet.h>
#include <vector>
#include "Camera.h"
#include "Cube.h"
#include "Uniformgrid.h"
#include "Triangle.h"
#include "Line.h"
#include "Sphere.h"

int width = 1600;
int height = 900;
const float FOV = 45.0f;

GLFWwindow* window;
Camera* cam = new Camera(width, height, FOV);
glm::mat4 projectionMatrix = glm::perspective(glm::radians(FOV), (float)width / height, 0.1f, 100.0f);

void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	cam->updateRadius(yoffset * 5.0f);
}

void MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		cam->updateCamPos(xpos, ypos, true);
	else
		cam->updateCamPos(xpos, ypos, false);
}

void resizeCallback(GLFWwindow *window, int w, int h) {
	width = w;
	height = h;
	projectionMatrix = glm::perspective(3.141f * 40.0f / 180.0f, width / (float)height, 0.1f, 500.0f);
	cam->setResolution(width, height);
	glViewport(0, 0, width, height);
}

int main(void)
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(width, height, "UniformGridDemo", NULL, NULL);
	glfwSetWindowPos(window, 150, 90);
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSetCursorPosCallback(window, &MouseCallback);
	glfwSetScrollCallback(window, &ScrollCallback);
	glfwSetWindowSizeCallback(window, &resizeCallback);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	std::cout << glGetString(GL_VERSION) << std::endl;

	glm::mat4 modelMatrix(1.0f);
	glm::vec4 light_pos(-30.0f, 30.0f, 30.0f, 1.0f);
	glm::vec3 light_col(1.0f);
	glm::vec3 light_ambient(0.3f);
	glm::vec3 mat_diffuse(1.0f, 0.0f, 0.0f);
	glm::vec3 mat_specular(1.0f);
	float mat_shininess = 5.0f;

	const char *minimalshaderfiles[2] = { SHADERS_PATH"/UniformGridDemo/minimal.vert", SHADERS_PATH"/UniformGridDemo/minimal.frag" };
	ShaderSet minimalShaderProgram(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, minimalshaderfiles);
	minimalShaderProgram.UseProgram();
	GLuint m_modelMatrixID = glGetUniformLocation(minimalShaderProgram.getProgramID(), "modelMatrix");
	GLuint m_viewMatrixID = glGetUniformLocation(minimalShaderProgram.getProgramID(), "viewMatrix");;
	GLuint m_projectionMatrixID = glGetUniformLocation(minimalShaderProgram.getProgramID(), "projectionMatrix");
	GLuint m_colorID = glGetUniformLocation(minimalShaderProgram.getProgramID(), "color");

	Uniformgrid grid = Uniformgrid(glm::vec3(0.0f), glm::vec3(24.f), 0.125f);

	const char *phongshaderfiles[2] = {SHADERS_PATH"/UniformGridDemo/phong.vert", SHADERS_PATH"/UniformGridDemo/phong.frag" };
	ShaderSet phongShaderProgram(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, phongshaderfiles);
	phongShaderProgram.UseProgram();
	GLuint modelID = glGetUniformLocation(phongShaderProgram.getProgramID(), "modelMatrix");
	GLuint viewID = glGetUniformLocation(phongShaderProgram.getProgramID(), "viewMatrix");
	GLuint projectionID = glGetUniformLocation(phongShaderProgram.getProgramID(), "projectionMatrix");
	GLuint lightID = glGetUniformLocation(phongShaderProgram.getProgramID(), "light_pos");
	GLuint lightcolorID = glGetUniformLocation(phongShaderProgram.getProgramID(), "light_col");
	GLuint diffuseID = glGetUniformLocation(phongShaderProgram.getProgramID(), "mat_diffuse");
	GLuint specularID = glGetUniformLocation(phongShaderProgram.getProgramID(), "mat_specular");
	GLuint shininessID = glGetUniformLocation(phongShaderProgram.getProgramID(), "mat_shininess");
	GLuint ambientID = glGetUniformLocation(phongShaderProgram.getProgramID(), "light_ambient");

	Triangle t  = Triangle(glm::ballRand(10.f), glm::ballRand(10.f), glm::ballRand(10.f));
	t.intersectVoxel(&grid);
	Triangle t2 = Triangle(glm::ballRand(10.f), glm::ballRand(10.f), glm::ballRand(10.f));
	t2.intersectVoxel(&grid);
	Triangle t3 = Triangle(glm::ballRand(10.f), glm::ballRand(10.f), glm::ballRand(10.f));
	t3.intersectVoxel(&grid);
	Sphere ball = Sphere(glm::vec3(0.f), 2.f, 50);
	ball.intersectVoxel(&grid);
	Line l = Line(glm::vec3(-9, 9, -9), glm::normalize(glm::vec3(1, -1, 1.2)), 25.455f);
	l.intersectVoxel(&grid);
	Line l1 = Line(glm::vec3(9, 9, -9), glm::normalize(glm::vec3(-1.589, -1.8, 1.2)), 25.455f);
	l1.intersectVoxel(&grid);

	grid.createCandidates();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSwapInterval(0);
	double start = glfwGetTime();
	bool isDone = false;
	while (!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		minimalShaderProgram.UseProgram();
		glEnable(GL_BLEND);
		mat_diffuse = glm::vec3(1.0f,1.0f,1.0f);
		glUniformMatrix4fv(m_modelMatrixID, 1, false, glm::value_ptr(modelMatrix));
    	glUniformMatrix4fv(m_viewMatrixID, 1, false, glm::value_ptr(cam->getViewMatrix()));
		glUniformMatrix4fv(m_projectionMatrixID, 1, false, glm::value_ptr(projectionMatrix));
		glUniform3fv(m_colorID, 1, glm::value_ptr(mat_diffuse));
		// grid.render();
		glDisable(GL_BLEND);
		mat_diffuse = glm::vec3(1.0f,0.0f,0.0f);
		glUniform3fv(m_colorID, 1, glm::value_ptr(mat_diffuse));
		glLineWidth(2.0f);
		 t.render();
		t2.render();
		t3.render();
		 l.render();
		l1.render();

		phongShaderProgram.UseProgram();
		glLineWidth(1.0f);
		mat_diffuse = glm::vec3(0.0f,0.8f,0.0f);
		glUniformMatrix4fv(modelID, 1, false, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(viewID, 1, false, glm::value_ptr(cam->getViewMatrix()));
		glUniformMatrix4fv(projectionID, 1, false, glm::value_ptr(projectionMatrix));
		glUniform4fv(lightID, 1, glm::value_ptr(light_pos));
		glUniform3fv(lightcolorID, 1, glm::value_ptr(light_col));
		glUniform3fv(ambientID, 1, glm::value_ptr(light_ambient));
		glUniform3fv(specularID, 1, glm::value_ptr(mat_specular));
		glUniform1f(shininessID, mat_shininess);
		glUniform3fv(diffuseID, 1, glm::value_ptr(mat_diffuse));
		if(!isDone && glfwGetTime() - start > 20.0)
		{
			isDone = true;
			ball.m_center = glm::vec3(2.0f);
			ball.intersectVoxel(&grid);
			l.intersectVoxel(&grid);
			l1.intersectVoxel(&grid);
			grid.createCandidates();
		}

		grid.renderCandidates();
		if(!isDone)
			ball.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
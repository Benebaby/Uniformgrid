#include <Tools/CompatibilityTools.h>
#include <Tools/Defs.h>
#include <iostream>
#include <string.h>

void CompatibilityTools::useOpenGL33CoreProfile()
{

  #if defined(__APPLE__) || defined(__linux__)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  #endif
}

void CompatibilityTools::checkCompatibility()
{
        
	std::cout << "** Testing Compatibility **" << std::endl;

	GLint data = 0;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &data);
	std::cout << "GL_MAX_COMPUTE_WORK_GROUP_SIZE: " << data;
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &data);
	std::cout << " * " << data;
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &data);
	std::cout << " * " << data << std::endl;
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &data);
	std::cout << "GL_MAX_COMPUTE_WORK_GROUP_COUNT: " << data;
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &data);
	std::cout << " * " << data;
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &data);
	std::cout << " * " << data << std::endl;
	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &data);
	std::cout << "GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS: " << data << std::endl;
	glGetIntegerv(GL_MAX_COMPUTE_SHARED_MEMORY_SIZE, &data);
	std::cout << "GL_MAX_COMPUTE_SHARED_MEMORY_SIZE: " << data / 1024 << "KB" << std::endl;
}

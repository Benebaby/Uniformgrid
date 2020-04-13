#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <iostream>

#define VERTICES 0
#define NORMALS 1
#define TEXTURECOORDS 2

#define COLOR_TEXTURE_UNIT GL_TEXTURE0
#define SHADOW_TEXTURE_UNIT GL_TEXTURE1
#define NORMAL_TEXTURE_UNIT GL_TEXTURE2

#define NO_TEXTURE_BIT 0
#define COLOR_TEXTURE_BIT 1
#define SHADOW_TEXTURE_BIT 2
#define NORMAL_TEXTURE_BIT 4

#define VERTEX_SHADER_BIT 1
#define TESS_CONTROL_BIT 2
#define TESS_EVAL_BIT 4
#define GEOMETRY_SHADER_BIT 8
#define FRAGMENT_SHADER_BIT 16
#define COMPUTE_SHADER_BIT 32

#define MAT_AMBIENT_BIT 1
#define MAT_DIFFUSE_BIT 2
#define MAT_SPECULAR_BIT 4
#define MAT_TRANSPARENCY_BIT 8

#define LIGHT_DIR 0
#define LIGHT_POINT 1

#define INVALID_OGL_VALUE 0xFFFFFFFF


/**
 * @file OpenGL.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once
#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <glm.hpp>

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>



/**
 * @brief Initialize GLEW
 * 
 * @return GLenum 
 */
static GLenum  InitOpenGL()
{
	
	return glewInit();
}

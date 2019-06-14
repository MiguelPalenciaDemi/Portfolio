/**
 * @file Shader.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once
#include <memory>
#include <map>
#include <iostream>
#include "OpenGL.hpp"

namespace render
{

	/**
	 * @brief Shader class
	 * 
	 */
	class Shader
	{
		public:

			/**
			 * @brief Type Shader
			 * 
			 */
			enum Shader_Type
			{
				vertex_shader, fragment_shader
			};

		private:

			/**
			 * @brief Source code 
			 * 
			 */
			std::string code;

			/**
			 * @brief Shader id
			 * 
			 */
			GLuint id;

			/**
			 * @brief code lenght
			 * 
			 */
			GLint size;

			/**
			 * @brief Type of shader
			 * 
			 */
			Shader_Type type;
			

		public:

			/**
			 * @brief Construct a new Shader object
			 * 
			 * @param _type 
			 * @param _code 
			 */
			Shader(Shader_Type _type,std::string _code): type(_type)
			{
				code = _code;
				size = (GLuint)_code.size();
				create();
			}

			
			/**
			 * @brief Create shader
			 * 
			 */
			void create()
			{			

				if (type == Shader::Shader_Type::fragment_shader)
					id = glCreateShader(GL_FRAGMENT_SHADER);
				else					
					id = glCreateShader(GL_VERTEX_SHADER);
				const char* code_shader = code.c_str();
				glShaderSource(id, 1, &code_shader, &size);
				compile_shader();
			}

			/**
			 * @brief Compile shader
			 * 
			 * @return true 
			 * @return false 
			 */
			bool compile_shader()
			{				
				glCompileShader(id);
				int success;
				GLchar error[1024];
				glGetShaderiv(id, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(id, 1024, NULL, error);
					std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << error << "\n -- --------------------------------------------------- -- " << std::endl;
					return false;
				}
				
				return true;
			
			}

			/**
			 * @brief Get the id 
			 * 
			 * @return GLuint 
			 */
			GLuint get_id() { return id; }
						

	
	};


}
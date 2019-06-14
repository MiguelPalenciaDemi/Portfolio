/**
 * @file Shader_Program.hpp
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
#include "OpenGL.hpp"
#include "Shader.hpp"
#include "Shader_List.hpp"

namespace render
{
	

	/**
	 * @brief Shader Program class
	 * 
	 */
	class Shader_Program
	{
		
		private:

			/**
			 * @brief active shader program 
			 * 
			 */
			static Shader_Program * active_shader_program;	

			/**
			 * @brief collection of shaders
			 * 
			 */
			std::map<int, std::shared_ptr<Shader>> shaders;

			/**
			 * @brief Shader Program ID
			 * 
			 */
			GLuint id; 

		public:

			/**
			 * @brief Construct a new Shader_Program object
			 * 
			 * @param vertex_shader 
			 * @param fragment_shader 
			 */
			Shader_Program(std::string vertex_shader, std::string fragment_shader);

			/**
			 * @brief Construct a new Shader_Program object
			 * 
			 */
			Shader_Program();
			
			/**
			 * @brief add shader to the program
			 * 
			 * @param type 
			 * @param code 
			 */
			void add_Shader(Shader::Shader_Type type, std::string code);
			
			/**
			 * @brief attach a shader to the shader program 
			 * 
			 * @param shader 
			 */
			void link_shader(std::shared_ptr<Shader> shader)
			{
				glAttachShader(id, shader->get_id());
			}

			/**
			 * @brief Detach a shader from the shader program
			 * 
			 * @param shader 
			 */
			void detach_shader(std::shared_ptr<Shader> shader)
			{
				glDetachShader(id, shader->get_id());
			}

			/**
			 * @brief Link the program to OpenGL
			 * 
			 */
			void link_program();

			/**
			 * @brief Check if its linked succesfully
			 * 
			 * @return true 
			 * @return false 
			 */
			bool check_link();
			
			/**
			 * @brief Get the id program
			 * 
			 * @return GLuint 
			 */
			GLuint get_id() { return id; }
			void use();			

			/**
			 * @brief Set the uniform bool value
			 * 
			 * @param name 
			 * @param value 
			 */
			void set_uniform_bool(const std::string &name, bool value) const
			{
				glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
			}

			/**
			 * @brief Set the uniform int value
			 * 
			 * @param name 
			 * @param value 
			 */
			void set_uniform_int(const std::string &name, int value) const
			{
				glUniform1i(glGetUniformLocation(id, name.c_str()), value);
			}

			/**
			 * @brief Set the uniform float value
			 * 
			 * @param name 
			 * @param value 
			 */
			void set_uniform_float(const std::string &name, float value) const
			{		
				GLint error = glGetUniformLocation(id, name.c_str());
				if (error == -1)
					std::cout << "ERROR FLOAT: " << name << std::endl;
				glUniform1f(glGetUniformLocation(id, name.c_str()), value);
			}

			/**
			 * @brief Set the uniform matrix4 value
			 * 
			 * @param name 
			 * @param value 
			 */
			void set_uniform_matrix4(const std::string &name, const glm::mat4  value) const
			{
				glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
			}

			/**
			 * @brief Set the uniform matrix3 value
			 * 
			 * @param name 
			 * @param value 
			 */
			void set_uniform_matrix3(const std::string &name, const glm::mat3  value) const
			{
				glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
			}

			/**
			 * @brief Set the uniform matrix2 value
			 * 
			 * @param name 
			 * @param value 
			 */
			void set_uniform_matrix2(const std::string &name, const glm::mat2  value) const
			{
				glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
			}

			/**
			 * @brief Set the uniform vec2 value
			 * 
			 * @param name 
			 * @param value 
			 */
			void set_uniform_vec2(const std::string &name, const glm::vec2  value) const
			{
				glUniform2f(glGetUniformLocation(id, name.c_str()), value.x, value.y);
			}

			/**
			 * @brief Set the uniform vec3 value
			 * 
			 * @param name 
			 * @param value 
			 */
			void set_uniform_vec3(const std::string &name, const glm::vec3  value) const
			{				
				GLint error = glGetUniformLocation(id, name.c_str());
				if (error == -1)
					std::cout << "ERROR Vec3: " << name << std::endl;
				glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);				
			}

			/**
			 * @brief Set the uniform vec4 value
			 * 
			 * @param name 
			 * @param value 
			 */
			void set_uniform_vec4(const std::string &name, const glm::vec4  value) const
			{				
				glUniform4f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z,value.w);
			}
		
			
	
	
	};


}
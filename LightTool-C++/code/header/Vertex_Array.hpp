/**
 * @file Vertex_Array.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once
#include "OpenGL.hpp"

namespace render
{
	/**
	 * @brief Vertex array object
	 * 
	 */
	class Vertex_Array
	{

	private: 
		
		/**
		 * @brief id vertex buffer
		 * 
		 */
		GLuint vao_id;

		/**
		 * @brief number of attributes
		 * 
		 */
		GLuint numAttribs;

	public: 

		/**
		 * @brief Construct a new Vertex_Array object
		 * 
		 */
		Vertex_Array()
		{
			glGenVertexArrays(1, &vao_id);	
			numAttribs = 0;
		}

		/**
		 * @brief Destroy the Vertex_Array object
		 * 
		 */
		~Vertex_Array()
		{
			glDeleteVertexArrays(1, &vao_id);
		}

		/**
		 * @brief Bind vertex array
		 * 
		 */
		void bind() { glBindVertexArray(vao_id); }

		/**
		 * @brief Unbind vertex array
		 * 
		 */
		void unbind() { glBindVertexArray(0); }
		
		/**
		 * @brief add atrribute
		 * 
		 * @param num_attribute 
		 * @param buffer 
		 */
		void add_attribute( GLuint num_attribute, Vertex_Buffer& buffer)
		{
			glBindBuffer(GL_ARRAY_BUFFER, buffer.get_id());
			glEnableVertexAttribArray(num_attribute);
			glVertexAttribPointer(num_attribute,buffer.get_pack(), buffer.get_type(), buffer.get_is_normalized(), 0, 0);
			numAttribs++;
		}
	
	
	};

}
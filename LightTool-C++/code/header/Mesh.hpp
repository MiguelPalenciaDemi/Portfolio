/**
 * @file Mesh.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once
#include <cmath>
#include <memory>
#include <string>
#include "OpenGL.hpp"
#include "Vertex_Buffer.hpp"
#include "Vertex_Array.hpp"

namespace render
{
	/**
	 * @brief Mesh class
	 * 
	 */
	class Mesh
	{

	protected:

		/**
		 * @brief Coordinate vertex buffer 
		 * 
		 */
		std::shared_ptr<Vertex_Buffer> coordinates_vbo;

		/**
		 * @brief Normal vertex buffer
		 * 
		 */
		std::shared_ptr<Vertex_Buffer> normals_vbo;

		/**
		 * @brief Texture coordinate vertex buffer
		 * 
		 */
		std::shared_ptr<Vertex_Buffer> text_coord_vbo;

		/**
		 * @brief Vertex  array buffer
		 * 
		 */
		std::shared_ptr<Vertex_Array>  vao;

		/**
		 * @brief Error log
		 * 
		 */
		std::string error;

		/**
		 * @brief size of the coordinate buffer
		 * 
		 */
		GLsizei size_buffer;
	

	public:

		/**
		 * @brief Construct a new Mesh object
		 * 
		 */
		Mesh();
		
		/**
		 * @brief Construct a new Mesh object. Load an obj
		 * 
		 * @param path 
		 */
		Mesh(const std::string&  path);

		~Mesh()
		{			
			glDeleteBuffers(1, &coordinates_vbo->get_id());
			glDeleteBuffers(1, &normals_vbo->get_id());
			glDeleteBuffers(1, &text_coord_vbo->get_id());
			
		}		
		
		/**
		 * @brief render mesh
		 * 
		 */
		virtual void render() 
		{		
			vao->bind();//Bind the vertex array
			glDrawArrays(GL_TRIANGLES, 0, size_buffer); //Draw the content
			vao->unbind(); //Disconect
		
		};
		
	
		
	};

}


/**
 * @file Vertex_Buffer.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once
//#include <SFML\OpenGL.hpp>
#include <GL\glew.h>
#include <glm.hpp>

namespace render
{

	/**
	 * @brief Vetex buffer object class
	 * 
	 */
	class Vertex_Buffer
	{
	private:

		/**
		 * @brief id vbo
		 * 
		 */
		GLuint vbo_id;

		/**
		 * @brief buffer size
		 * 
		 */
		GLsizeiptr size_buffer;

		/**
		 * @brief target
		 * 
		 */
		GLenum target;

		/**
		 * @brief type
		 * 
		 */
		GLenum type;

		/**
		 * @brief size of pack. Vertex,Normals = 3 UV = 2
		 * 
		 */
		GLuint size_pack;

		/**
		 * @brief Is normalized?
		 * 
		 */
		GLboolean is_normalized;
		
	public:

		/**
		 * @brief Construct a new Vertex_Buffer object
		 * 
		 * @param size 
		 * @param _size_pack 
		 * @param data 
		 * @param usage 
		 */
		Vertex_Buffer(GLsizeiptr size,GLuint _size_pack, GLvoid* data, GLenum usage)
		{
			target = GL_ARRAY_BUFFER;
			type = GL_FLOAT;
			size_pack = _size_pack;
			is_normalized = GL_FALSE;

			glGenBuffers(1, &vbo_id);
			set_up_buffer(size,data,usage);
		}

		/**
		 * @brief Construct a new Vertex_Buffer object
		 * 
		 */
		Vertex_Buffer()
		{
			glGenBuffers(1,&vbo_id);
		}

		/**
		 * @brief Destroy the Vertex_Buffer object
		 * 
		 */
		 ~Vertex_Buffer()
		 {
			 glDeleteBuffers(1, &vbo_id);
		 }

		/**
		 * @brief Get the id 
		 * 
		 * @return GLuint& 
		 */
		GLuint& get_id() { return vbo_id; }

		/**
		 * @brief Get the size buffer
		 * 
		 * @return const GLsizeiptr 
		 */
		const GLsizeiptr get_size() { return size_buffer; }

		/**
		 * @brief Get the type 
		 * 
		 * @return GLenum 
		 */
		GLenum get_type() { return type; }

		/**
		 * @brief Get the pack size
		 * 
		 * @return GLuint 
		 */
		GLuint get_pack() { return size_pack; }

		/**
		 * @brief Get the is normalized  bool
		 * 
		 * @return GLboolean 
		 */
		GLboolean get_is_normalized() { return is_normalized; }

		/**
		 * @brief bind buffer
		 * 
		 */
		void bind_buffer()  { glBindBuffer(target, vbo_id); }

		/**
		 * @brief unbind buffer
		 * 
		 */
		void unbind_buffer(){ glBindBuffer(target, 0); }
		
		/**
		 * @brief Set up buffer 
		 * 
		 * @param size 
		 * @param data 
		 * @param usage 
		 */
		void set_up_buffer(GLsizeiptr size,GLvoid* data, GLenum usage)
		{
			size_buffer = size;
			bind_buffer();
			glBufferData(target, size_buffer,data,usage);//Fill the buffer
			

		}
	
	};

}
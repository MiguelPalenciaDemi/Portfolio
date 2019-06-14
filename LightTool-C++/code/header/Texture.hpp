/**
 * @file Texture.hpp
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
#include "Shader_Program.hpp"
#include <list>
#include <memory>
#include <map>

extern "C"
{
	#include <targa.h>
}

namespace render
{
	class Color_Buffer_Rgba8888;

	/**
	 * @brief Buffer color
	 * 
	 */
	typedef Color_Buffer_Rgba8888 Texture_Color;

	/**
	 * @brief Texture class
	 * 
	 */
	class Texture
	{
		

	protected:

		/**
		 * @brief Texture id
		 * 
		 */
		GLuint id;

		/**
		 * @brief static collection of paths
		 * 
		 */
		static std::map<std::string, std::shared_ptr<Texture_Color>> textures_loaded;

	public:

		/**
		 * @brief Construct a new Texture object
		 * 
		 */
		Texture() {};

		/**
		 * @brief Destroy the Texture object
		 * 
		 */
		~Texture() { glDeleteTextures(1, &id); }

		/**
		 * @brief load a texture TGA
		 * 
		 * @param path 
		 * @return std::shared_ptr<Texture_Color> 
		 */
		std::shared_ptr<Texture_Color> load_texture(const char* path);

		/**
		 * @brief bind the texture to OpenGL
		 * 
		 * @param index 
		 */
		virtual void bind(int index) = 0;
		
	
	
	};


}
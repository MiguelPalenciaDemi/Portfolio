/**
 * @file Texture2D.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once
#include "Texture.hpp"



namespace render
{
	/**
	 * @brief Texture 2D class
	 * 
	 */
	class Texture2D:public Texture
	{
		
	public:

		/**
		 * @brief Construct a new Texture 2D object
		 * 
		 * @param path 
		 */
		Texture2D(const char * path);

		/**
		 * @brief bind the texture to OpenGL
		 * 
		 * @param index 
		 */
		void bind(int index)override;
	
	
	};


}
/**
 * @file Texture_Cubemap.hpp
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
	 * @brief Cubemap texture class
	 * 
	 */
	class Texture_Cubemap:public Texture
	{
		
	public:

		/**
		 * @brief Construct a new Texture_Cubemap texture
		 * 
		 * @param path 
		 */
		Texture_Cubemap(const char* path);

		/**
		 * @brief bind the texture
		 * 
		 * @param index 
		 */
		void bind(int index) override;
	
	
	};


}
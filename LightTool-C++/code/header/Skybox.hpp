/**
 * @file Skybox.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once
#include "Texture_Cubemap.hpp"
#include "Material.hpp"
#include "Scene.hpp"
#include "Vertex_Buffer.hpp"
#include "Vertex_Array.hpp"


namespace render
{
	/**
	 * @brief Skybox class
	 * 
	 */
	class Skybox:public Material
	{
		/**
		 * @brief Texture coord buffer
		 * 
		 */
		std::shared_ptr<Vertex_Buffer> texture_coord_vbo;
		/**
		 * @brief vertex array buffer
		 * 
		 */
		std::shared_ptr<Vertex_Array> vao;
		/**
		 * @brief Cubemap texture
		 * 
		 */
		std::shared_ptr<Texture_Cubemap> sky;

		/**
		 * @brief Scene where it belongs to
		 * 
		 */
		Scene* own_scene;
		


	public:

		/**
		 * @brief Construct a new Skybox object
		 * 
		 */
		Skybox() {}

		/**
		 * @brief Construct a new Skybox object
		 * 
		 * @param path 
		 * @param scene 
		 */
		Skybox(const char* path, Scene* scene);

		/**
		 * @brief Render function
		 * 
		 */
		void render();
		
	
	};


}
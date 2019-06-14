/**
 * @file Terrain.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once 
#include "Model.hpp"
#include "Material.hpp"
#include "Scene.hpp"
#include "Mesh.hpp"


namespace render 
{

	/**
	 * @brief Terrain class
	 * 
	 */
	class Terrain
	{
	
	public: 

		/**
		 * @brief Construct a new Terrain model
		 * 
		 * @param name 
		 * @param scene 
		 */
		Terrain(std::string name, Scene* scene)
		{
			std::shared_ptr<Model> mountains;
			mountains.reset(new Model(scene, nullptr));

			std::vector<std::string> paths = { "../../assets/island2.tga" };

			std::shared_ptr<Material> material;		
			material.reset(new Material(GL_TEXTURE_2D, paths,vertex_shader_heightmap, default_fragment_shader_code));			
			
			std::shared_ptr<Mesh> mesh;
			mesh.reset(new Mesh("../../assets/plane.obj"));

			mountains->add_piece("base", mesh, material);
			scene->add_model(name, mountains);
		
		
		}
	
	};


}
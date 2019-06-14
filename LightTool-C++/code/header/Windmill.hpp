/**
 * @file Windmill.hpp
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
#include "Transform.hpp"


namespace render
{

	/**
	 * @brief Windmill class
	 * 
	 */
	class Windmill
	{
		/**
		 * @brief base model
		 * 
		 */
		std::shared_ptr<Model> base;

		/**
		 * @brief aspas model
		 * 
		 */
		std::shared_ptr<Model> aspas;

		/**
		 * @brief aspas speed
		 * 
		 */
		float speed;

	public:

		/**
		 * @brief Construct a new Windmill object
		 * 
		 * @param name 
		 * @param scene 
		 * @param position 
		 * @param _speed 
		 */
		Windmill(std::string name,Scene* scene,glm::vec3 position,float _speed = 0.5f)
		{
			speed = _speed;
			base.reset(new Model(scene, nullptr));
			aspas.reset(new Model(scene, base));

			std::shared_ptr<Mesh> base_mesh;
			base_mesh.reset(new Mesh("../../assets/base-molino.obj"));

			std::shared_ptr<Mesh> aspas_mesh;
			aspas_mesh.reset(new Mesh("../../assets/aspas-molino.obj"));


			std::shared_ptr<Material> base_material;
			std::shared_ptr<Material> aspas_material;
			std::vector<std::string> path = { "../../assets/aspas_material.tga" };
			std::vector<std::string> paths = { "../../assets/wood.tga" };
			base_material.reset(new Material(GL_TEXTURE_2D,paths));
			aspas_material.reset(new Material(GL_TEXTURE_2D,path));

			base->add_piece("base",base_mesh, base_material);
			aspas->add_piece("aspas", aspas_mesh, aspas_material);

			scene->add_model(name+"windmill_base", base);
			scene->add_model(name+"windmill_aspas", aspas);
			//aspas->set_parent(base);
			base->get_transform()->set_position(position.x,position.y,position.z);
			aspas->get_transform()->set_position(0, 30, 0);
			
		
		
		}

		/**
		 * @brief Update function. Rotate aspas
		 * 
		 * @param time 
		 */
		void update(float time)
		{
			aspas->rotate_around_x(speed * time);		
		}

		/**
		 * @brief Get the transform object
		 * 
		 * @return Transform* 
		 */
		Transform* get_transform() { return base->get_transform(); }

	
	};


}
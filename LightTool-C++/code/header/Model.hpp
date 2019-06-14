/**
 * @file Model.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once
#include <list>
#include <memory>
#include <vector>
#include <map>
#include "Actor.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "RigidBody.hpp"
#include "Point_Light.hpp"
#include "Directional_Light.hpp"



namespace render
{
	class Scene;

	/**
	 * @brief Model class. Store the meshes and materials that shape the model
	 * 
	 */
	class Model: public Actor
	{
		/**
		 * @brief Structure that link mesh and material
		 * 
		 */
		typedef std::pair<std::shared_ptr< Mesh >, std::shared_ptr< Material >> piece;		

		private:

			/**
			 * @brief List of all the pieces
			 * 
			 */
			std::map<std::string,piece> list_pieces;


		
		
		public:

			/**
			 * @brief Construct a new Model object
			 * 
			 */
			Model():Actor() {};

			/**
			 * @brief Construct a new Model object
			 * 
			 * @param scene 
			 * @param parent 
			 */
			Model(Scene* scene, std::shared_ptr<Actor> parent) : Actor(scene, parent) {};

			/**
			 * @brief add piece to the collection
			 * 
			 * @param name 
			 * @param mesh 
			 * @param material 
			 */
			void add_piece(std::string name, std::shared_ptr< Mesh >  mesh, const std::shared_ptr< Material >  material);

			/**
			 * @brief Render opaque
			 * 
			 */
			void render();

			/**
			 * @brief Render transparent
			 *
			 */
			void render_opacity();

			/**
			 * @brief Update
			 * 
			 * @param time 
			 */
			void update(float time);
			 
			/**
			 * @brief Get the pieces colection
			 * 
			 * @return std::map<std::string, piece>& 
			 */
			std::map<std::string, piece>& get_pieces() { return list_pieces; }

			/**
			 * @brief Set the directional light values object to a concrete material
			 * 
			 * @param material 
			 */
			void set_directional_light_values(std::shared_ptr<Material> material);
			void set_directional_light_values(std::shared_ptr<Material> material, int index);

			/**
			 * @brief Set the point light values object to a concrete material
			 * 
			 * @param material 
			 * @param index 
			 */
			void set_point_light_values(std::shared_ptr<Material> material,int index);

			/**
			 * @brief Update the directional light values object to a concrete material
			 * 
			 * @param material 
			 */
			void update_directional_light_values(std::shared_ptr<Material> material);
			void update_directional_light_values(std::shared_ptr<Material> material, int index, Directional_Light light);
			void clean_directional_light_values();
			void clean_point_light_values();

			/**
			 * @brief Update the point light values object to a concrete material
			 * 
			 * @param material 
			 * @param index 
			 * @param light 
			 */
			void update_point_light_values(std::shared_ptr<Material> material,int index, Point_Light light);
				
	
	
	};

}
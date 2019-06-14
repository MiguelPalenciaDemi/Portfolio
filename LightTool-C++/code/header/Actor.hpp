
/**
 * @file Actor.hpp
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
#include <memory>

#include "Transform.hpp"



//http://acodigo.blogspot.com/2016/04/cargar-modelo-3d-formato-obj.html
namespace render
{
	
	class Scene;
	class RigidBody;

	/**
	 * @brief Actor Class
	 * 
	 */
	class Actor
	{
	
	protected:
		/**
		 * @brief Pointer to the parent actor
		 * 
		*/	
		std::shared_ptr<Actor> parent;
		/**
		 * @brief Transform object
		 * 
		 */
		Transform local_transform;
		/**
		 * @brief Pointer to the scene where its located
		 * 
		 */
		Scene* own_scene;
		/**
		* @brief RigidBody. Add the physicsn to the model
		*
		*/
		RigidBody* rigid_body;

		/**
		 * @brief it is going to be render
		 * 
		 */
		bool visible; 

	public:

		/**
		 * @brief Construct a new Actor object
		 * 
		 */
		Actor()
		{
			parent = nullptr;
			own_scene = nullptr;
			rigid_body = nullptr;
			visible = true;

		}

		/**
		 * @brief Construct a new Actor object
		 * 
		 * @param _scene 
		 * @param _parent 
		 */
		Actor(Scene* _scene, std::shared_ptr<Actor> _parent);
		
	
		/**
		 * @brief Destroy the Actor object
		 * 
		 */
		~Actor() 
		{
			own_scene = nullptr;
		
		}
		/**
		* @brief Set a new rigid body
		*
		*/
		void set_rigid_body(RigidBody* new_rigid_body) { rigid_body = new_rigid_body; }

		/**
		* @brief Get the RigidBody object
		*
		* @return RigidBody*
		*/
		RigidBody* get_rigid_body() { return rigid_body; }
		/**
		 * @brief Get the transform object
		 * 
		 * @return Transform* 
		 */
		Transform* get_transform(){	return &local_transform; }

		/**
		 * @brief Set the parent object
		 * 
		 * @param new_parent 
		 */
		void set_parent(std::shared_ptr<Actor> new_parent)
		{
			if(new_parent != nullptr)
			{
				parent = new_parent;
				local_transform.set_parent(new_parent->get_transform());
			}
			else
			{
				parent = nullptr;
			}
			
		}
		/**
		 * @brief Get the parent object
		 * 
		 * @return std::shared_ptr<Actor> 
		 */
		std::shared_ptr<Actor> get_parent()
		{
			return parent;
		}

		/**
		 * @brief Set the scene object
		 * 
		 * @param new_scene 
		 */
		void set_scene(Scene* new_scene)
		{
			if(new_scene != nullptr)
			{
				own_scene = new_scene;
			}
			else
			{
				own_scene = nullptr;
			}
		
		
		}

		/**
		 * @brief Set the position object
		 * 
		 * @param new_position 
		 */
		void set_position(glm::vec3 new_position);
		

		/**
		 * @brief Get the position object
		 * 
		 * @return glm::vec3 
		 */
		glm::vec3 get_position()
		{
			return local_transform.get_position();
		}

		/**
		 * @brief Set the scale object
		 * 
		 * @param new_scale 
		 */
		void set_scale(glm::vec3 new_scale)
		{
			local_transform.scale_model(new_scale);
		}

		/**
		 * @brief Get the scale object
		 * 
		 * @return glm::vec3 
		 */
		glm::vec3  get_scale()
		{
			return local_transform.get_scale();
		}

		/**
		 * @brief rotate around x axis
		 * 
		 * @param angle 
		 */
		void rotate_around_x(float angle)
		{
			local_transform.rotate_around_x(angle);
		}

		/**
		 * @brief rotate around y axis
		 * 
		 * @param angle 
		 */
		void rotate_around_y(float angle)
		{
			local_transform.rotate_around_y(angle);
		}

		/**
		 * @brief rotate around z axis
		 * 
		 * @param angle 
		 */
		void rotate_around_z(float angle)
		{
			local_transform.rotate_around_z(angle);
		}
		
		/**
		 * @brief update the transform
		 * 
		 */
		void update();
		
		/**
		* @brief Set visibility
		*
		* @param state
		*/
		void set_visible(bool state) { visible = state; }
			
	
	};

}
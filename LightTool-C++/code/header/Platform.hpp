/**
 * @file Platform.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-31
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once
#include "Model.hpp"
#include "RigidBody.hpp"
#include "Joints.hpp"
#include <vector>

namespace render
{
	class Physics_World;

	/**
	 * @brief Platform class
	 * 
	 */
	class Platform
	{
		/**
		 * @brief platform body
		 * 
		 */
		RigidBody* base_rigidbody;

		/**
		 * @brief Trigger body
		 * 
		 */
		RigidBody* trigger;

		/**
		 * @brief Slider Joint
		 * 
		 */
		SliderJoint* slider;


	public:

		/**
		 * @brief Construct a new Platform object
		 * 
		 * @param name 
		 * @param position 
		 * @param size 
		 * @param floor_base 
		 * @param world 
		 */
		Platform(std::string name, btVector3 position, btVector3 size, RigidBody* floor_base, Scene* world);

		/**
		 * @brief Start to move
		 * 
		 * @param work 
		 */
		void work(bool work);
		
		/**
		 * @brief Update function
		 * 
		 */
		void update();

		/**
		 * @brief Get the trigger
		 * 
		 * @return RigidBody* 
		 */
		RigidBody* get_trigger() { return trigger; }


	};


}
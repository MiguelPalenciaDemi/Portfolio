/**
 * @file Door.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-31
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once
#include "Joints.hpp"
#include "Scene.hpp"



namespace render
{

	/**
	 * @brief Door claas
	 * 
	 */
	class Door
	{
		HingeJoint* joint;
		RigidBody* base_rigidbody;

	public:
		Door(std::string name, btVector3 position, btVector3 size,RigidBody* other_body, Scene* world);
		void open();
		RigidBody* get_rigid_body();
		
		
	
	
	
	};


}
/**
 * @file Catapult.hpp
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
#include "Point_Light.hpp"
#include <vector>

namespace render
{
	/**
	 * @brief Catapult class
	 * 
	 */
	__declspec(align(16)) class Catapult
	{
		/**
		 * @brief Chasis rigidbody
		 * 
		 */
		RigidBody* base_rigidbody;

		/**
		 * @brief All the wheels
		 * 
		 */
		std::vector<HingeJoint*> wheels;

		/**
		 * @brief Right wheels
		 * 
		 */
		std::vector<HingeJoint*> wheels_right;

		/**
		 * @brief Left wheels
		 * 
		 */
		std::vector<HingeJoint*> wheels_left;

		/**
		 * @brief All the rigidbodies
		 * 
		 */
		std::vector<RigidBody*> rigidBodies;

		/**
		 * @brief arm joint. Make it fire
		 * 
		 */
		HingeJoint* arm;

		/**
		 * @brief basket base box
		 * 
		 */
		RigidBody* box_base;

		/**
		 * @brief catapult trigger
		 * 
		 */
		RigidBody* trigger;

		/**
		 * @brief Is fired?
		 * 
		 */
		bool used;



	public: 
		/**
		 * @brief Construct a new Catapult object
		 * 
		 * @param name 
		 * @param position 
		 * @param size 
		 * @param world 
		 */
		Catapult(std::string name, btVector3 position,btVector3 size, Scene* world);

		/**
		 * @brief Create a chasis
		 * 
		 * @param name 
		 * @param position 
		 * @param world 
		 * @return RigidBody* 
		 */
		RigidBody* create_base(std::string name, btVector3 position, Scene * world);

		/**
		 * @brief Create a basket piece
		 * 
		 * @param name 
		 * @param path 
		 * @param size 
		 * @param position 
		 * @param position1_joint 
		 * @param position2_joint 
		 * @param other 
		 * @param world 
		 * @return RigidBody* 
		 */
		RigidBody* create_platform(std::string name, std::string path, btVector3 size, btVector3 position, btVector3 position1_joint, btVector3 position2_joint, RigidBody * other, Scene * world);

		/**
		 * @brief Create a wheel object
		 * 
		 * @param name 
		 * @param position 
		 * @param position_joint 
		 * @param base 
		 * @param world 
		 * @return HingeJoint* 
		 */
		HingeJoint* create_wheel(std::string name, btVector3 position, btVector3 position_joint, RigidBody* base, Scene * world);

		/**
		 * @brief Move forward
		 * 
		 */
		void move_forward();

		/**
		 * @brief Move backward
		 * 
		 */
		void move_backward();

		/**
		 * @brief Move left
		 * 
		 */
		void move_left();

		/**
		 * @brief Move right
		 * 
		 */
		void move_right();

		/**
		 * @brief Stop catapult
		 * 
		 */
		void stop();

		/**
		 * @brief update catapult
		 * 
		 */
		void update();

		/**
		 * @brief Fire or Reload 
		 * 
		 */
		void fire();

		/**
		 * @brief Get the trigger body
		 * 
		 * @return RigidBody* 
		 */
		RigidBody* get_trigger() { return trigger; }

		/**
		 * @brief Get the chasis body
		 * 
		 * @return RigidBody* 
		 */
		RigidBody* get_base() { return base_rigidbody; }

		/**
		 * @brief Get the arm body
		 * 
		 * @return RigidBody* 
		 */
		RigidBody* get_arm() { return arm->get_body_2(); }

		/**
		 * @brief Get the position basket
		 * 
		 * @return btVector3 
		 */
		btVector3 get_position_box() 
		{
			glm::mat4 mat4 =  box_base->update_OpenGL_transform();
			return btVector3{mat4[3].x,mat4[3].y, mat4[3].z};
		}
		

		void* operator new(size_t i)
		{
			return _mm_malloc(i, 16);
		}

		void operator delete(void* p)
		{
			_mm_free(p);
		}

	
	};


}
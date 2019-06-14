/**
 * @file RigidBody.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-31
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once 
#include <btBulletDynamicsCommon.h>
#include <memory>
#include "Shape.hpp"
#include "Physic_World.hpp"
#include "OpenGL.hpp"
#include <iostream>



namespace render
{

	/**
	 * @brief Rigibody class
	 * 
	 */
	__declspec(align(16)) class RigidBody
	{

	public:

		/**
		 * @brief Type
		 * 
		 */
		enum RigidBody_Type
		{
			STATIC,
			DYNAMIC
		};

	private:

		/**
		 * @brief physic transform. This transform is who locate the object
		 * 
		 */
		btTransform physic_transform;

		/**
		 * @brief MotionState
		 * 
		 */
		std::shared_ptr<btDefaultMotionState> state;

		/**
		 * @brief Rigidbody
		 * 
		 */
		std::shared_ptr<btRigidBody> rigid_body;

		/**
		 * @brief Shape of body
		 * 
		 */
		Shape shape;
		
	public: 

		/**
		 * @brief Construct a new Rigid Body object
		 * 
		 * @param type 
		 * @param world 
		 * @param _shape 
		 * @param pos 
		 * @param mass 
		 * @param inertia 
		 * @param trigger 
		 */
		RigidBody(RigidBody_Type type, Physics_World* world, Shape* _shape, btVector3 pos, btScalar mass, btVector3 inertia, bool trigger);

		/**
		 * @brief Construct a new Rigid Body object
		 * 
		 * @param type 
		 * @param world 
		 * @param pos 
		 * @param radius 
		 * @param mass 
		 * @param inertia 
		 * @param trigger 
		 */
		RigidBody(RigidBody_Type type, Physics_World * world, btVector3 pos, btScalar radius, btScalar mass, btVector3 inertia, bool trigger);

		/**
		 * @brief Construct a new Rigid Body object
		 * 
		 * @param type 
		 * @param world 
		 * @param pos 
		 * @param width 
		 * @param length 
		 * @param height 
		 * @param mass 
		 * @param inertia 
		 * @param trigger 
		 */
		RigidBody(RigidBody_Type type, Physics_World * world, btVector3 pos, btScalar width,btScalar length, btScalar height, btScalar mass, btVector3 inertia, bool trigger);

		/**
		 * @brief Create a rigid body object
		 * 
		 * @param type 
		 * @param world 
		 * @param pos 
		 * @param trigger 
		 */
		void create_rigid_body(RigidBody_Type type, Physics_World * world, btVector3 pos, bool trigger);
		
		/**
		 * @brief Set the position object
		 * 
		 * @param position 
		 */
		void set_position(btVector3 position)
		{ 			 
			physic_transform.setOrigin(position);
			rigid_body->setWorldTransform(physic_transform);
			state->setWorldTransform(physic_transform);
			
		}

		/**
		 * @brief Set the rotation object
		 * 
		 * @param rotation 
		 */
		void set_rotation(btQuaternion rotation) { physic_transform.setRotation(rotation); }

		/**
		 * @brief 
		 * 
		 * @return glm::mat4 
		 */
		glm::mat4 update_OpenGL_transform()
		{
			rigid_body->getMotionState()->getWorldTransform(physic_transform);

			glm::mat4 graphic_transform;
			physic_transform.getOpenGLMatrix(glm::value_ptr(graphic_transform)); 
			
			return graphic_transform;
		
		}

		/**
		 * @brief Get the state object
		 * 
		 * @return std::shared_ptr<btDefaultMotionState> 
		 */
		std::shared_ptr<btDefaultMotionState> get_state() { return state; }

		/**
		 * @brief Get the rigid body object
		 * 
		 * @return std::shared_ptr<btRigidBody> 
		 */
		std::shared_ptr<btRigidBody> get_rigid_body() { return rigid_body; }

		/**
		 * @brief Get the shape object
		 * 
		 * @return Shape* 
		 */
		Shape* get_shape() { return &shape; }

		/**
		 * @brief Get the position object
		 * 
		 * @return btVector3 
		 */
		btVector3 get_position() { return physic_transform.getOrigin(); }

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


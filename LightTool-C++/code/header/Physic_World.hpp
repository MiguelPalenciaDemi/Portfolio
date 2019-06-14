/**
 * @file Physic_World.hpp
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
#include <vector>
#include <memory>


namespace render
{
	class RigidBody;

	/**
	 * @brief Physic World class
	 * 
	 */
	class Physics_World
	{

		//Create Physics world
		// Collision configuration contains default setup for memory, collision setup.
		btDefaultCollisionConfiguration collisionConfiguration;

		// Use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded).

		btCollisionDispatcher collisionDispatcher;

		// btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		btDbvtBroadphase overlappingPairCache;

		// The default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded).
		btSequentialImpulseConstraintSolver constraintSolver;

		/**
		 * @brief Physic World 
		 * 
		 */
		btDiscreteDynamicsWorld physic_world;
		
		/**
		 * @brief All the RigidBodies
		 * 
		 */
		std::vector<std::shared_ptr<btRigidBody>> rigidbodies;

		/**
		 * @brief All the MotionStates
		 * 
		 */
		std::vector<std::shared_ptr<btDefaultMotionState>> motionState;

		/**
		 * @brief All the collisionShapes
		 * 
		 */
		std::vector<std::shared_ptr<btCollisionShape>> collisionShapes;

		

	public: 

		/**
		 * @brief Construct a new Physics_World object
		 * 
		 */
		Physics_World() :collisionDispatcher(&collisionConfiguration), physic_world(&collisionDispatcher, &overlappingPairCache, &constraintSolver, &collisionConfiguration){ physic_world.setGravity({ 0,-10,0 }); }
		
		/**
		 * @brief Update function
		 * 
		 * @param time 
		 */
		void update(float time);
		

		/**
		 * @brief Get the physic world
		 * 
		 * @return btDiscreteDynamicsWorld* 
		 */
		btDiscreteDynamicsWorld* get_physic_world() { return &physic_world; }

		/**
		 * @brief Add RigidBody to the world
		 * 
		 * @param rigidbody 
		 */
		void add_rigid_body(RigidBody* rigidbody);
	
	};


}
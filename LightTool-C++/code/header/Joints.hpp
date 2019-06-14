/**
 * @file Joints.hpp
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
#include "RigidBody.hpp"


namespace render 
{
	/**
	 * @brief Joint class
	 * 
	 */
	class Joint
	{
	protected:

		/**
		 * @brief body 1
		 * 
		 */
		RigidBody * body1;

		/**
		 * @brief body 2
		 * 
		 */
		RigidBody* body2;

	public:

		/**
		 * @brief Construct a new Joint object
		 * 
		 * @param b1 
		 * @param b2 
		 */
		Joint(RigidBody* b1, RigidBody* b2): body1(b1), body2(b2) {};

		/**
		 * @brief Get the body 1 object
		 * 
		 * @return RigidBody* 
		 */
		RigidBody* get_body_1(){ return body1; }

		/**
		 * @brief Get the body 2 object
		 * 
		 * @return RigidBody* 
		 */
		RigidBody* get_body_2(){ return body2; }

	};

	/**
	 * @brief Hinge joint
	 * 
	 */
	class HingeJoint:public Joint
	{
		/**
		 * @brief joint
		 * 
		 */
		btHingeConstraint* joint;

	public:

		/**
		 * @brief Construct a new Hinge Joint object
		 * 
		 * @param b1 
		 * @param b2 
		 * @param pos1 
		 * @param pos2 
		 * @param world 
		 */
		HingeJoint(RigidBody* b1, RigidBody* b2, btVector3 pos1, btVector3 pos2, btDiscreteDynamicsWorld* world) ;
		
		/**
		 * @brief Destroy the Hinge Joint object
		 * 
		 */
		~HingeJoint()
		{
		
			joint = nullptr;
		}

		/**
		 * @brief Get the joint object
		 * 
		 * @return btHingeConstraint* 
		 */
		btHingeConstraint* get_joint() { return joint; }
		
	
	};

	/**
	 * @brief Slider Joint class
	 * 
	 */
	class SliderJoint :public Joint
	{
		/**
		 * @brief joint
		 * 
		 */
		btSliderConstraint* joint;

	public:

		/**
		 * @brief Construct a new Slider Joint object
		 * 
		 * @param b1 
		 * @param b2 
		 * @param pos1 
		 * @param pos2 
		 * @param distance 
		 * @param world 
		 */
		SliderJoint(RigidBody * b1, RigidBody * b2, btVector3 pos1, btVector3 pos2, btScalar distance, btDiscreteDynamicsWorld * world);

		/**
		 * @brief Destroy the Slider Joint object
		 * 
		 */
		~SliderJoint()
		{
			joint = nullptr;
		}

		/**
		 * @brief Get the joint object
		 * 
		 * @return btSliderConstraint* 
		 */
		btSliderConstraint* get_joint() { return joint; }


	};


}
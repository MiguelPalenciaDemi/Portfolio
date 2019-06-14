//Code by Miguel Palencia May2019

#pragma once
#include "..\header\Physic_World.hpp"
#include "..\header\RigidBody.hpp"





namespace render
{



	void Physics_World::update(float time)
	{
		physic_world.stepSimulation(time);
	}

	void Physics_World::add_rigid_body(RigidBody * rigidbody)
	{
		physic_world.addRigidBody(rigidbody->get_rigid_body().get());

		rigidbodies.push_back(rigidbody->get_rigid_body());
		motionState.push_back(rigidbody->get_state());
		collisionShapes.push_back(rigidbody->get_shape()->get_shape());

	}

}
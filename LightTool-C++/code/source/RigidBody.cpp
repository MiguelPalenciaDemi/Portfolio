//Code by Miguel Palencia May2019
#pragma once
#include "..\header\RigidBody.hpp"
#include "..\header\Physic_World.hpp"




namespace render
{


	RigidBody::RigidBody(RigidBody_Type type, Physics_World * world, Shape * _shape, btVector3 pos, btScalar mass, btVector3 inertia, bool trigger = false):shape(*_shape)
	{
		create_rigid_body(type, world, pos, trigger);
	}
	RigidBody::RigidBody(RigidBody_Type type, Physics_World * world, btVector3 pos, btScalar radius, btScalar mass, btVector3 inertia, bool trigger):shape(radius,mass,inertia)
	{
		create_rigid_body(type, world, pos, trigger);
	}
	RigidBody::RigidBody(RigidBody_Type type, Physics_World * world, btVector3 pos, btScalar width, btScalar length, btScalar height, btScalar mass, btVector3 inertia, bool trigger):shape(width,length,height,mass,inertia)
	{
		create_rigid_body(type, world, pos, trigger);
	}
	void RigidBody::create_rigid_body(RigidBody_Type type, Physics_World * world, btVector3 pos, bool trigger)
	{

		physic_transform.setIdentity();
		physic_transform.setOrigin(pos);

		state.reset(new btDefaultMotionState(physic_transform));

		if (type == RigidBody_Type::DYNAMIC)
		{
			shape.calculate_inertia();

			btRigidBody::btRigidBodyConstructionInfo dynamic_info(this->shape.get_mass(), state.get(), shape.get_shape().get(), this->shape.get_inetia());

			rigid_body.reset(new btRigidBody(dynamic_info));

		}
		else
		{
			btRigidBody::btRigidBodyConstructionInfo static_info(0, state.get(), shape.get_shape().get());
			rigid_body.reset(new btRigidBody(static_info));

		}

		if (trigger)
			rigid_body->setCollisionFlags(rigid_body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);

		rigid_body->setActivationState(DISABLE_DEACTIVATION);
		world->add_rigid_body(this);
	}
}





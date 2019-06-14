//Code by Miguel Palencia May2019
#pragma once
#include "..\header\RigidBody.hpp"
#include "..\header\Joints.hpp"


namespace render
{
	HingeJoint::HingeJoint(RigidBody * b1, RigidBody * b2, btVector3 pos1, btVector3 pos2, btDiscreteDynamicsWorld * world) :Joint(b1, b2)
	{

		joint = new btHingeConstraint(*body1->get_rigid_body(), *body2->get_rigid_body(), pos1, pos2, { 0,0,1 }, { 0,0,1 });
		joint->enableAngularMotor(true, 0, 100.f);
		world->addConstraint(joint, true);

	}
	SliderJoint::SliderJoint(RigidBody * b1, RigidBody * b2, btVector3 pos1, btVector3 pos2,btScalar distance, btDiscreteDynamicsWorld * world) :Joint(b1, b2)
	{
		btTransform t1 = btTransform::getIdentity();
		t1.setOrigin(pos1);
		btTransform t2 = btTransform::getIdentity();
		t2.setOrigin(pos2);

		joint = new btSliderConstraint(*body1->get_rigid_body(), *body2->get_rigid_body(), t1, t2, true);
		
		joint->setPoweredLinMotor(true);
		joint->setLowerLinLimit(0);
		joint->setUpperLinLimit(distance);

		joint->setTargetLinMotorVelocity(0);
		joint->setMaxLinMotorForce(100);

		world->addConstraint(joint, true);
	}
}
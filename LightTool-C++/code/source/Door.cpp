//Code by Miguel Palencia May2019
#pragma once 
#include "..\header\Catapult.hpp"
#include "..\header\Scene.hpp"
#include "..\header\Model.hpp"
#include "..\header\Joints.hpp"
#include "..\header\RigidBody.hpp"
#include "..\header\Door.hpp"





namespace render
{
	Door::Door(std::string name, btVector3 position, btVector3 size, RigidBody* other_body, Scene* world)
	{//Chasis
		std::shared_ptr<Model> model;
		model.reset(new Model(world, nullptr));


		std::shared_ptr<Mesh> mesh;
		mesh.reset(new Mesh("../../assets/gate.obj"));
		std::shared_ptr<Material> material;
		material.reset(new Material(default_vertex_shader_code, fragment_shader_no_texture_code, { 1,0,0 }, 0, 1));

		model->add_piece("base", mesh, material);

		
		base_rigidbody = new RigidBody(RigidBody::DYNAMIC, world->get_world(), position, 5, 10, 10, 10, { 0,0,0 }, false);
		base_rigidbody->get_rigid_body()->setFriction(5);

		//Make the joint to cab be open
		joint = new HingeJoint(base_rigidbody, other_body, { 0,12,0 }, { 0,0,0 }, world->get_world()->get_physic_world());

		joint->get_joint()->setLimit(-3.14f *0.5f, 0);
		joint->get_joint()->setMotorTargetVelocity(0);
		joint->get_joint()->setMaxMotorImpulse(50);

		model->set_rigid_body(base_rigidbody);

		world->add_model(name, model);

	}
	void Door::open()
	{
		joint->get_joint()->setMotorTargetVelocity(-5);
	}
	RigidBody * Door::get_rigid_body()
	{
		return base_rigidbody;
	}
}
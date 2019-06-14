//Code by Miguel Palencia May2019
#pragma once 
#include "..\header\Platform.hpp"
#include "..\header\Scene.hpp"
#include "..\header\Model.hpp"
#include "..\header\Joints.hpp"
#include "..\header\RigidBody.hpp"


namespace render
{
	Platform::Platform(std::string name, btVector3 position, btVector3 size, RigidBody* floor_base, Scene* world)
	{
		//Create trigger
		trigger = new RigidBody(RigidBody::DYNAMIC, world->get_world(), position, 2, 2, 5, 5, { 0,0,0 }, true);

		std::shared_ptr<Model> model;
		model.reset(new Model(world, nullptr));


		std::shared_ptr<Mesh> mesh;
		mesh.reset(new Mesh("../../assets/platform.obj"));
		std::shared_ptr<Material> material;
		material.reset(new Material(default_vertex_shader_code, fragment_shader_no_texture_code, { 1,0,1 }, 0, 1));

		model->add_piece("base", mesh, material);

		base_rigidbody = new RigidBody(RigidBody::DYNAMIC, world->get_world(), position, size.x(), size.z(), size.y(), 500, { 0,0,0 }, false);
		base_rigidbody->get_rigid_body()->setFriction(50);

		model->set_rigid_body(base_rigidbody);
		slider = new SliderJoint(floor_base, base_rigidbody, { 0,0,0 }, position, 50, world->get_world()->get_physic_world());
		slider->get_joint()->setMaxLinMotorForce(2000);
		world->add_model(name, model);


		



	}

	

	void Platform::work(bool work)
	{
		if(work)
			slider->get_joint()->setTargetLinMotorVelocity(20.f);
		else
			slider->get_joint()->setTargetLinMotorVelocity(-20.f);


	}


	void Platform::update()
	{
		trigger->set_position(base_rigidbody->get_position());
	}


}
//Code by Miguel Palencia May2019
#pragma once 
#include "..\header\Catapult.hpp"
#include "..\header\Scene.hpp"
#include "..\header\Model.hpp"
#include "..\header\Joints.hpp"
#include "..\header\RigidBody.hpp"


namespace render
{
	Catapult::Catapult(std::string name, btVector3 position, btVector3 size, Scene * world) 
	{


		//Create all the pieces
		Shape* shape_trigger = new Shape(size.x(), size.z(), size.y(), 5, { 0,0,0 });
		trigger = new RigidBody(RigidBody::DYNAMIC, world->get_world(), shape_trigger, position, 5, { 0,0,0 }, true);
		
		base_rigidbody = create_base(name + "_chasis", position, world);

		HingeJoint* right_sup = create_wheel(name + "_wheel1", position, {  -0.7f, 0,-0.65f }, base_rigidbody, world);
		wheels.push_back(right_sup);
		wheels_right.push_back(right_sup);
		
		HingeJoint* left_sup = create_wheel(name + "_wheel4", position,{  -0.7f, 0, 0.50f }, base_rigidbody, world);
		wheels.push_back(left_sup);
		wheels_left.push_back(left_sup);


		HingeJoint* right_inf = create_wheel(name + "_wheel3", position, { 0.7f, 0, -0.65f }, base_rigidbody, world);
		wheels.push_back(right_inf);
		wheels_right.push_back(right_inf);


		HingeJoint* left_inf = create_wheel(name + "_wheel2", position, {  0.7f, 0, 0.5f }, base_rigidbody, world);
		wheels.push_back(left_inf);
		wheels_left.push_back(left_inf);


		//Create arm
		std::shared_ptr<Model> arm_model;
		arm_model.reset(new Model(world, nullptr));		

		std::shared_ptr<Mesh> arm_mesh;
		arm_mesh.reset(new Mesh("../../assets/arm-catapult.obj"));
		std::shared_ptr<Material> arm_mat;
		arm_mat.reset(new Material(default_vertex_shader_code, fragment_shader_no_texture_code, { 0,1,0 }, 0, 1));

		arm_model->add_piece("base", arm_mesh, arm_mat);

		RigidBody* arm_rigidbody = new RigidBody(RigidBody::DYNAMIC, world->get_world(), { position.x() + 1.2f,position.y() + 0.25f,position.z() }, 1.f, 0.1f, 0.05f, 5, { 0,0,0 }, false);
		rigidBodies.push_back(arm_rigidbody);

		arm_model->set_rigid_body(arm_rigidbody);

		world->add_model("arm", arm_model);


		//Create Joint. It makes the catapult can fire
		arm = new HingeJoint(base_rigidbody, arm_rigidbody, { 0,0.3f,0 }, { -0.9f,0,0 }, world->get_world()->get_physic_world());
		
		//Deactivate collision with the catapult pieces
		arm_rigidbody->get_rigid_body()->setIgnoreCollisionCheck(base_rigidbody->get_rigid_body().get(), true);
		arm_rigidbody->get_rigid_body()->setIgnoreCollisionCheck(left_inf->get_body_1()->get_rigid_body().get(), true);
		arm_rigidbody->get_rigid_body()->setIgnoreCollisionCheck(left_sup->get_body_1()->get_rigid_body().get(), true);
		arm_rigidbody->get_rigid_body()->setIgnoreCollisionCheck(right_sup->get_body_1()->get_rigid_body().get(), true);
		arm_rigidbody->get_rigid_body()->setIgnoreCollisionCheck(right_inf->get_body_1()->get_rigid_body().get(), true);

		//Set info joint
		arm->get_joint()->setMotorTargetVelocity(0);
		arm->get_joint()->setMaxMotorImpulse(2000);
		arm->get_joint()->setLimit(-3.14f*0.5f,-0.2f);

		//Create basket
		box_base = create_platform("box_base", "../../assets/box-base.obj", { 0.5f, 0.05f, 0.5f }, { position.x() + 1.2f, position.y() + 0.25f, position.z() }, { 1.2f,0,0 }, { 0,0,0 }, arm_rigidbody, world);
		create_platform("box_left", "../../assets/box-left.obj", { 0.05f, 0.2f, 0.05f }, { position.x() + 1.2f, position.y() + 0.25f, position.z()+0.25f }, { 0,0,0.25 }, { 0,0,0 }, box_base, world);
		create_platform("box_right", "../../assets/box-left.obj", { 0.05f, 0.2f, 0.05f }, { position.x() + 1.2f, position.y() + 0.25f, position.z()-0.25f }, { 0,0,-0.25 }, { 0,0,0 }, box_base, world);
		create_platform("box_up", "../../assets/box-up.obj", { 0.05f, 0.2f, 0.05f }, { position.x() + 1.45f, position.y() + 0.25f, position.z() }, { 0.25f,0,0 }, { 0,0,0 }, box_base, world);
		create_platform("box_down", "../../assets/box-up.obj", { 0.05f, 0.2f, 0.05f }, { position.x() + 0.95f, position.y() + 0.25f, position.z() }, { -0.25f,0,0 }, { 0,0,0 }, box_base, world);

		//Set unfired
		used = false;



	}

	RigidBody * Catapult::create_base(std::string name, btVector3 position, Scene * world) 
	{

		//Chasis
		std::shared_ptr<Model> chasis;
		chasis.reset(new Model(world, nullptr));


		std::shared_ptr<Mesh> mesh_ball;
		mesh_ball.reset(new Mesh("../../assets/base-vehicle.obj"));
		std::shared_ptr<Material> mat_ball;
		mat_ball.reset(new Material(default_vertex_shader_code, fragment_shader_no_texture_code, { 1,0,0 }, 0, 1));

		chasis->add_piece("base", mesh_ball, mat_ball);

		RigidBody* base_rigidbody = new RigidBody(RigidBody::DYNAMIC, world->get_world(), position, 1.5f, 0.5f, 0.1f, 20, { 0,0,0 },false);
		rigidBodies.push_back(base_rigidbody);
		chasis->set_rigid_body(base_rigidbody);

		world->add_model(name, chasis);

		return base_rigidbody;

	}

	RigidBody * Catapult::create_platform(std::string name, std::string path, btVector3 size, btVector3 position, btVector3 position1_joint, btVector3 position2_joint, RigidBody * other, Scene * world)
	{
		//Create Model
		std::shared_ptr<Model> model;
		model.reset(new Model(world, nullptr));

		std::shared_ptr<Mesh> mesh;
		mesh.reset(new Mesh(path));
		std::shared_ptr<Material> material;
		material.reset(new Material(default_vertex_shader_code, fragment_shader_no_texture_code, { 0,1,0 }, 0, 1));

		model->add_piece("piece", mesh, material);

		
		RigidBody* rigid_body = new RigidBody(RigidBody::DYNAMIC, world->get_world(), position, size.x(), size.z(), size.y(), 1, { 0,0,0 }, false);
		rigidBodies.push_back(rigid_body);

		model->set_rigid_body(rigid_body);

		world->add_model(name, model);


		//Make the joints between wall box
		HingeJoint* joint = new HingeJoint(other, rigid_body, position1_joint, position2_joint, world->get_world()->get_physic_world());

		//Deactivae collisions with the rest of pieces
		for(auto rb : rigidBodies)
		{		
			rigid_body->get_rigid_body()->setIgnoreCollisionCheck(rb->get_rigid_body().get(), true);
		}
				
		joint->get_joint()->setMotorTargetVelocity(0);
		joint->get_joint()->setLimit(0, 0);

		return rigid_body;
	}

	HingeJoint* Catapult::create_wheel(std::string name, btVector3 position, btVector3 position_joint, RigidBody * base, Scene * world)
	{

		std::shared_ptr<Model> wheel_model;
		wheel_model.reset(new Model(world, nullptr));

		std::shared_ptr<Mesh> wheel_mesh;
		wheel_mesh.reset(new Mesh("../../assets/wheel.obj"));
		std::shared_ptr<Material> wheel_material;
		wheel_material.reset(new Material(default_vertex_shader_code, fragment_shader_no_texture_code, { 1,1,0 }, 0, 1));

		wheel_model->add_piece("rueda", wheel_mesh, wheel_material);

		RigidBody* wheel_rigidbody = new RigidBody(RigidBody::DYNAMIC, world->get_world(), position,0.2f,50, { 0,0,0 }, false);
		base_rigidbody->get_rigid_body()->setFriction(1);
		rigidBodies.push_back(wheel_rigidbody);

		wheel_model->set_rigid_body(wheel_rigidbody);


		HingeJoint* wheel_joint = new HingeJoint(wheel_rigidbody, base, {0,0,0}, position_joint, world->get_world()->get_physic_world());
		world->add_model(name, wheel_model);

		return wheel_joint;

	}

	void Catapult::move_forward()
	{
		for (auto wheel : wheels)
		{
			wheel->get_joint()->setMotorTargetVelocity(20);
		}

	}

	void Catapult::move_backward()
	{
		for (auto wheel : wheels)
		{
			wheel->get_joint()->setMotorTargetVelocity(-20);
		}
	}

	void Catapult::stop()
	{
		for (auto wheel : wheels)
		{
			wheel->get_joint()->setMotorTargetVelocity(0);
		}

	}

	void Catapult::update()
	{
		trigger->set_position(base_rigidbody->get_position());
	}

	void Catapult::fire()
	{
		if(used)
			arm->get_joint()->setMotorTargetVelocity(100);
		else
			arm->get_joint()->setMotorTargetVelocity(-1000);

		used = !used;

	}

	void Catapult::move_left()
	{
		for (auto wheel : wheels_left)
		{
			wheel->get_joint()->setMotorTargetVelocity(-50);
		}

		for (auto wheel : wheels_right)
		{
			wheel->get_joint()->setMotorTargetVelocity(50);
		}

	}

	void Catapult::move_right()
	{

		for (auto wheel : wheels_left)
		{
			wheel->get_joint()->setMotorTargetVelocity(50);
		}

		for (auto wheel : wheels_right)
		{
			wheel->get_joint()->setMotorTargetVelocity(-50);
		}

	}

	
}
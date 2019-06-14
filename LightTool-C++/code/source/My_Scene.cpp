//Code by Miguel Palencia May 2019

#pragma once
#include "../header/My_Scene.hpp"
#include "../header/WindMill.hpp"
#include "../header/Circle.hpp"
#include "../header/Plane.hpp"
#include "../header/Terrain.hpp"
#include "../header/Joints.hpp"
#include "../header/Catapult.hpp"
#include "../header/Platform.hpp"
#include "../header/Door.hpp"
#include <ParserXML.hpp>

namespace render
{

	My_Scene::My_Scene(std::size_t width, std::size_t height) :Scene(width, height)
	{
		

		//Islands
		RigidBody* mid = create_platform("mid", "../../assets/mid-base.obj", { 50,0,0 }, { 25,0.5f,35 }, RigidBody::STATIC);
		RigidBody* top = create_platform("top", "../../assets/top.obj", { 50,20,0 }, { 5,5,25 }, RigidBody::STATIC);
		RigidBody* wall1 = create_platform("wall1", "../../assets/wall.obj", { 50,10,25 }, { 5,10,12.5f }, RigidBody::STATIC);
		RigidBody* wall2 = create_platform("wall2", "../../assets/wall.obj", { 50,10,-25 }, { 5,10,12.5f }, RigidBody::STATIC);
		RigidBody* goal = create_platform("goal", "../../assets/wall.obj", { 100,10,0 }, { 5,10,12.5f }, RigidBody::DYNAMIC);
		RigidBody* r1 =  create_platform("start", "../../assets/base-scene-start.obj", { 0,0,0 }, { 12,0.5f,25 }, RigidBody::STATIC);
		RigidBody* end =  create_platform("end", "../../assets/base-scene-start.obj", { 100,0,0 }, { 12,0.5f,25 }, RigidBody::STATIC);



		//Set camera start position
		active_camera->set_position(-20, 20, 0);

	}

	void My_Scene::update(float time)
	{
		//Updtae all models
		Scene::update(time);
		time_variable += time;//For some shaders


	}


	

	RigidBody * My_Scene::create_platform(std::string name, std::string path, btVector3 position, btVector3 size, RigidBody::RigidBody_Type type)
	{
		//Chasis
		std::shared_ptr<Model> model;
		model.reset(new Model(this, nullptr));


		std::shared_ptr<Mesh> mesh;
		mesh.reset(new Mesh(path));
		std::shared_ptr<Material> material;
		material.reset(new Material(default_vertex_shader_code, fragment_shader_no_texture_code, { 1,1,1 }, 0, 1));
		materials.push_back(material);

		model->add_piece("base", mesh, material);

		RigidBody* base_rigidbody = new RigidBody(type, &physic_world, position, size.x(), size.z(), size.y(), 1, { 0,0,0 }, false);
		base_rigidbody->get_rigid_body()->setFriction(5);
		model->set_rigid_body(base_rigidbody);

		add_model(name, model);

		return base_rigidbody;
	}


	void My_Scene::check_collision()
	{
		int manifold_count = physic_world.get_physic_world()->getDispatcher()->getNumManifolds();
		for (int i = 0; i < manifold_count; i++)
		{
			btPersistentManifold * manifold =
				physic_world.get_physic_world()->getDispatcher()->getManifoldByIndexInternal(i);
			btCollisionObject * object_a = (btCollisionObject *)(manifold->getBody0());
			btCollisionObject * object_b = (btCollisionObject *)(manifold->getBody1());
			int numContacts = manifold->getNumContacts();
			for (int j = 0; j < numContacts; j++)
			{
				btManifoldPoint & point = manifold->getContactPoint(j);
				if (point.getDistance() < 0.f)
				{
				}
			}
		}


	}

	

	void My_Scene::create_rock()
	{
		std::shared_ptr<Model> model;
		model.reset(new Model(this, nullptr));

		std::shared_ptr<Mesh> mesh;
		mesh.reset(new Mesh("../../assets/rock.obj"));
		std::shared_ptr<Material> material;
		material.reset(new Material(default_vertex_shader_code, fragment_shader_no_texture_code, { 0.2f,0.3f,0.2f }, 0, 1));
		materials.push_back(material);


		model->add_piece("rueda", mesh, material);
		
		btVector3 pos = {0,0,0};		
		RigidBody* rg = new RigidBody(RigidBody::DYNAMIC, &physic_world,  { pos.x(),pos.y()+2,pos.z() }, 0.1f, 1, { 0,0,0 }, false);
		
		model->set_rigid_body(rg);


		models["rock"] = model;

	}

	

}


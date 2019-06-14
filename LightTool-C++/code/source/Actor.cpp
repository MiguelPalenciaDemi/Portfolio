//Code by Miguel Palencia May2019
#pragma once 
#include "../header/Actor.hpp"
#include "../header/Scene.hpp"
#include "../header/Physic_World.hpp"
#include "../header/RigidBody.hpp"
#include <btBulletDynamicsCommon.h>

namespace render
{




	Actor::Actor(Scene * _scene, std::shared_ptr<Actor> _parent)
	{
		own_scene = _scene;
		rigid_body = nullptr;

		if (_parent != nullptr)
			set_parent(_parent);

		visible = true;
	}
	void Actor::set_position(glm::vec3 new_position)
	{
		rigid_body->set_position({ new_position.x,new_position.y,new_position.z });
		//local_transform.set_position(new_position.x, new_position.y, new_position.z);
	}
	void Actor::update()
	{
		
		local_transform.set_transformation(rigid_body->update_OpenGL_transform());//Update transform		
		local_transform.update();//Update based on the graph


	}

}
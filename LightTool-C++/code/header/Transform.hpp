/**
 * @file Transform.hpp
 * @author Miguel Palencia de Miguel
 * @brief 
 * @version 0.1
 * @date 2019-03-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once
#include <Vector.hpp>
#include <Scaling.hpp>
#include <Rotation.hpp>
#include <Projection.hpp>
#include <Translation.hpp>
#include "OpenGL.hpp"



using namespace toolkit;
using namespace glm;

namespace render
{
	

	/**
	 * @brief Transform class
	 * 
	 */
	class Transform
	{
		/**
		 * @brief local_tranform
		 * 
		 */
		mat4 local_transform;

		/**
		 * @brief World transform
		 * 
		 */
		mat4 transform;

		/**
		 * @brief Position
		 * 
		 */
		vec3 translation = { 0,0,0 };

		/**
		 * @brief Scale
		 * 
		 */
		vec3 scale = { 1,1,1 };

		/**
		 * @brief rotation
		 * 
		 */
		vec3 rotation;

		/**
		 * @brief parent tranform
		 * 
		 */
		Transform* parent;

		/**
		 * @brief Indicate if it's updated 
		 * 
		 */
		bool updated = false;
		
		
	public:

		/**
		 * @brief Construct a new Transform object
		 * 
		 */
		Transform() { parent = nullptr; };

		/**
		 * @brief translate model
		 * 
		 * @param x 
		 * @param y 
		 * @param z 
		 */
		void translate_model(float x, float y, float z) { translation += vec3(x, y, z); local_transform = translate(local_transform, vec3(x, y, z)); update_position(); }

		/**
		 * @brief translate model
		 * 
		 * @param displacement 
		 */
		void translate_model(vec3 displacement)			{ translation += displacement;	local_transform = translate(local_transform, vec3(displacement.x, displacement.y, displacement.z)); update_position(); }

		/**
		 * @brief rotate around x axis
		 * 
		 * @param angle 
		 */
		void rotate_around_x(float angle) { rotation.x += angle; local_transform = rotate(local_transform, angle, vec3(1.f, 0.f, 0.f)); update_position();}

		/**
		 * @brief rotate around y axis
		 * 
		 * @param angle 
		 */
		void rotate_around_y(float angle) { rotation.y += angle; local_transform = rotate(local_transform, angle, vec3( 0.f, 1.f, 0.f));update_position();}

		/**
		 * @brief rotate around z axis
		 * 
		 * @param angle 
		 */
		void rotate_around_z(float angle) { rotation.z += angle; local_transform = rotate(local_transform, angle, vec3( 0.f, 0.f, 1.f)); update_position();}
		
		/**
		 * @brief scale model
		 * 
		 * @param _scale 
		 */
		void scale_model(vec3 _scale)	  { scale += scale; local_transform = glm::scale(local_transform,_scale); update_position();}


		/**
		 * @brief Set the position object
		 * 
		 * @param x 
		 * @param y 
		 * @param z 
		 */
		void set_position(float x, float y, float z);
		
		/**
		 * @brief Get the transform object
		 * 
		 * @return mat4 
		 */
		mat4 get_transform() { return transform; }
		void set_transformation(glm::mat4 new_transformation) { local_transform = new_transformation; }

		/**
		 * @brief Get the local transform object
		 * 
		 * @return mat4 
		 */
		mat4 get_local_transform() { return local_transform; }

		/**
		 * @brief Get the position 
		 * 
		 * @return vec3 
		 */
		vec3 get_position() { return translation; }

		/**
		 * @brief Get the rotation 
		 * 
		 * @return vec3 
		 */
		vec3 get_rotation() { return rotation; }

		/**
		 * @brief Get the scale 
		 * 
		 * @return vec3 
		 */
		vec3 get_scale() { return scale; }
		
		/**
		 * @brief Get the parent transform
		 * 
		 * @return Transform* 
		 */
		Transform* get_parent(){return parent;};


		/**
		 * @brief Set a new parent
		 * 
		 * @param new_parent 
		 */
		void set_parent(Transform* new_parent) { parent = new_parent; update_position();}

		/**
		 * @brief Update  function
		 * 
		 */
		void update() { updated = false; update_position(); };

		/**
		 * @brief Update transform and local tranform.
		 * 
		 * @return mat4 
		 */
		mat4 update_position();

		
	
	};
	

		
		


		


		


	



}


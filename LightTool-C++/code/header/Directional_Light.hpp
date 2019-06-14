/**
 * @file Directional_Light.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once
#include "OpenGL.hpp"
#include "Light.hpp"


namespace render
{
	/**
	 * @brief Direction Light class
	 * 
	 */
	class Directional_Light: public Light
	{
		/**
		 * @brief direction of the light
		 * 
		 */
		glm::vec3 direction;

	public:

		/**
		 * @brief Construct a new Directional_Light object
		 * 
		 * @param _ambient 
		 * @param _intensity 
		 * @param _specular 
		 * @param _color 
		 * @param _position 
		 * @param _direction 
		 */
		Directional_Light(float _ambient, float _intensity, float _specular, glm::vec3 _color, glm::vec3 _position, glm::vec3 _direction) :Light(_ambient, _intensity, _specular, _color, _position),direction(_direction) {};

		/**
		 * @brief Get the direction of light
		 * 
		 * @return glm::vec3 
		 */
		glm::vec3 get_direction() { return direction; }
	};


}
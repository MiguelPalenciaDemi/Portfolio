
/**
 * @file Light.hpp
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


namespace render
{
	/**
	 * @brief Light class
	 * 
	 */
	class Light
	{

	protected:

		/**
		 * @brief ambient light
		 * 
		 */
		float ambient;
		/**
		 * @brief intensity light
		 * 
		 */
		float intensity;
		/**
		 * @brief specular amount of the light
		 * 
		 */
		float specular;

		/**
		 * @brief color of the light
		 * 
		 */
		glm::vec3 color;

		/**
		 * @brief position of the light
		 * 
		 */
		glm::vec3 position;

		/**
		 * @brief visible
		 *
		 */
		int enable;

	public:

		/**
		 * @brief Construct a new Light object
		 * 
		 * @param _ambient 
		 * @param _intesity 
		 * @param _specular 
		 * @param _color 
		 * @param _position 
		 */
		Light(float _ambient,float _intesity,float _specular,glm::vec3 _color , glm::vec3 _position)
		{
			ambient	  = _ambient;
			intensity = _intesity;
			specular  = _specular;
			color	  = _color;			
			position  = _position;
			enable	  = 1;
		
		}

		/**
		 * @brief Destroy the Light object
		 * 
		 */
		~Light()
		{
			ambient = 0;
		}

		/**
		 * @brief Get the ambient light
		 * 
		 * @return float 
		 */
		float get_ambient() { return ambient; }

		/**
		 * @brief Get the specular light
		 * 
		 * @return float 
		 */
		float get_specular() { return specular; }

		/**
		 * @brief Get the intensity light
		 * 
		 * @return float 
		 */
		float get_intensity() { return intensity; }


		void  set_intensity(float new_intensity) { intensity = new_intensity; }

		/**
		 * @brief Get the color light
		 * 
		 * @return glm::vec3 
		 */
		glm::vec3 get_color() { return color; }

		/**
		 * @brief Get the position light
		 * 
		 * @return glm::vec3 
		 */
		glm::vec3 get_position() { return position; }

		/**
		 * @brief Turn off the light
		 * 
		 */
		virtual void turn_off() { enable = 0; ambient = 0; intensity = 0; }
		
		/**
		 * @brief Set the position object
		 * 
		 * @param pos 
		 */
		void set_position(glm::vec3 pos) { position = pos; };

		/**
		 * @brief Get the enable value
		 * 
		 * @return int 
		 */
		int get_enable() { return enable; }
	
	};


}
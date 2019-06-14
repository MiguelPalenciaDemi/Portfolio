/**
 * @file Point_Light.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once
#include "Light.hpp"

namespace render
{

	/**
	 * @brief Point Light class
	 * 
	 */
	class Point_Light:public Light
	{
		/**
		 * @brief constant value
		 * 
		 */
		float constant;
		
		/**
		 * @brief Linear attenuation
		 * 
		 */
		float linear;

		/**
		 * @brief Quadratic attenuation
		 * 
		 */
		float quadratic;

		/**
		* @brief Range attenuation
		*
		*/
		float range;

		

	public:

		Point_Light() :Light(0, 0, 0, { 0,0,0 }, { 0,0,0 }) {};
		/**
		 * @brief Construct a new Point_Light object
		 * 
		 * @param _ambient 
		 * @param _intensity 
		 * @param _specular 
		 * @param _color 
		 * @param _position 
		 * @param _constant 
		 * @param _linear 
		 * @param _quadratic 
		 */
		Point_Light(float _ambient, float _intensity, float _specular, glm::vec3 _color, glm::vec3 _position, float _constant, float _linear, float _quadratic ) :Light(_ambient, _intensity, _specular, _color, _position), constant(_constant),linear(_linear),quadratic(_quadratic) {};
		
		/**
		* @brief Construct a new Point_Light object
		*
		* @param _ambient
		* @param _intensity
		* @param _specular
		* @param _color
		* @param _position
		* @param _range		
		*/
		Point_Light(float _ambient, float _intensity, float _specular, glm::vec3 _color, glm::vec3 _position, float _range) :Light(_ambient, _intensity, _specular, _color, _position), range(_range) { set_attenuation_values(); };

		/**
		 * @brief Get the constant value
		 * 
		 * @return float 
		 */
		float get_constant() { return constant; }

		/**
		 * @brief Get the linear value
		 * 
		 * @return float 
		 */
		float get_linear() { return linear; }

		/**
		 * @brief Get the quadratic value
		 * 
		 * @return float 
		 */
		float get_quadratic() { return quadratic; }

		/**
		* @brief Get the range value
		*
		* @return float
		*/
		float get_range() { return range; }

		/**
		* @brief Set the attenuation values
		*
		*/
		void set_attenuation_values()
		{
			constant = 1;
			if(range<7)
			{
				linear = 0.7f;
				quadratic = 1.8f;
			}
			else if (range<13)
			{
				linear = 0.35f;
				quadratic = 0.44f;
			}
			else if (range<20)
			{
				linear = 0.22;
				quadratic = 0.20f;
			}
			else if (range<32)
			{
				linear = 0.14f;
				quadratic = 0.07f;
			}
			else if (range<50)
			{
				linear = 0.09f;
				quadratic = 0.032f;
			}
			else if (range<65)
			{
				linear = 0.07f;
				quadratic = 0.017f;
			}
			else if (range<100)
			{
				linear = 0.045f;
				quadratic = 0.0075f;
			}
			else if (range<160)
			{
				linear = 0.027f;
				quadratic = 0.0028f;
			}
			else if (range<200)
			{
				linear = 0.022f;
				quadratic = 0.0019f;
			}
			else
			{
				linear = 0.007f;
				quadratic = 0.0007f;
			}

		
		}
		
	
	};

}
/**
 * @file Circle.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-31
 * 
 * @copyright Copyright (c) 2019
 * 
 */


#pragma once
#include <cmath>
#include <memory>
#include "Mesh.hpp"
#include <list>
#include <vector> 
#include "OpenGL.hpp"
#include "Vertex_Buffer.hpp"
#include "Scene.hpp"
#include "Model.hpp"
#include "Plane.hpp"



using namespace toolkit;

namespace render
{

	/**
	 * @brief  Circle class
	 * 
	 */
	class Circle :public Model
	{
		
	public:
	
		/**
		 * @brief Construct a new Circle object
		 * 
		 * @param scene 
		 * @param parent 
		 * @param specular 
		 * @param color 
		 */
		Circle(Scene* scene, std::shared_ptr<Actor> parent,float specular = 0.5f, glm::vec3 color = { 0.35,0.4,0.6 }) :Model(scene, parent)
		{

			std::shared_ptr<Material> material;
			material.reset(new Material(vertex_shader_water_code, fragment_shader_water_circle_code,color, specular,0.5f));

			std::shared_ptr<Mesh> mesh;
			mesh.reset(new Mesh("../../assets/plane.obj"));

			material->add_uniform_vector3("color", color);
			material->add_uniform_float("opacity", 0.5f);
			material->add_uniform_float("speed", 5);
			material->add_uniform_float("height", 3);
			material->add_uniform_float("distance", 15);
			material->add_uniform_float("radius", 100);
			material->add_uniform_float("time", 0);
			add_piece("circle", mesh, material);	
		
		};
		

	};

}
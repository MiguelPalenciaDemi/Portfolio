/**
 * @file Plane.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
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
#include <Point.hpp>
#include <Vector.hpp>
#include "Vertex_Buffer.hpp"


using namespace toolkit;

namespace render
{

	/**
	 * @brief Plane class
	 * 
	 */
	class Plane:public Mesh
	{
		/**
		 * @brief size of coordinates
		 * 
		 */
		int coordinates_size;

		/**
		 * @brief size of normals
		 * 
		 */
		int normals_size;

		/**
		 * @brief collection of coordinates
		 * 
		 */
		std::vector< Point3f  > coordinates;

		/**
		 * @brief collection of normals
		 * 
		 */
		std::vector<toolkit::Vector3f > normals;

		/**
		 * @brief collection of teexture coordinates
		 * 
		 */
		std::vector< Point2f  > texture_uvs;
		

	public:

	/**
	 * @brief Construct a new Plane object
	 * 
	 * @param width 
	 * @param length 
	 * @param tiles_w 
	 * @param tiles_l 
	 */
		Plane(float width, float length, int tiles_w, int tiles_l)
		{
			int number_of_vertices = (tiles_w + 1) * (tiles_l + 1);		
			
			
			float  left_x = -width / 2.f;
			float  right_x = -left_x;
			float  x_step = width / float(tiles_w);
			float  u_step = 1.f / float(tiles_w);

			float  far_z = -length / 2.f;
			float  near_z = -far_z;
			float  z_step = length / float(tiles_l);
			float  v_step = 1.f / float(tiles_l);

			//Fill the containers
			for (float z = far_z; z < near_z; z += z_step)
			{
				for (float x = left_x; x < right_x; x += x_step)
				{
					coordinates.push_back(Point3f({ x,0.f,z }));					
					normals.push_back(toolkit::Vector3f({ 0.f, 1.f, 0.f }));					

					coordinates.push_back(Point3f({ x + x_step,0.f,z }));					
					normals.push_back(toolkit::Vector3f({ 0.f, 1.f, 0.f }));

					coordinates.push_back(Point3f({ x,0.f,z + z_step }));				
					normals.push_back(toolkit::Vector3f({ 0.f, 1.f, 0.f }));

					coordinates.push_back(Point3f({ x + x_step,0.f,z }));
					normals.push_back(toolkit::Vector3f({ 0.f, 1.f, 0.f }));

					coordinates.push_back(Point3f({ x + x_step,0.f,z + z_step }));
					normals.push_back(toolkit::Vector3f({ 0.f, 1.f, 0.f }));
					
					coordinates.push_back(Point3f({ x,0.f,z + z_step }));
					normals.push_back(toolkit::Vector3f({ 0.f, 1.f, 0.f }));

					
			
				}
			}
			//Initialize the VAO
			vao.reset(new Vertex_Array());
			vao->bind();

			//Calculate and fill the coord buffer
			coordinates_size = coordinates.size();
			coordinates_vbo.reset(new Vertex_Buffer(coordinates.size() * sizeof(Point3f),3, coordinates.data(), GL_STATIC_DRAW));
			vao->add_attribute(0,*coordinates_vbo);//Add to the VAO

			//Calculate and fill the normal buffer
			normals_size = normals.size() * sizeof(toolkit::Vector3f);
			normals_vbo.reset (new Vertex_Buffer(normals.size() * sizeof(Point3f),3, normals.data(), GL_STATIC_DRAW));			
			vao->add_attribute(1,*normals_vbo);//Add to the VAO
			
			vao->unbind();
			
			
			
		}

		/**
		 * @brief Render function
		 * 
		 */
		void render() override
		{
			vao->bind();			
			glDrawArrays(GL_TRIANGLES,0, coordinates_size);
			vao->unbind();
		}
	
	};

}


//Code by Miguel Palencia May 2019
#pragma once
#include <cmath>
#include <vector>
#include <string>
#include "../header/OpenGL.hpp"
#include "../header/Vertex_Buffer.hpp"
#include "../header/Mesh.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

using namespace tinyobj;
using namespace std;
namespace render
{	
	typedef glm::vec3 Vertex;
	typedef glm::vec2 UV;

	Mesh::Mesh()
	{
		{
			coordinates_vbo.reset(new Vertex_Buffer());
			normals_vbo.reset(new Vertex_Buffer());
			text_coord_vbo.reset(new Vertex_Buffer());
			vao.reset(new Vertex_Array());
			size_buffer = 0;
		}
	}
	Mesh::Mesh(const std::string& path)
	 {
		 attrib_t             attributes;
		 vector< shape_t    > shapes;
		 vector< material_t > materials;

		  size_buffer = 0;



		 // Load OBJ file:

		 if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &error, path.c_str()) || !error.empty())
		 {
			 return;
		 }

		 // Check if there're some problem:

		 if (shapes.size() == 0) { error = std::string("There're no shapes in ") + path; return; }
		 if (attributes.vertices.size() == 0) { error = std::string("There're no vertices in ") + path; return; }
		 if (attributes.normals.size() == 0) { error = std::string("There're no normals in ") + path; return; }
		 if (attributes.colors.size() == 0) { error = std::string("There're no colors in ") + path; return; } //but always is black


		 std::vector<Vertex> temporal_vertex_final;
		 std::vector<Vertex> temporal_normals_final;
		 std::vector<UV> temporal_text_coords_final;																						   // Se crean las mallas que forman el modelo:

		 for (auto & shape : shapes)
		 {
			 const vector< index_t > & indices = shape.mesh.indices;
			 const GLsizei             indices_count = (GLsizei)indices.size();

			

			
			 if (indices_count > 0)
			 {
				 

				 const GLsizei   vertices_count = indices_count;

				 vector< float > vertex_components(vertices_count * 3);
				 vector< float > normal_components(vertices_count * 3);

				 std::vector<Vertex> temporal_vertex;
				
				 std::vector<Vertex> temporal_normals;
				 
				 std::vector<UV> temporal_text_coords;
				
				

				 //Normals
				 for (size_t offset = 0; offset < attributes.normals.size(); offset += 3)
				 {
					 Vertex vertex
					 ({
						 attributes.normals[offset + 0],
						 attributes.normals[offset + 1],
						 attributes.normals[offset + 2]
					 });

					 temporal_normals.push_back(vertex);

				 }

				 //Vertex
				 for (size_t offset = 0; offset < attributes.vertices.size(); offset += 3)
				 {

					 Vertex vertex
					 ({
						 attributes.vertices[offset + 0],
						 attributes.vertices[offset + 1],
						 attributes.vertices[offset + 2]

					 });

					 temporal_vertex.push_back(vertex);



				 }

				 //TexCoords
				 for (size_t offset = 0; offset < attributes.texcoords.size(); offset += 2)
				 {

					 UV uv
					 ({
						 attributes.texcoords[offset + 0],
						 attributes.texcoords[offset + 1]

					 });

					 temporal_text_coords.push_back(uv);

				 }

				 //Set all the info 
				 for (size_t i = 0; i < indices.size(); ++i)
				 {
					 
					 temporal_vertex_final.push_back(temporal_vertex[indices[i].vertex_index]);
					 temporal_normals_final.push_back(temporal_normals[indices[i].normal_index]);
					 temporal_text_coords_final.push_back(temporal_text_coords[indices[i].texcoord_index]);
					 

				 }

				 //If we have more than one shape
				 size_buffer += indices.size();

			 }


		 }

		 //Create vertex buffers and vertex array
		 normals_vbo.reset(new Vertex_Buffer());
		 text_coord_vbo.reset(new Vertex_Buffer());
		 vao.reset(new Vertex_Array());

		 vao->bind();

		 //Fill the buffer
		 coordinates_vbo.reset(new Vertex_Buffer(size_buffer*sizeof(glm::vec3),3, temporal_vertex_final.data(),GL_STATIC_DRAW));
		 vao->add_attribute(0, *coordinates_vbo);

		 normals_vbo.reset(new Vertex_Buffer(size_buffer * sizeof(glm::vec3),3, temporal_normals_final.data(), GL_STATIC_DRAW));
		 vao->add_attribute(1, *normals_vbo);

		 text_coord_vbo.reset(new Vertex_Buffer(size_buffer * sizeof(glm::vec2),2, temporal_text_coords_final.data(), GL_STATIC_DRAW));
		 vao->add_attribute(2, *text_coord_vbo);


	 }

 }

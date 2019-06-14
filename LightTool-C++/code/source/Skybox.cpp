//Code by Miguel Palencia May 2019
#pragma once
#include "..\header\Skybox.hpp"
#include "..\header\Shader_Program.hpp"
#include "..\header\Shader_List.hpp"


namespace render
{

	float coordinates[] =
	{
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	Skybox::Skybox(const char * path, Scene* scene)
	{
		own_scene = scene;
		
		//Create the buffer of texCoords
		vao.reset(new Vertex_Array());
		texture_coord_vbo.reset(new Vertex_Buffer(sizeof(coordinates), 3, coordinates, GL_STATIC_DRAW));
		sky.reset(new Texture_Cubemap(path));
		shader_program.reset(new Shader_Program(default_vertex_shader_cube_code,default_fragment_shader_cube_code));
		
		vao->bind();
		vao->add_attribute(0, *texture_coord_vbo);

		//Add the essentials uniforms
		add_uniform_mat4("projection_matrix", own_scene->get_active_camera()->get_projection_matrix());
		add_uniform_mat4("view_matrix", own_scene->get_active_camera()->get_view_matrix_origin());
				
	}

	void Skybox::render()
	{
		update_uniforms();
		shader_program->use();
		
		//Update uniforms
		get_uniform("projection_matrix")->value.data.mat4 = own_scene->get_active_camera()->get_projection_matrix();
		get_uniform("view_matrix")->value.data.mat4 = own_scene->get_active_camera()->get_view_matrix_origin();

		glDepthMask(GL_FALSE);		
		vao->bind();
		sky->bind(0);
		glDrawArrays(GL_TRIANGLES, 0, texture_coord_vbo->get_size());
		glDepthMask(GL_TRUE);
	}

	
}
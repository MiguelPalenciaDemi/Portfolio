//Code by Miguel Palencia May 2019

#pragma once

#include "../header/Material.hpp"
#include "../header/OpenGL.hpp"
#include "../header/Shader_List.hpp"


namespace render
{

	

	Material::Uniform::Uniform(const Uniform &other)
	{
	
		name = other.name;
		value.type = other.value.type;
		value.data.int_value = other.value.data.int_value;
		value.data.float_value = other.value.data.float_value;
		value.data.uint_value = other.value.data.uint_value;
		value.data.vector2 = other.value.data.vector2;
		value.data.vector3 = other.value.data.vector3;
		value.data.vector4 = other.value.data.vector4;
		value.data.mat2 = other.value.data.mat2;
		value.data.mat3 = other.value.data.mat3;
		value.data.mat4 = other.value.data.mat4;

	
	}
	
	//Constructor
	Material::Material()
	{
		shader_program.reset(new Shader_Program(default_vertex_shader_code, default_fragment_shader_code));
		material_properties.diffuse = glm::vec3(1, 1, 1);
		material_properties.specular =8.f;
		add_uniform_float("opacity", 1);
	}

	Material::Material(GLenum type, std::vector<std::string> paths, std::string vertex, std::string fragment, float opacity)
	{
		shader_program.reset(new Shader_Program(vertex, fragment));
		material_properties.specular = 0.5f;
		for (std::size_t index = 0; index < paths.size(); ++index)
		{
			create_texture(type, paths[index]);
		}
		add_uniform_float("opacity", opacity);
	}

	Material::Material(GLenum type, std::vector<std::string> paths, float opacity)
	{
		shader_program.reset(new Shader_Program(default_vertex_shader_code, default_fragment_shader_code));
		material_properties.specular = 0.5f;
		for(std::size_t index = 0; index < paths.size(); ++index)
		{
			create_texture(type, paths[index]);
		}
		add_uniform_float("opacity", opacity);
	}

	Material::Material(GLenum type, std::string path, float opacity)
	{
		shader_program.reset(new Shader_Program(default_vertex_shader_code, default_fragment_shader_code));
		create_texture(type, path);
		material_properties.specular = 0.5f;
		add_uniform_float("opacity", opacity);
	}

	Material::Material(std::string vertex, std::string fragment, glm::vec3 color = {1,1,1 }, float specular = 0.5f, float opacity)
	{
		shader_program.reset(new Shader_Program(vertex, fragment));
		material_properties.diffuse = color;
		material_properties.specular = specular;
		add_uniform_float("opacity", opacity);
		add_uniform_vector3("color", color);
		
	}

	
	//Shader Program and uniforms

	void Material::set_shader_program(std::shared_ptr<Shader_Program> new_program)
	{
		shader_program = new_program;
	}

	void Material::set_material_info(glm::vec3 color, float specular)
	{
		material_properties.diffuse = color;
		material_properties.specular = specular;
	};



	//--------------------------------------------------------------------------------------------//
	//UPDATE:: When we add a uniform, we first if it's exist. We don't duplicate uniforms that way//
	//--------------------------------------------------------------------------------------------//

	void Material::add_uniform_int(std::string name, GLint value)
	{
		std::size_t i = 0;

		for (; i < uniforms.size() && uniforms[i].name != name; ++i);

		if (i == uniforms.size())
		{
			Uniform uniform;
			uniform.value.type = Var::Type::INT;
			uniform.value.data.int_value = value;
			uniform.name = name;
			uniforms.push_back(uniform);
		}
		else
			uniforms[i].value.data.int_value = value;	
		
	}

	void Material::add_uniform_uint(std::string name, GLuint value)
	{

		std::size_t i = 0;

		for (; i < uniforms.size() && uniforms[i].name != name; ++i);

		if (i == uniforms.size())
		{
			Uniform uniform;
			uniform.value.type = Var::Type::UINT;
			uniform.value.data.uint_value = value;
			uniform.name = name;
			uniforms.push_back(uniform);
		}
		else
			uniforms[i].value.data.uint_value = value;	
	}

	void Material::add_uniform_float(std::string name, GLfloat value)
	{
		std::size_t i = 0;

		for (; i < uniforms.size() && uniforms[i].name != name; ++i);

		if(i == uniforms.size())
		{
			Uniform uniform;
			uniform.value.type = Var::Type::FLOAT;
			uniform.value.data.float_value = value;
			uniform.name = name;
			uniforms.push_back(uniform);
		}
		else
			uniforms[i].value.data.float_value = value;	

	}


	void Material::add_uniform_vector2(std::string name, glm::vec2 value)
	{
		std::size_t i = 0;

		for (; i < uniforms.size() && uniforms[i].name != name; ++i);

		if (i == uniforms.size())
		{
			Uniform uniform;
			uniform.value.type = Var::Type::VECTOR2;
			uniform.value.data.vector2 = value;
			uniform.name = name;
			uniforms.push_back(uniform);
		}
		else
			uniforms[i].value.data.vector2 = value;		

	}


	void Material::add_uniform_vector3(std::string name, glm::vec3 value)
	{

		std::size_t i = 0;

		for (; i < uniforms.size() && uniforms[i].name != name; ++i);
		
		if (i == uniforms.size())
		{
			Uniform uniform;
			uniform.value.type = Var::Type::VECTOR3;
			uniform.value.data.vector3 = value;
			uniform.name = name;
			uniforms.push_back(uniform);
		}
		else
			uniforms[i].value.data.vector3 = value;


	}


	void Material::add_uniform_vector4(std::string name, glm::vec4 value)
	{

		std::size_t i = 0;

		for (; i < uniforms.size() && uniforms[i].name != name; ++i);

		if (i == uniforms.size())
		{
			Uniform uniform;
			uniform.value.type = Var::Type::VECTOR4;
			uniform.value.data.vector4 = value;
			uniform.name = name;
			uniforms.push_back(uniform);
		}
		else
			uniforms[i].value.data.vector4 = value;
	}


	void Material::add_uniform_mat2(std::string name, glm::mat2 value)
	{

		std::size_t i = 0;
		for (; i < uniforms.size() && uniforms[i].name != name; ++i);

		if (i == uniforms.size())
		{
			Uniform uniform;
			uniform.value.type = Var::Type::MAT2;
			uniform.value.data.mat2 = value;
			uniform.name = name;
			uniforms.push_back(uniform);
		}
		else
			uniforms[i].value.data.mat2 = value;		
	}


	void Material::add_uniform_mat3(std::string name, glm::mat3 value)
	{
		std::size_t i = 0;
		for (; i < uniforms.size() && uniforms[i].name != name; ++i);

		if (i == uniforms.size())
		{
			Uniform uniform;
			uniform.value.type = Var::Type::MAT3;
			uniform.value.data.mat3 = value;
			uniform.name = name;
			uniforms.push_back(uniform);
		}
		else
			uniforms[i].value.data.mat3 = value;
	}


	void Material::add_uniform_mat4(std::string name, glm::mat4 value)
	{

		std::size_t i = 0;
		for (; i < uniforms.size() && uniforms[i].name != name; ++i);

		if (i == uniforms.size())
		{
			Uniform uniform;
			uniform.value.type = Var::Type::MAT4;
			uniform.value.data.mat4 = value;
			uniform.name = name;
			uniforms.push_back(uniform);
		}
		else
			uniforms[i].value.data.mat4 = value;		
	
	}

	Material::Uniform * Material::get_uniform(std::string name)
	{

		for (auto& uniform : uniforms)
		{
			if (uniform.name == name)
				return &uniform;

		}

		return nullptr;
	}

	//Render
	void Material::render()
	{
		GLint index = 0;		

		for (auto texture : textures)
		{
			texture->bind(index);
			index++;
		}
		update_uniforms();

	}

	//Update all uniforms
	void Material::update_uniforms()
	{

		shader_program->use();


		for (auto uniform : uniforms)
		{

			switch (uniform.value.type)
			{
			case Var::Type::INT:
				shader_program->set_uniform_int(uniform.name, uniform.value.data.int_value);
				break;

			case Var::Type::FLOAT:
				shader_program->set_uniform_float(uniform.name, uniform.value.data.float_value);
				break;

			case Var::Type::VECTOR2:
				shader_program->set_uniform_vec2(uniform.name, uniform.value.data.vector2);
				break;

			case Var::Type::VECTOR3:
				shader_program->set_uniform_vec3(uniform.name, uniform.value.data.vector3);
				break;

			case Var::Type::VECTOR4:
				shader_program->set_uniform_vec4(uniform.name, uniform.value.data.vector4);
				break;

			case Var::Type::MAT2:
				shader_program->set_uniform_matrix2(uniform.name, uniform.value.data.mat2);
				break;

			case Var::Type::MAT3:
				shader_program->set_uniform_matrix4(uniform.name, uniform.value.data.mat4);
				break;

			case Var::Type::MAT4:
				shader_program->set_uniform_matrix4(uniform.name, uniform.value.data.mat4);
				break;

			default:
				break;
			}


		}
	}

	//Add texture
	void Material::create_texture(GLenum type, std::string path)
	{
		std::shared_ptr<Texture> texture;

		if (type == GL_TEXTURE_2D)
			texture.reset(new Texture2D(path.c_str()));

		else if (type == GL_TEXTURE_CUBE_MAP)
			texture.reset(new Texture_Cubemap(path.c_str()));

		textures.push_back(texture);
	};
}
//Code by Miguel Palencia May 2019
#pragma once 
#include "../header/Shader_Program.hpp"

namespace render
{
	Shader_Program * Shader_Program::active_shader_program = nullptr;



	Shader_Program::Shader_Program(std::string vertex_shader, std::string fragment_shader)
	{
		id = glCreateProgram();
		add_Shader(Shader::Shader_Type::vertex_shader, vertex_shader);
		add_Shader(Shader::Shader_Type::fragment_shader, fragment_shader);
		link_program();
	}

	Shader_Program::Shader_Program()
	{
		id = glCreateProgram();
		add_Shader(Shader::Shader_Type::vertex_shader, default_vertex_shader_code);
		add_Shader(Shader::Shader_Type::fragment_shader, default_fragment_shader_code);
		link_program();
	}

	void Shader_Program::add_Shader(Shader::Shader_Type type, std::string code)
	{
		shaders[type].reset(new Shader(type, code));
		link_shader(shaders[type]);
	}

	void Shader_Program::link_program()
	{
		glLinkProgram(id);
		check_link();
	}

	bool Shader_Program::check_link()
	{
		GLint success = 0;
		GLchar error[1024];

		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 512, NULL, error);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << error << std::endl;
			return false;
		}

		return true;

	}

	void Shader_Program::use()
	{
		if (this != active_shader_program)
		{
			glUseProgram(id);

			active_shader_program = this;
		}
	}

}
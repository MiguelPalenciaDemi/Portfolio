/**
 * @file Material.hpp
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
#include "Shader_Program.hpp"
#include "Texture.hpp"
#include "Texture2D.hpp"
#include "Texture_Cubemap.hpp"
#include <vector>


namespace render 
{
	
	/**
	 * @brief Material class
	 * 
	 */
	class Material
	{
		/**
		 * @brief Var struct 
		 * 
		 */
		struct Var
		{
			/**
			 * @brief Type of the data
			 * 
			 */
			enum class Type
			{
				BYTE, UBYTE, SHORT, USHORT, INT, UINT, FLOAT, VECTOR2, VECTOR3, VECTOR4, MAT2, MAT3, MAT4
			};

			/**
			 * @brief value
			 * 
			 */
			union Value
			{
				GLint   int_value;
				GLuint  uint_value;
				GLfloat float_value;
				glm::vec2 vector2;
				glm::vec3 vector3;
				glm::vec4 vector4;
				glm::mat2 mat2;
				glm::mat3 mat3;
				glm::mat4 mat4;			
				
				Value()
				{
					glm::vec2 vector2 = glm::vec2();
					glm::vec3 vector3 = glm::vec3();
					glm::vec4 vector4 = glm::vec4();
					glm::mat2 mat2    = glm::mat2();
					glm::mat3 mat3 = glm::mat3();
					glm::mat4 mat4 = glm::mat4();;
				
				}
			};
			

			Type type;
			Value data;
			
			

		};

		/**
		 * @brief Uniform struct
		 * 
		 */
		struct Uniform
		{
			std::string name;
			Var value;

		public:
			Uniform() {};
			Uniform(const Uniform &);	
			
		
		};

		/**
		 * @brief Material info
		 * 
		 */
		struct Material_Info
		{
			glm::vec3 diffuse;
			float specular;

		};

	protected:

		/**
		 * @brief collection of textures
		 * 
		 */
		std::vector<std::shared_ptr<Texture>> textures;

		/**
		 * @brief shader program linked
		 * 
		 */
		std::shared_ptr<Shader_Program> shader_program;	
		/**
		 * @brief Info
		 * 
		 */
		Material_Info material_properties;

		/**
		 * @brief Collection of uniforms
		 * 
		 */
		std::vector<Uniform> uniforms;
		

	public:

		/**
		 * @brief Construct a new Material object
		 * 
		 */
		Material();

		/**
		 * @brief Construct a new Material object
		 * 
		 * @param type 
		 * @param paths 
		 * @param vertex 
		 * @param fragment 
		 */
		Material(GLenum type, std::vector<std::string> paths, std::string vertex, std::string fragment,float opacity = 1);

		/**
		 * @brief Construct a new Material object
		 * 
		 * @param type 
		 * @param paths 
		 */
		Material(GLenum type, std::vector<std::string> paths, float opacity = 1);

		/**
		 * @brief Construct a new Material object
		 * 
		 * @param type 
		 * @param path 
		 */
		Material(GLenum type, std::string path, float opacity = 1);

		/**
		 * @brief Construct a new Material object
		 * 
		 * @param vertex 
		 * @param fragment 
		 * @param color 
		 * @param specular 
		 */
		Material(std::string vertex, std::string fragment, glm::vec3 color, float specular, float opacity = 1);

		/**
		 * @brief Construct a new Material object
		 * 
		 * @param type 
		 * @param path 
		 * @param vertex 
		 * @param fragment 
		 * @param color 
		 * @param specular 
		 */
		Material(GLenum type, std::string path, std::string vertex, std::string fragment, glm::vec3 color, float specular, float opacity = 1);
		
		
		/**
		 * @brief Set the material info 
		 * 
		 * @param color 
		 * @param specular 
		 */
		void set_material_info(glm::vec3 color, float specular);

		/**
		 * @brief Get the diffuse 
		 * 
		 * @return glm::vec3 
		 */
		glm::vec3 get_diffuse() { return material_properties.diffuse; }

		/**
		 * @brief Get the specular 
		 * 
		 * @return float 
		 */
		float get_specular() { return material_properties.specular; }

		/**
		 * @brief Set the shader program object
		 * 
		 * @param new_program 
		 */
		void set_shader_program(std::shared_ptr<Shader_Program> new_program);


		/**
		 * @brief Get the shader program object
		 * 
		 * @return std::shared_ptr<Shader_Program> 
		 */
		std::shared_ptr<Shader_Program> get_shader_program() { return shader_program; }		

		/**
		 * @brief 
		 * 
		 * @param texture 
		 */
		void add_texture(std::shared_ptr<Texture> texture) { if(texture!=nullptr)textures.push_back(texture); }

		/**
		 * @brief add uniform with int value 
		 * 
		 * @param name 
		 * @param value 
		 */
		void add_uniform_int(std::string name, GLint value);	

		/**
		 * @brief add uniform with unsingned integer value
		 * 
		 * @param name 
		 * @param value 
		 */
		void add_uniform_uint(std::string name, GLuint value);

		/**
		 * @brief add uniform with float value
		 * 
		 * @param name 
		 * @param value 
		 */
		void add_uniform_float(std::string name, GLfloat value);

		/**
		 * @brief add uniform with vector2 value
		 * 
		 * @param name 
		 * @param value 
		 */
		void add_uniform_vector2(std::string name, glm::vec2 value);

		/**
		 * @brief add uniform with vector3 value
		 * 
		 * @param name 
		 * @param value 
		 */
		void add_uniform_vector3(std::string name, glm::vec3 value);

		/**
		 * @brief add uniform with vector4 value
		 * 
		 * @param name 
		 * @param value 
		 */
		void add_uniform_vector4(std::string name, glm::vec4 value);

		/**
		 * @brief add uniform with matrix2 value
		 * 
		 * @param name 
		 * @param value 
		 */
		void add_uniform_mat2(std::string name, glm::mat2 value);

		/**
		 * @brief add uniform with matrix3 value
		 * 
		 * @param name 
		 * @param value 
		 */
		void add_uniform_mat3(std::string name, glm::mat3 value);

		/**
		 * @brief add uniform with matrix4 value
		 * 
		 * @param name 
		 * @param value 
		 */
		void add_uniform_mat4(std::string name, glm::mat4 value);

		/**
		 * @brief Get the uniform object
		 * 
		 * @param name 
		 * @return Uniform* 
		 */
		Uniform* get_uniform(std::string name);

		/**
		 * @brief Update uniforms values on shader
		 * 
		 */
		void update_uniforms();

		/**
		 * @brief render the material. Bind textures and update lights
		 * 
		 */
		void render();		

		/**
		 * @brief Create a texture object
		 * 
		 * @param type 
		 * @param path 
		 */
		void create_texture(GLenum type, std::string path);
		
	
	
	};

}
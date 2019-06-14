/**
 * @file Scene.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once
#include "Camera.hpp"
#include "Model.hpp"
#include "Shader_Program.hpp"
#include "Physic_World.hpp"
#include "Directional_Light.hpp"
#include "Point_Light.hpp"
#include <vector>
#include <map>
#include <ParserXML.hpp>


namespace render
{	
	class Skybox;

	/**
	 * @brief Scene class
	 * 
	 */
	class Scene
	{

	protected:

		/**
		 * @brief active camera pointer
		 * 
		 */
		Camera* active_camera;
		std::vector<Camera*> cameras;

		/**
		 * @brief collection of models
		 * 
		 */
		std::map<std::string,std::shared_ptr<Model>> models;

		/**
		 * @brief Directional light
		 * 
		 */
		Directional_Light* directional_light;

		std::vector<Directional_Light*> directional_light_list;

		/**
		 * @brief Collection of point lights
		 * 
		 */
		std::vector<Point_Light*> point_light_list;

		/**
		 * @brief variable thar store the time to the uniforms that depend on time
		 * 
		 */
		float time_variable = 0;

		/**
		 * @brief Skybox pointer
		 * 
		 */
		Skybox* skybox;

		Physics_World physic_world;

		std::vector<std::shared_ptr<Material>> materials;

		parser::ParserXML parser_xml;

		public:

			/**
			 * @brief Construct a new Scene object
			 * 
			 * @param width 
			 * @param height 
			 */
			Scene(std::size_t width, std::size_t height);

			Physics_World* get_world() { return &physic_world; }
			/**
			 * @brief Add model
			 * 
			 * @param name 
			 * @param model 
			 */
			void add_model(std::string name, std::shared_ptr<Model> model) { models[name] = model; }			

			/**
			 * @brief render function
			 * 
			 */
			void render();

			/**
			 * @brief Update function
			 * 
			 * @param time 
			 */
			virtual void  update(float time);
			

			/**
			 * @brief Get the active camera pointer
			 * 
			 * @return Camera* 
			 */
			Camera* get_active_camera() { return active_camera; }

			/**
			 * @brief Set the active camera pointer
			 * 
			 * @param camera 
			 */
			void set_active_camera(Camera* camera) { active_camera = camera; }

			/**
			 * @brief Get the shader program of piece object
			 * 
			 * @param name_model 
			 * @param name_piece 
			 * @return std::shared_ptr<Shader_Program> 
			 */
			std::shared_ptr<Shader_Program> get_shader_program_of_piece(std::string name_model, std::string name_piece)	{ return models[name_model]->get_pieces()[name_piece].second->get_shader_program(); }

			/**
			 * @brief Get the material object
			 * 
			 * @param name_model 
			 * @param name_piece 
			 * @return Material& 
			 */
			Material& get_material(std::string name_model, std::string name_piece) { return *models[name_model]->get_pieces()[name_piece].second; }

			/**
			 * @brief Get the actor object
			 * 
			 * @param name 
			 * @return std::shared_ptr<Model> 
			 */
			std::shared_ptr<Model> get_actor(std::string name) { return models[name]; }			

			/**
			 * @brief Get the directional light object
			 * 
			 * @return Directional_Light 
			 */
			Directional_Light get_directional_light() { return *directional_light; }

			/**
			 * @brief Get the point lights collection
			 * 
			 * @return std::vector<Point_Light> 
			 */
			std::vector<Point_Light*> get_point_lights() { return point_light_list; }

			/**
			 * @brief Get the directional lights colection
			 * 
			 * @return std::vector<Directional_Light*> 
			 */
			std::vector<Directional_Light*> get_directional_lights() { return directional_light_list; }

			/**
			 * @brief Clean all the lights. 
			 * 
			 */
			void clean_lights();
			
			/**
			 * @brief Clean just the point lights
			 * 
			 */
			void clean_point_lights();
			

			/**
			 * @brief Clean just th edirectional light
			 * 
			 */
			void clean_directional_lights();
			
			/**
			 * @brief Create a point light 
			 * 
			 * @param _ambient 
			 * @param _intensity 
			 * @param _specular 
			 * @param _color 
			 * @param _position 
			 * @param _constant 
			 * @param _linear 
			 * @param _quadratic 
			 * @return Point_Light* 
			 */
			Point_Light* create_point_light(float _ambient, float _intensity, float _specular, glm::vec3 _color, glm::vec3 _position, float _constant, float _linear, float _quadratic);
			
			/**
			 * @brief Create a point light 
			 * 
			 * @param _ambient 
			 * @param _intensity 
			 * @param _specular 
			 * @param _color 
			 * @param _position 
			 * @param _range 
			 * @return Point_Light* 
			 */
			Point_Light* create_point_light(float _ambient, float _intensity, float _specular, glm::vec3 _color, glm::vec3 _position, float _range);
			
			/**
			 * @brief Create a directional light 
			 * 
			 * @param _ambient 
			 * @param _intensity 
			 * @param _specular 
			 * @param _color 
			 * @param _position 
			 * @param _direction 
			 * @return Directional_Light* 
			 */
			Directional_Light* create_directional_light(float _ambient, float _intensity, float _specular, glm::vec3 _color, glm::vec3 _position, glm::vec3 _direction);
			
			/**
			 * @brief Load a xml. Load lights config
			 * 
			 * @param path 
			 */
			void load_xml(std::string path);

			/**
			 * @brief Write a xml with all the info about the lights
			 * 
			 * @param path 
			 */
			void write_xml(std::string path);
			
			
	};

}
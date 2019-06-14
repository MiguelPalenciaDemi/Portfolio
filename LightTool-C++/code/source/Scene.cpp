//Code by Miguel Palencia May 2019
#pragma once 
#include "..\header\Skybox.hpp"
#include "..\header\Scene.hpp"
#include "..\header\Mesh.hpp"
#include "..\header\Model.hpp"
#include "..\header\Light.hpp"
#include "..\header\Material.hpp"
#include "..\header\Windmill.hpp"
#include <ParserXML.hpp>


namespace render
{
	
	Scene::Scene(std::size_t width, std::size_t height)
	{

		Camera* new_camera = new Camera(60.0f, (GLfloat)(width / height), 0.01f, 1000.f);
		active_camera = new_camera;

		cameras.push_back(new_camera);
		skybox = new Skybox("../../assets/mnight", this);
		
		directional_light_list.push_back(new Directional_Light(0.1f,0.1f, 0, glm::vec3(1.f, 1.f,1.f), glm::vec3(0, 80, 0), glm::vec3(-1, 0.5, 0.5)));

	}

	void Scene::render()
	{
		skybox->render();
		
		for (auto &model : models)
		{			
			model.second->render();
		}

		for (auto &model : models)
		{
			model.second->render_opacity();
		}
		
	}

	void Scene::update(float time)
	{
		time_variable += time; //We need to the shader thar depends on time
		physic_world.update(time);
		for (auto &model : models)
		{
			model.second->update(time);
		}

		if (active_camera)
			active_camera->update();



	}

	void Scene::clean_lights()
	{

		for (auto model : models)
		{
			model.second->clean_directional_light_values();
			model.second->clean_point_light_values();


		}

		directional_light_list.clear();
		point_light_list.clear();

	}

	void Scene::clean_point_lights()
	{
		for (auto model : models)
		{
			model.second->clean_point_light_values();
		}

		point_light_list.clear();
	}

	void Scene::clean_directional_lights()
	{
		for (auto model : models)
		{
			model.second->clean_directional_light_values();
		}

		directional_light_list.clear();
	}

	Point_Light * Scene::create_point_light(float _ambient, float _intensity, float _specular, glm::vec3 _color, glm::vec3 _position, float _constant, float _linear, float _quadratic)
	{
		Point_Light* light = new Point_Light(_ambient, _intensity, _specular, _color, _position, _constant, _linear, _quadratic);
		point_light_list.push_back(light);

		for (auto m : models)
		{
			std::shared_ptr<Model> model = m.second;
			for (auto mat : model->get_pieces())
			{
				std::shared_ptr<Material> material = mat.second.second;
				model->set_point_light_values(material, point_light_list.size() - 1);

			}

		}

		return light;
	}

	Point_Light * Scene::create_point_light(float _ambient, float _intensity, float _specular, glm::vec3 _color, glm::vec3 _position, float _range)
	{
		Point_Light* light = new Point_Light(_ambient, _intensity, _specular, _color, _position, _range);
		point_light_list.push_back(light);

		for (auto m : models)
		{
			std::shared_ptr<Model> model = m.second;
			for (auto mat : model->get_pieces())
			{
				std::shared_ptr<Material> material = mat.second.second;
				model->set_point_light_values(material, point_light_list.size() - 1);

			}

		}

		return light;
	}

	Directional_Light * Scene::create_directional_light(float _ambient, float _intensity, float _specular, glm::vec3 _color, glm::vec3 _position, glm::vec3 _direction)
	{
		Directional_Light* light = new Directional_Light(_ambient, _intensity, _specular, _color, _position, _direction);
		directional_light_list.push_back(light);

		for (auto m : models)
		{
			std::shared_ptr<Model> model = m.second;
			for (auto mat : model->get_pieces())
			{
				std::shared_ptr<Material> material = mat.second.second;
				model->set_directional_light_values(material, directional_light_list.size() - 1);

			}

		}

		return light;
	}

	void Scene::load_xml(std::string path)
	{
		if (FILE *file = fopen(path.c_str(), "r"))
		{
			fclose(file);
			clean_lights();

			//Parse Collections
			std::vector<parser::Directional_Light_Struct*> direct_lights;
			std::vector<parser::Point_Light_Struct*> points_lights;

			//Fill the vectors
			parser_xml.load_xml(path, &points_lights, &direct_lights);


			//Assign the values
			for (auto light : direct_lights)
			{
				create_directional_light(light->ambient, light->intensity, light->specular, glm::vec3(light->color[0], light->color[1], light->color[2]),
					glm::vec3(0, 0, 0), glm::vec3(light->direction[0], light->direction[1], light->direction[2]));

			}

			for (auto light : points_lights)
			{

				create_point_light(light->ambient, light->intensity, light->specular, glm::vec3(light->color[0], light->color[1], light->color[2]),
					glm::vec3(light->position[0], light->position[1], light->position[2]), light->range);
			}

		}


	}

	void Scene::write_xml(std::string path)
	{
		
		//Parse Collections
		std::vector<parser::Directional_Light_Struct*> direct_lights;
		std::vector<parser::Point_Light_Struct*> points_lights;

		//Fill the collectors
		for (auto light : directional_light_list)
		{
			parser::Directional_Light_Struct* direct_light = new parser::Directional_Light_Struct();
			direct_light->ambient = light->get_ambient();

			direct_light->color[0] = light->get_color().x;
			direct_light->color[1] = light->get_color().y;
			direct_light->color[2] = light->get_color().z;

			direct_light->direction[0] = light->get_direction().x;
			direct_light->direction[1] = light->get_direction().y;
			direct_light->direction[2] = light->get_direction().z;


			direct_light->intensity = light->get_intensity();
			direct_light->specular = light->get_specular();

			direct_lights.push_back(direct_light);

		}

		for (auto light : point_light_list)
		{
			parser::Point_Light_Struct* point_light = new parser::Point_Light_Struct();
			point_light->ambient = light->get_ambient();

			point_light->color[0] = light->get_color().x;
			point_light->color[1] = light->get_color().y;
			point_light->color[2] = light->get_color().z;

			point_light->position[0] = light->get_position().x;
			point_light->position[1] = light->get_position().y;
			point_light->position[2] = light->get_position().z;


			point_light->intensity = light->get_intensity();
			point_light->specular = light->get_specular();
			point_light->range = light->get_range();

			points_lights.push_back(point_light);

		}

		//Write the xml with all the lights
		parser_xml.write_xml(path, points_lights, direct_lights);

	}


	

	

	

}
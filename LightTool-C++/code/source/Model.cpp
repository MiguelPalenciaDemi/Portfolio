//Code by Miguel Palencia May 2019

#pragma once
#include "..\header\Model.hpp"
#include "..\header\Scene.hpp"
#include "..\header\Light.hpp"
#include "..\header\Point_Light.hpp"


namespace render
{




	void Model::add_piece(std::string name, std::shared_ptr<Mesh> mesh, const std::shared_ptr<Material> material)
	{
		//Add main uniforms to be can rendered
		material->add_uniform_mat4("model_matrix", local_transform.get_transform());		
		material->add_uniform_mat4("projection_matrix", own_scene->get_active_camera()->get_projection_matrix());		
		material->add_uniform_mat4("view_matrix", own_scene->get_active_camera()->get_view_matrix());

		material->add_uniform_vector3("camera_position", own_scene->get_active_camera()->get_position());

		//Uniforms about lightning
		std::vector<Directional_Light*> directional_list = own_scene->get_directional_lights();
		material->add_uniform_int("number_of_directional_lights", directional_list.size());

		for (std::size_t i = 0; i < directional_list.size(); ++i)
		{
			set_directional_light_values(material, i);
		}


		//set_directional_light_values(material);

		std::vector<Point_Light*> point_list = own_scene->get_point_lights();
		material->add_uniform_int("number_of_point_lights", point_list.size());
		for (std::size_t i = 0; i<point_list.size(); ++i)
		{
			set_point_light_values(material, i);
		}

		//Add the piece
		list_pieces[name] = { mesh,material };

	}

	void Model::render()
	{
		if(visible)
		{
			for (auto &piece : list_pieces)
			{

				std::shared_ptr<Material> mat = piece.second.second;


				//Directional
				//update_directional_light_values(mat);
				std::vector<Directional_Light*> directional_list = own_scene->get_directional_lights();
				mat->get_uniform("number_of_directional_lights")->value.data.int_value = directional_list.size();

				for (std::size_t i = 0; i < directional_list.size(); ++i)
				{
					update_directional_light_values(mat, i,*directional_list[i]);
				}

				//PointLight
				std::vector<Point_Light*> point_list = own_scene->get_point_lights();
				mat->get_uniform("number_of_point_lights")->value.data.int_value = point_list.size();
				for (std::size_t i = 0; i<point_list.size(); ++i)
				{
					update_point_light_values(mat, i, *point_list[i]);
				}

				float opa = mat->get_uniform("opacity")->value.data.float_value;
				if (mat->get_uniform("opacity")->value.data.float_value == 1)
				{
					mat->render();
					std::shared_ptr<Mesh> mesh = piece.second.first;
					mesh->render();
				}
			}
		}
		
		
	}

	void Model::render_opacity()
	{
		if (visible)
		{
			glEnable(GL_BLEND);
			for (auto &piece : list_pieces)
			{
				std::shared_ptr<Material> mat = piece.second.second;
				if (mat->get_uniform("opacity")->value.data.float_value < 1)
				{
					mat->render();
					std::shared_ptr<Mesh> mesh = piece.second.first;
					mesh->render();
				}
			}

			glDisable(GL_BLEND);
		}
	}

	void Model::update(float time)
	{
		Actor::update();
		for (auto &piece : list_pieces)
		{
			//Update uniforms of position
			std::shared_ptr<Material> mat = piece.second.second;
			mat->get_uniform("model_matrix")->value.data.mat4 = local_transform.get_transform();
			mat->get_uniform("projection_matrix")->value.data.mat4 = own_scene->get_active_camera()->get_projection_matrix();
			mat->get_uniform("view_matrix")->value.data.mat4 = own_scene->get_active_camera()->get_view_matrix();

		}
		
	}

	

	void Model::set_directional_light_values(std::shared_ptr<Material> material, int index)
	{
		std::string name = "directional_lights[";
		name.append(std::to_string(index));
		name.append("]");

		
		material->add_uniform_vector3(name + ".color", vec3(0, 0, 0));
		material->add_uniform_vector3(name + ".direction", vec3(0, 0, 0));
		material->add_uniform_float(name + ".ambient", 0);
		material->add_uniform_float(name + ".specular", 0);
		material->add_uniform_float(name + ".intensity", 0);
		
	}

	void Model::set_point_light_values(std::shared_ptr<Material> material,int index)
	{
		std::string name = "point_lights[";
		name.append(std::to_string(index));
		name.append("]");
		
		material->add_uniform_vector3(name + ".position",vec3(0,0,0));
		material->add_uniform_vector3(name + ".color", vec3(0, 0, 0));
		material->add_uniform_float(name   + ".ambient", 0);				
		material->add_uniform_float(name   + ".intensity", 0);				
		material->add_uniform_float(name + ".specular",0);
		material->add_uniform_float(name + ".constant", 0);
		material->add_uniform_float(name + ".linear",0);
		material->add_uniform_float(name + ".quadratic", 0);
		material->add_uniform_int(name + ".turn_on", 1);

		
	}

	

	void Model::update_directional_light_values(std::shared_ptr<Material> material, int index, Directional_Light light)
	{
		std::string name = "directional_lights[";
		name.append(std::to_string(index));
		name.append("]");

		material->get_uniform(name + ".color")->value.data.vector3 = light.get_color();
		material->get_uniform(name + ".direction")->value.data.vector3 = light.get_direction();
		material->get_uniform(name + ".specular")->value.data.float_value = light.get_specular();
		material->get_uniform(name + ".ambient")->value.data.float_value = light.get_ambient();
		material->get_uniform(name + ".intensity")->value.data.float_value = light.get_intensity();
		
	}

	void Model::update_point_light_values(std::shared_ptr<Material> material, int index, Point_Light light)
	{
		std::string name = "point_lights[";
		name.append(std::to_string(index));
		name.append("]");

		material->get_uniform(name + ".color")->value.data.vector3 = light.get_color();
		material->get_uniform(name + ".position")->value.data.vector3 = light.get_position();
		material->get_uniform(name + ".specular")->value.data.float_value = light.get_specular();
		material->get_uniform(name + ".ambient")->value.data.float_value = light.get_ambient();
		material->get_uniform(name + ".intensity")->value.data.float_value = light.get_intensity();
		material->get_uniform(name + ".constant")->value.data.float_value = light.get_constant();
		material->get_uniform(name + ".linear")->value.data.float_value = light.get_linear();
		material->get_uniform(name + ".quadratic")->value.data.float_value = light.get_quadratic();
		material->get_uniform(name + ".turn_on")->value.data.int_value = light.get_enable();
	}



	void Model::clean_directional_light_values()
	{
		for (auto &piece : list_pieces)
		{

			std::shared_ptr<Material> mat = piece.second.second;
			std::vector<Directional_Light*> directional_list = own_scene->get_directional_lights();
			mat->get_uniform("number_of_directional_lights")->value.data.int_value = 0;

			for (std::size_t i = 0; i < directional_list.size(); ++i)
			{
				std::string name = "directional_lights[";
				name.append(std::to_string(i));
				name.append("]");

				mat->get_uniform(name + ".color")->value.data.vector3 = { 0,0,0 };
				mat->get_uniform(name + ".direction")->value.data.vector3 = { 0,0,0 };
				mat->get_uniform(name + ".specular")->value.data.float_value = 0;
				mat->get_uniform(name + ".ambient")->value.data.float_value = 0;
				mat->get_uniform(name + ".intensity")->value.data.float_value = 0;
			}

		}
	}

	void Model::clean_point_light_values()
	{
		for (auto &piece : list_pieces)
		{

			std::shared_ptr<Material> mat = piece.second.second;
			std::vector<Point_Light*> point_list = own_scene->get_point_lights();
			mat->get_uniform("number_of_directional_lights")->value.data.int_value = 0;

			for (std::size_t i = 0; i < point_list.size(); ++i)
			{
				std::string name = "point_lights[";
				name.append(std::to_string(i));
				name.append("]");


				mat->get_uniform(name + ".color")->value.data.vector3 = { 0,0,0 };
				mat->get_uniform(name + ".position")->value.data.vector3 = { 0,0,0 };
				mat->get_uniform(name + ".specular")->value.data.float_value = 0;
				mat->get_uniform(name + ".ambient")->value.data.float_value = 0;
				mat->get_uniform(name + ".intensity")->value.data.float_value = 0;				
				mat->get_uniform(name + ".turn_on")->value.data.int_value = 0;

			}

		}
	}
	

	

}
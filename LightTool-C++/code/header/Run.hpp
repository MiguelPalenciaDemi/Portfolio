
//Code by Miguel Palencia May 2019
#pragma once

#include "Plane.hpp"
#include <SFML/Window.hpp>

#include "OpenGL.hpp"
#include <btBulletDynamicsCommon.h>
#include "Shader_Program.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Scene.hpp"
#include "My_Scene.hpp"
#include "Material.hpp"
#include "Texture2D.hpp"
#include "Windmill.hpp"
#include "Shader_List.hpp"
#include<tiny_obj_loader.h>


#include <iostream>

using namespace sf;
using namespace render;

static const size_t window_width = 1080;
static const size_t window_height = 720;



int Start()
{
	btDefaultCollisionConfiguration it;
	// Create the window and the view that will be shown within the window:
	Window window(VideoMode(window_width, window_height), "Render OpenGL", Style::Titlebar | Style::Close, ContextSettings(32));

	//	window.getSettings().setMouseCursorGrabbed();

	// Initialization:
	GLenum glew_initialization = InitOpenGL();
	window.setVerticalSyncEnabled(true);

	//Depth activation
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//Transparency activation
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//Create Scene
	std::shared_ptr<My_Scene> scene;
	scene.reset(new My_Scene(window_width, window_height));

	//Timer
	Clock timer_sfml;

	// Run the main loop:	
	bool running = true;

	//Mouse object
	Mouse mouse;
	int lastX = 0, lastY = 0;



	do
	{
		//Get time between ticks
		float time_elapsed = timer_sfml.restart().asSeconds();

		Event event;
		float x_offset = 0;
		float y_offset = 0;

		// Attend the window events:
		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed)
			{
				running = false;
			}

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == 0)//A
				{
					scene->get_character()->move_left();
				}
				if (event.key.code == 3)//D
				{
					scene->get_character()->move_right();
				}

				if (event.key.code == 22)//W
				{
					scene->get_character()->move_forward();
				}

				if (event.key.code == 18)//S
				{
					scene->get_character()->move_backward();
				}

				if (event.key.code == 73)//Arrow UP
				{
					scene->get_active_camera()->move_up(50 * time_elapsed);
				}

				if (event.key.code == 74)//Arrow DOWN
				{
					scene->get_active_camera()->move_down(50 * time_elapsed);
				}

				if (event.key.code == 72)//Arrow RIGTH
				{
					scene->get_active_camera()->move_rigth(50 * time_elapsed);
				}

				if (event.key.code == 71)//Arrow LEFT
				{
					scene->get_active_camera()->move_left(50 * time_elapsed);
				}

				if (event.key.code == 57)//Space
				{
					scene->get_character()->fire();
				}
				if (event.key.code == 17)//R
				{
					scene->create_rock();
				}
				if (event.key.code == 1)//B
				{
					scene->create_point_light(0.8f, 1, 0.f, glm::vec3(0.1f, 0.1f, 1), scene->get_active_camera()->get_position(), 1, 0.045f, 0.0075f);
					//scene->create_point_light();
				}
			}

			if (event.type == Event::KeyReleased)
			{
				//scene->get_character()->stop();

			}

			if (event.type == Event::MouseMoved)
			{

				float sensitivity = 0.5f;
				x_offset += (mouse.getPosition(window).x - lastX)*sensitivity;
				y_offset += (mouse.getPosition(window).y - lastY)*sensitivity;
				scene->get_active_camera()->rotate(y_offset, x_offset);
				lastX = mouse.getPosition(window).x;
				lastY = mouse.getPosition(window).y;

			}


			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == 0)
					scene->get_active_camera()->move_up(50 * time_elapsed);
				if (event.key.code == 1)
					scene->get_active_camera()->move_down(50 * time_elapsed);



			}
		}

		//Reset buffer and "clean" the window
		glClearColor(0.5f, 0.5f, 0.5f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		//Update and render

		scene->update(time_elapsed);
		scene->render();

		window.display();


	} while (running);

	// Close the application:

	return (EXIT_SUCCESS);
}

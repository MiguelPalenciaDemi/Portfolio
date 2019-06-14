#include "Tool.h"
#include <QtWidgets/QApplication>
#include "SFML\Window.hpp"
#include "OpenGL.hpp"
#include "My_Scene.hpp"
#include <ParserXML.hpp>

using namespace sf;
using namespace render;
static  size_t window_width = 800;
static  size_t window_height = 500;
int main(int argc, char *argv[])
{
	window_width = std::stoi(argv[1]);
	window_height = std::stoi(argv[2]);

	parser::ParserXML p;
	QApplication a(argc, argv);
	sf::Window window(VideoMode(window_width, window_height), "Render OpenGL", Style::Titlebar | Style::Close, ContextSettings(32));
	window.setPosition({ 200,100 });
	GLenum glew_initialization = InitOpenGL();
	window.setVerticalSyncEnabled(true);

	//Depth activation
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//Transparency activation
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Tool w;

	w.move(1100,100);
	
	//Timer
	Clock timer_sfml;

	// Run the main loop:	
	bool running = true;

	//Mouse object
	Mouse mouse;
	int lastX = 0, lastY = 0;

	//Create Scene
	std::shared_ptr<My_Scene> scene;
	scene.reset(new My_Scene(window_width, window_height));
	w.set_scene(scene.get());


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
					
					scene->get_active_camera()->move_left(50 * time_elapsed);

				}
				if (event.key.code == 3)//D
				{
					scene->get_active_camera()->move_rigth(50 * time_elapsed);
				}

				if (event.key.code == 22)//W
				{
					scene->get_active_camera()->move_up(50 * time_elapsed);
					
				}

				if (event.key.code == 18)//S
				{
					scene->get_active_camera()->move_down(50 * time_elapsed);

				}	
				if (event.key.code == 16)//Q
				{
					scene->get_active_camera()->rotate(0, -200*time_elapsed);

				}
				if (event.key.code == 4)//E
				{
					scene->get_active_camera()->rotate(0, 200 * time_elapsed);


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
				scene->get_active_camera()->rotate(y_offset, x_offset*0.1f);
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
		w.update();

		scene->render();

		window.display();
		w.show();


	} while (running);

	
	return (EXIT_SUCCESS);
}

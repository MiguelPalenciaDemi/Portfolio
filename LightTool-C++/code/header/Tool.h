#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tool.h"
#include "My_Scene.hpp"

using namespace render;
class Tool : public QMainWindow
{
	Q_OBJECT
		My_Scene* scene;
public:
	Tool(QWidget *parent = Q_NULLPTR,My_Scene* _scene =nullptr);
	void set_scene(My_Scene* _scene) { scene = _scene; }
	void update();
private:
	Ui::ToolClass ui;

	private slots:
	void directional_button_pressed()
	{
		glm::vec3 color = glm::vec3((float)(ui.directional_r->value()), (float)(ui.directional_g->value()), (float)(ui.directional_b->value()));
		glm::vec3 pos = glm::vec3(0,0,0);
		glm::vec3 direction = glm::vec3((float)(ui.directional_x->value()), (float)(ui.directional_y->value()), (float)(ui.directional_z->value()));
		scene->create_directional_light((float)(ui.directional_ambient->value()), (float)(ui.directional_intensity->value()), (float)(ui.directional_specular->value()),
			color, pos, direction);
	
	};
	void point_button_pressed()
	{
		
		glm::vec3 color = glm::vec3((float)(ui.point_r->value()), (float)(ui.point_g->value()), (float)(ui.point_b->value()));
		glm::vec3 pos = glm::vec3((float)(ui.point_x->value()), (float)(ui.point_y->value()), (float)(ui.point_z->value()));
		scene->create_point_light((float)(ui.point_ambient->value()), (float)(ui.point_intensity->value()), (float)(ui.point_specular->value()),
			color, pos, (float)(ui.point_range->value()));

	};

	void load_xml()
	{
		ui.LoadPath->text();
		
		scene->load_xml(ui.LoadPath->text().toLocal8Bit().constData());
	
	};

	void save_xml()
	{
		

		scene->write_xml(ui.SavePath->text().toLocal8Bit().constData());

	};

	void delete_point_lights()
	{
		scene->clean_point_lights();
	}
	void delete_directional_lights()
	{
		scene->clean_directional_lights();
	}
	
};

#pragma once
#include "Tool.h"
#include "My_Scene.hpp"
#include <string>
using namespace render;

Tool::Tool(QWidget *parent,  My_Scene* _scene)
	: QMainWindow(parent)
{
	scene = _scene;
	ui.setupUi(this);
	connect(ui.CreateDirectionalLight_Button, SIGNAL(released()), this, SLOT(directional_button_pressed()));
	connect(ui.CreatePointLight_Button, SIGNAL(released()), this, SLOT(point_button_pressed()));
	connect(ui.DeleteDirectionalLight_Button, SIGNAL(released()), this, SLOT(delete_directional_lights()));
	connect(ui.DeletePointLight_Button, SIGNAL(released()), this, SLOT(delete_point_lights()));
	connect(ui.SaveButton, SIGNAL(released()), this, SLOT(save_xml()));
	connect(ui.LoadButton, SIGNAL(released()), this, SLOT(load_xml()));
}

void Tool::update()
{
	glm::vec3 pos = scene->get_active_camera()->get_position();
	
	ui.camera_x->setText(QString::number(pos.x));
	ui.camera_y->setText(QString::number(pos.y));
	ui.camera_z->setText(QString::number(pos.z));
}

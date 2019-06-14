#pragma once
#include <rapidxml.hpp>
#include <string>
#include <vector>
#include "Linkage.hpp"


using namespace rapidxml;

namespace parser
{

	struct Directional_Light_Struct
	{

		float direction[3];
		float color[3];
		float ambient;
		float intensity;
		float specular;

	};

	struct Point_Light_Struct
	{
		float position[3];
		float range;

		float color[3];
		float ambient;
		float intensity;
		float specular;

	};

	class PARSER_MIGUEL_API ParserXML
	{

	public:
		ParserXML() {};
		void load_xml(std::string path, std::vector<Point_Light_Struct*>* points, std::vector<Directional_Light_Struct*>* directionals);
		Point_Light_Struct* parse_point_light(xml_node< > * class_tag);
		Directional_Light_Struct* parse_directional_light(xml_node< > * class_tag);

		void write_xml(std::string path, std::vector<Point_Light_Struct*> points, std::vector<Directional_Light_Struct*> directionals);

	};


}

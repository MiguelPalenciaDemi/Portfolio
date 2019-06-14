/**
 * @file Shader_List.hpp
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
#include <string>


namespace render
{
	static const std::string default_vertex_shader_code =
		"#version 330 \n"
		"uniform mat4 model_matrix;"
		"uniform mat4 projection_matrix;"
		"uniform mat4 view_matrix;"
		
		
		
		""
		"layout (location = 0) in vec3 vertex_coordinates;"
		"layout (location = 1) in vec3 normal_coordinates;"
		"layout (location = 2) in vec2 vertex_texture_uv;"
		""
		"out vec2 TextCoord;"
		"out vec3 Normal;"
		"out vec3 coord;"
		"out vec3 VectorLight;"
	
		//"out vec3 Color;"
		"void main()"
		"{"
		"    vec4 coordinates = vec4(vertex_coordinates,1.0f);"
		/*"    coordinates.x    = coordinates.x * 0.5;"
		"    coordinates.y    = coordinates.y * 0.5;"
		"    coordinates.z    = coordinates.z * 0.5;"*/
		"    gl_Position      = projection_matrix * view_matrix *model_matrix* coordinates;"
		"    TextCoord        = vertex_texture_uv;"
		"    Normal			  = mat3(transpose(inverse(model_matrix)))*normal_coordinates;"
		"    VectorLight	  = vec3(model_matrix * vec4(vertex_coordinates, 1.0));"
		"    coord			  = vertex_coordinates;	"	
		"}";

	static const std::string default_fragment_shader_code =

		"#version 330 \n"

		//Light
		"struct Directional_Light"
		"{"
		"	vec3 direction;"
		//"	vec3 position;"
		"	vec3 color;"
		"	float ambient;"
		"	float specular;"
		"};"

		"struct Point_Light"
		"{"		
		"	vec3 position;"
		"	vec3 color;"
		"	float ambient;"
		"	float specular;"		
		"	float constant;"
		"	float linear;"
		"	float quadratic;"
		"	int turn_on;"

		"};"

		"struct Light"
		"{"
		"	vec3 position;"
		"	vec3 color;"
		"};"
		
		"const int MAX_POINT_LIGHTS = 20;"
		"uniform Point_Light point_lights[MAX_POINT_LIGHTS];"
		"uniform Light light;"
		"uniform Directional_Light directional_light;"

		
		"uniform float intensity_light;"
		//Camera
		"uniform vec3 camera_position;"

		//Scene
		"uniform float ambient_light;"
		"uniform float opacity;"
		
		"uniform int number_of_point_lights;"



		//Texture
		"uniform sampler2D our_texture;"
		"in vec2 TextCoord;"
		"in vec3 Normal;"
		"in vec3 VectorLight;"
		//"in vec3 Color;"
		"out vec4 fragment_color;"

		//Esta funciona
		"vec3 calculate_directional(Directional_Light light,vec3 normal, vec3 view_dir)"
		"{"
		"	 vec3 tex = vec3(texture(our_texture,TextCoord));"

		//"	 vec3 ambient = tex *directional_light.ambient;"

		"	 vec3 lightDir = normalize(light.direction); "
		//"	 vec4 color_texture = texture(our_texture,TextCoord);"
		"	 float diff = max(dot(normal, lightDir), 0.0);"
		"	 vec3 diffuse = light.color * diff;"

		//"	 vec3 viewDir = normalize(camera_position - VectorLight);"
		"	 vec3 reflectDir = reflect(lightDir, normal);"
		"	 float spec = pow(max(dot(view_dir, reflectDir), 0.0), 32);"

		"	 vec3 specular = light.specular * spec * light.color;  "
		"	 vec3 result = diffuse + specular + light.ambient*light.color;"
		"	 return result ;"

		
		"};"

		"vec3 calculate_point(Point_Light light, vec3 normal, vec3 fragPos, vec3 view_dir)"
		"{"
		"	 vec3 tex = vec3(texture(our_texture,TextCoord));"
		"	 vec3 lightDir = normalize(light.position - fragPos ); "		
		"	 float diff = max(dot(normal, lightDir), 0.0);"
		"	 vec3 diffuse = light.color * diff;"

		
		"	 vec3 reflectDir = reflect(lightDir, normal);"
		"	 float spec = pow(max(dot(view_dir, reflectDir), 0.0), 32);"
		"	 float distance = length(light.position - fragPos);"
		"	 float attenuation = light.turn_on / (light.constant + light.linear * distance + light.quadratic * (distance * distance));"

		//"	 vec3 ambient = light.ambient*light.color;"
		"	 vec3 ambient = light.ambient*light.color*attenuation;  "
		"	 vec3 specular = light.specular * spec * light.color*attenuation;  "
		
		"	 diffuse *= attenuation;  "
		"	 vec3 result = diffuse + specular + ambient;"	
		
		"	 return result;"
		"};"

		"void main()"
		"{"
		"	 vec3 norm = normalize(Normal);"		
		"	 vec3 viewDir = normalize(VectorLight-camera_position);"
		"	 vec3 output_value = vec3(0,0,0);"
			//Directional
		"	 output_value += calculate_directional(directional_light,norm, viewDir);"
	
			//Point Light
		"	 for (int i = 0; i < number_of_point_lights; i++)"
			"		output_value += calculate_point(point_lights[i], norm, VectorLight, viewDir);"

		"	 vec3 color_texture = vec3(texture(our_texture,TextCoord));"		
		"    color_texture *= intensity_light*directional_light.color;"
	//	"    fragment_color = vec4(1,1,1, 1.0);"	
		"    fragment_color = vec4(output_value*color_texture, 1.0);"	
		"    fragment_color.a = 1;"
		
		"}";


	//Este funciona. Es una pointLight
	//static const std::string default_fragment_shader_code =

	//	"#version 330 \n"

	//	//Light
	//	"struct Light"
	//	"{"
	//	"	vec3 position;"
	//	"	vec3 color;"
	//	"};"
	//	"uniform Light light;"
	//	"uniform float intensity_light,specular_light;"
	//	//Camera
	//	"uniform vec3 camera_position;"

	//	//Scene
	//	"uniform float ambient_light;"


	//	//Texture
	//	"uniform sampler2D our_texture;"
	//	"in vec2 TextCoord;"
	//	"in vec3 Normal;"
	//	"in vec3 VectorLight;"
	//	//"in vec3 Color;"
	//	"out vec4 fragment_color;"




	//	"void main()"
	//	"{"
	//	"	 vec3 norm = normalize(Normal);"
	//	"	 vec3 lightDir = normalize(light.position - VectorLight); "
	//	"	 vec4 color_texture = texture(our_texture,TextCoord);"
	//	"	 float diff = max(dot(norm, lightDir), 0.0);"
	//	"	 vec3 diffuse = light.color * diff;"

	//	"	 vec3 viewDir = normalize(camera_position - VectorLight);"
	//	"	 vec3 reflectDir = reflect(-lightDir, norm);"

	//	"	 float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);"
	//	"	 vec3 specular = specular_light * spec * light.color;  "
	//	"	 vec3 result = diffuse + specular + (ambient_light*light.color);"

	//	//"	 vec3 diffuse = light.color * diff;"		
	//	"	 float r = intensity_light*result.r + color_texture.r*(1-intensity_light);"
	//	"	 float g = intensity_light*result.g + color_texture.g*(1-intensity_light);"
	//	"	 float b = intensity_light*result.b + color_texture.b*(1-intensity_light);"

	//	"    fragment_color = vec4(r,g,b, 1.0);"
	//	//"    fragment_color = texture(our_texture,TextCoord)*vec4(light.color, 1.0);"
	//	"    fragment_color.a = 1;"
	//	"}";


	//static const std::string default_fragment_shader_code =

	//	"#version 330 \n"

	//	//Light
	//	"uniform float intensity_light,specular_light;"
	//	"uniform vec3 color_light,position_light;"

	//	//Camera
	//	"uniform vec3 camera_position;"

	//	//Scene
	//	"uniform float ambient_light;"


	//	//Texture
	//	"uniform sampler2D our_texture;"
	//	"in vec2 TextCoord;"
	//	"in vec3 Normal;"
	//	"in vec3 VectorLight;"
	//	//"in vec3 Color;"
	//	"out vec4 fragment_color;"




	//	"void main()"
	//	"{"
	//	"	 vec3 norm = normalize(Normal);"
	//	"	 vec3 lightDir = normalize(position_light - VectorLight); "
	//	"	 vec4 color_texture = texture(our_texture,TextCoord);"
	//	"	 float diff = max(dot(norm, lightDir), 0.0);"
	//	"	 vec3 diffuse = color_light * diff;"

	//	"	 vec3 viewDir = normalize(camera_position - VectorLight);"
	//	"	 vec3 reflectDir = reflect(-lightDir, norm);"

	//	"	 float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);"
	//	"	 vec3 specular = specular_light * spec * color_light;  "
	//	"	 vec3 result = diffuse + specular + (ambient_light*color_light);"

	//	//"	 vec3 diffuse = color_light * diff;"		
	//	"	 float r = intensity_light*result.r + color_texture.r*(1-intensity_light);"
	//	"	 float g = intensity_light*result.g + color_texture.g*(1-intensity_light);"
	//	"	 float b = intensity_light*result.b + color_texture.b*(1-intensity_light);"

	//	"    fragment_color = vec4(r,g,b, 1.0);"
	//	//"    fragment_color = texture(our_texture,TextCoord)*vec4(color_light, 1.0);"
	//	"    fragment_color.a = 1;"
	//	"}";

	//

	static const std::string default_fragment_shader_cube_code =

		"#version 330 \n"
		"in vec3 texture_cordinates;"
		//"in vec3 textureDir;"
		"out vec4 fragment_color;"
		"uniform samplerCube  our_texture;"
		"uniform float  opacity;"

		"void main()"
		"{"
		"    fragment_color = texture(our_texture,texture_cordinates);"
		"    fragment_color.a = opacity;"
		"}";

	static const std::string default_vertex_shader_cube_code =
		"#version 330 \n"
		
		"uniform mat4 projection_matrix;"
		"uniform mat4 view_matrix;"
		
		""
		"layout (location = 0) in vec3 vertex_coordinates;"
		"out vec3 texture_cordinates;"
		""
		"void main()"
		"{"
		//"    texture_cordinates = vertex_coordinates;"
		"    texture_cordinates = vec3(vertex_coordinates.x,-vertex_coordinates.y,vertex_coordinates.z);"
		//"    gl_Position      = vec4(vertex_coordinates,1.0f);"
		"    gl_Position      = projection_matrix * view_matrix * vec4(vertex_coordinates,1.0f);"
	//	"    gl_Position      = projection_matrix * view_matrix * vec4(vertex_coordinates,1.0f);"
		"}";

	static const std::string vertex_shader_heightmap =
		"#version 330 \n"
		"uniform mat4 model_matrix;"
		"uniform mat4 projection_matrix;"
		"uniform mat4 view_matrix;"
		//"uniform sampler2D diffuse_texture;"
		"uniform sampler2D heightmap_texture;"
		
		""
		"layout (location = 0) in vec3 vertex_coordinates;"
		"layout (location = 1) in vec3 normal_coordinates;"
		"layout (location = 2) in vec2 vertex_texture_uv;"
		""
		" out vec3 coord;"
		"out vec2 TextCoord;"
		"out vec3 Normal;"
		
		"out vec3 VectorLight;"
		
		"void main()"
		"{"
		"	 vec4 texture_color = texture(heightmap_texture,vertex_texture_uv);"
		"	 float grayscale  = (texture_color.r+texture_color.g+texture_color.b)/3;"
		"    vec4 coordinates = vec4(vertex_coordinates,1.0f);"
		"    coordinates.x    = coordinates.x * 3;"
		"    coordinates.y    = coordinates.y + grayscale*120;"
		"    coordinates.z    = coordinates.z * 3;"

		
		"    gl_Position      = projection_matrix * view_matrix *model_matrix* coordinates;"
		"	 TextCoord		  = vertex_texture_uv; "
		"    Normal			  = mat3(transpose(inverse(model_matrix)))*normal_coordinates;"
		"    VectorLight	  = vec3(model_matrix * vec4(vertex_coordinates, 1.0));"

		"    coord		      = vertex_coordinates;"
		"}";



	static const std::string vertex_shader_water_code =
		"#version 330 \n"
		"uniform mat4 model_matrix;"
		"uniform mat4 projection_matrix;"
		"uniform mat4 view_matrix;"
		"uniform float time, distance, height,speed,opacity;"
		""
		"layout (location = 0) in vec3 vertex_coordinates;"
		"layout (location = 1) in vec3 normal_coordinates;"
		"layout (location = 2) in vec2 vertex_texture_uv;"
		""

		"out vec3 coord;"
		"out vec2 TextCoord;"
		"out vec3 Normal;"
		"out vec3 VectorLight;"

		"void main()"
		"{"
		"    vec4 coordinates = vec4(vertex_coordinates,1.0f);"
		//"    coordinates.x    = coordinates.x * 0.5;"
		//"    coordinates.y    = coordinates.y * 0.5;"
		//"    coordinates.z    = coordinates.z * 0.5;"

		"    coordinates.y    = sin((coordinates.x + speed*time) / distance)*height;"
		"    gl_Position      = projection_matrix * view_matrix *model_matrix* coordinates;"		
		"	 TextCoord		  = vertex_texture_uv; "
		"    Normal			  = mat3(transpose(inverse(model_matrix)))*normal_coordinates;"
		"    VectorLight	  = vec3(model_matrix * vec4(vertex_coordinates, 1.0));"
		"    coord		      = vertex_coordinates;"
		"}";

	static const std::string fragment_shader_water_code =
		"#version 330 \n"
		"out vec4 fragment_color;"
		"uniform float opacity;"
		"void main()"
		"{"
		"    fragment_color = vec4(0.0, 0.0, 1.0, opacity);"
		"}";

	static const std::string fragment_shader_water_circle_code =

		"#version 330 \n"
		
		//Light
		"struct Directional_Light"
		"{"
		"	vec3 direction;"
		//"	vec3 position;"
		"	vec3 color;"
		"	float ambient;"
		"	float specular;"
		"};"
		
		"struct Point_Light"
		"{"
		"	vec3 position;"
		"	vec3 color;"
		"	float ambient;"
		"	float specular;"
		"	float constant;"
		"	float linear;"
		"	int turn_on;"
		"	float quadratic;"
		
		"};"
		
		"struct Light"
		"{"
		"	vec3 position;"
		"	vec3 color;"
		"};"
		
		"const int MAX_POINT_LIGHTS = 20;"
		"uniform Point_Light point_lights[MAX_POINT_LIGHTS];"
		
		"uniform Directional_Light directional_light;"
		
		
		"uniform float intensity_light;"
		//Camera
		"uniform vec3 camera_position;"
		
		//Scene
		"uniform float ambient_light;"
		"uniform float opacity;"
		
		"uniform int number_of_point_lights;"
		
		
		
		//Texture
		//"uniform sampler2D our_texture;"
		"uniform vec3 color;"
		"uniform float radius;"
		"in vec2 TextCoord;"
		"in vec3 Normal;"
		"in vec3 coord;"
		"in vec3 VectorLight;"
		//"in vec3 Color;"
		"out vec4 fragment_color;"
		
		//Esta funciona
		"vec3 calculate_directional(Directional_Light light,vec3 normal, vec3 view_dir)"
		"{"
		//"	 vec3 tex = color;"
		
		//"	 vec3 ambient = tex *directional_light.ambient;"
		
		"	 vec3 lightDir = normalize(-light.direction); "
		//"	 vec4 color_texture = texture(our_texture,TextCoord);"
		"	 float diff = max(dot(normal, lightDir), 0.0);"
		"	 vec3 diffuse = light.color * diff;"
		
		//"	 vec3 viewDir = normalize(camera_position - VectorLight);"
		"	 vec3 reflectDir = reflect(lightDir, normal);"
		"	 float spec = pow(max(dot(view_dir, reflectDir), 0.0), 32);"
		
		"	 vec3 specular = light.specular * spec * light.color;  "
		"	 vec3 result = diffuse + specular + light.ambient*light.color;"
		"	 return result ;"
		
		
		"};"
		
		"vec3 calculate_point(Point_Light light, vec3 normal, vec3 fragPos, vec3 view_dir)"
		"{"
		
		"	 vec3 lightDir = normalize(light.position - fragPos ); "
		"	 float diff = max(dot(normal, lightDir), 0.0);"
		"	 vec3 diffuse = light.color * diff;"
		
		
		"	 vec3 reflectDir = reflect(lightDir, normal);"
		"	 float spec = pow(max(dot(view_dir, reflectDir), 0.0), 32);"
		"	 float distance = length(light.position - fragPos);"
		"	 float attenuation = light.turn_on / (light.constant + light.linear * distance + light.quadratic * (distance * distance));"
		
		"	 vec3 ambient = light.ambient*light.color*attenuation;  "
		"	 vec3 specular = light.specular * spec * light.color*attenuation;  "
		
		"	 diffuse *= attenuation;  "
		"	 vec3 result = diffuse + specular + ambient;"
		
		"	 return result;"
		"};"
		
		"void main()"
		"{"
		
		"	 vec3 norm = normalize(Normal);"
		"	 vec3 viewDir = normalize(VectorLight-camera_position);"
		"	 vec3 output_value = vec3(0,0,0);"
		//Directional
		"	 output_value += calculate_directional(directional_light,norm, viewDir);"
		
		//Point Light
		"	 for (int i = 0; i < number_of_point_lights; i++)"
		"		output_value += calculate_point(point_lights[i], norm, VectorLight, viewDir);"
		
		"	 vec3 color_texture = color;"
		
		"    color_texture *= intensity_light*directional_light.color;"
		
		"    fragment_color = vec4(output_value*color_texture,opacity);"//Con opacidad no va
		"    fragment_color.a = coord.x * coord.x + coord.z * coord.z < radius*radius ? opacity : 0;"//Para hacer circulo		
		"}";

		static const std::string fragment_shader_no_texture_code =

			"#version 330 \n"

			//Light
			"struct Directional_Light"
			"{"
			"	vec3 direction;"
			//"	vec3 position;"
			"	vec3 color;"
			"	float ambient;"
			"	float specular;"
			"	float intensity;"
			"};"

			"struct Point_Light"
			"{"
			"	vec3 position;"
			"	vec3 color;"
			"	float ambient;"
			"	float specular;"
			"	float intensity;"
			"	float constant;"
			"	float linear;"
			"	float quadratic;"
			"	int turn_on;"

			"};"

			"struct Light"
			"{"
			"	vec3 position;"
			"	vec3 color;"
			"};"

			"const int MAX_POINT_LIGHTS = 20;"
			"uniform Point_Light point_lights[MAX_POINT_LIGHTS];"

			"uniform Directional_Light directional_lights[MAX_POINT_LIGHTS];"


			//"uniform float intensity_light;"
			//Camera
			"uniform vec3 camera_position;"

			//Scene
			"uniform float ambient_light;"
			"uniform float opacity;"

			"uniform int number_of_point_lights;"
			"uniform int number_of_directional_lights;"



			//Texture
			//"uniform sampler2D our_texture;"
			"uniform vec3 color;"
			"uniform float radius;"
			"in vec2 TextCoord;"
			"in vec3 Normal;"
			"in vec3 coord;"
			"in vec3 VectorLight;"
			//"in vec3 Color;"
			"out vec4 fragment_color;"

			//Esta funciona
			"vec3 calculate_directional(Directional_Light light,vec3 normal, vec3 view_dir)"
			"{"
		

			"	 vec3 lightDir = normalize(light.direction); "
			//"	 vec4 color_texture = texture(our_texture,TextCoord);"
			"	 float diff = max(dot(normal, lightDir), 0.0);"
			"	 vec3 diffuse = light.color * diff;"

			//"	 vec3 viewDir = normalize(camera_position - VectorLight);"
			"	 vec3 reflectDir = reflect(lightDir, normal);"
			"	 float spec = pow(max(dot(view_dir, reflectDir), 0.0), 32);"

			"	 vec3 specular = light.specular * spec * light.color;  "
			"	 vec3 result = (diffuse + specular + light.ambient*light.color)*light.intensity;"
			"	 return result ;"


			"};"

			"vec3 calculate_point(Point_Light light, vec3 normal, vec3 fragPos, vec3 view_dir)"
			"{"

			"	 vec3 lightDir = normalize(light.position - fragPos ); "
			"	 float diff = max(dot(normal, lightDir), 0.0);"
			"	 vec3 diffuse = light.color * diff*light.intensity;"


			"	 vec3 reflectDir = reflect(lightDir, normal);"
			"	 float spec = pow(max(dot(view_dir, reflectDir), 0.0), 32);"
			"	 float distance = length(light.position - fragPos);"
			"	 float attenuation = light.turn_on / (light.constant + light.linear * distance + light.quadratic * (distance * distance));"

			"	 vec3 ambient = light.ambient*light.color*attenuation;  "
			"	 vec3 specular = light.specular * spec * light.color*attenuation;  "

			"	 diffuse *= attenuation;  "
			"	 vec3 result = diffuse + specular + ambient;"

			"	 return result;"
			"};"

			"void main()"
			"{"

			"	 vec3 norm = normalize(Normal);"
			"	 vec3 viewDir = normalize(VectorLight-camera_position);"
			"	 vec3 output_value = vec3(0,0,0);"
			//Directional
			"	 for (int i = 0; i < number_of_directional_lights; i++)"
				"		output_value += calculate_directional(directional_lights[i],norm, viewDir);"

			//Point Light
			"	 for (int i = 0; i < number_of_point_lights; i++)"
			"		output_value += calculate_point(point_lights[i], norm, VectorLight, viewDir);"

			"	 vec3 color_texture = color;"
			//"    color_texture *= intensity_light*directional_light.color;"
			"    fragment_color = vec4(output_value*color_texture, opacity);"		
			"}";
	
}






//static const std::string fragment_shader_no_texture_code =
//
//"#version 330 \n"
//
////Light
//"struct Directional_Light"
//"{"
//"	vec3 direction;"
////"	vec3 position;"
//"	vec3 color;"
//"	float ambient;"
//"	float specular;"
//"};"
//
//"struct Point_Light"
//"{"
//"	vec3 position;"
//"	vec3 color;"
//"	float ambient;"
//"	float specular;"
//"	float constant;"
//"	float linear;"
//"	float quadratic;"
//"	int turn_on;"
//
//"};"
//
//"struct Light"
//"{"
//"	vec3 position;"
//"	vec3 color;"
//"};"
//
//"const int MAX_POINT_LIGHTS = 20;"
//"uniform Point_Light point_lights[MAX_POINT_LIGHTS];"
//
//"uniform Directional_Light directional_light;"
//
//
//"uniform float intensity_light;"
////Camera
//"uniform vec3 camera_position;"
//
////Scene
//"uniform float ambient_light;"
//"uniform float opacity;"
//
//"uniform int number_of_point_lights;"
//
//
//
////Texture
////"uniform sampler2D our_texture;"
//"uniform vec3 color;"
//"uniform float radius;"
//"in vec2 TextCoord;"
//"in vec3 Normal;"
//"in vec3 coord;"
//"in vec3 VectorLight;"
////"in vec3 Color;"
//"out vec4 fragment_color;"
//
////Esta funciona
//"vec3 calculate_directional(Directional_Light light,vec3 normal, vec3 view_dir)"
//"{"
//
//
//"	 vec3 lightDir = normalize(light.direction); "
////"	 vec4 color_texture = texture(our_texture,TextCoord);"
//"	 float diff = max(dot(normal, lightDir), 0.0);"
//"	 vec3 diffuse = light.color * diff;"
//
////"	 vec3 viewDir = normalize(camera_position - VectorLight);"
//"	 vec3 reflectDir = reflect(lightDir, normal);"
//"	 float spec = pow(max(dot(view_dir, reflectDir), 0.0), 32);"
//
//"	 vec3 specular = light.specular * spec * light.color;  "
//"	 vec3 result = diffuse + specular + light.ambient*light.color;"
//"	 return result ;"
//
//
//"};"
//
//"vec3 calculate_point(Point_Light light, vec3 normal, vec3 fragPos, vec3 view_dir)"
//"{"
//
//"	 vec3 lightDir = normalize(light.position - fragPos ); "
//"	 float diff = max(dot(normal, lightDir), 0.0);"
//"	 vec3 diffuse = light.color * diff;"
//
//
//"	 vec3 reflectDir = reflect(lightDir, normal);"
//"	 float spec = pow(max(dot(view_dir, reflectDir), 0.0), 32);"
//"	 float distance = length(light.position - fragPos);"
//"	 float attenuation = light.turn_on / (light.constant + light.linear * distance + light.quadratic * (distance * distance));"
//
//"	 vec3 ambient = light.ambient*light.color*attenuation;  "
//"	 vec3 specular = light.specular * spec * light.color*attenuation;  "
//
//"	 diffuse *= attenuation;  "
//"	 vec3 result = diffuse + specular + ambient;"
//
//"	 return result;"
//"};"
//
//"void main()"
//"{"
//
//"	 vec3 norm = normalize(Normal);"
//"	 vec3 viewDir = normalize(VectorLight-camera_position);"
//"	 vec3 output_value = vec3(0,0,0);"
////Directional
//"	 output_value += calculate_directional(directional_light,norm, viewDir);"
//
////Point Light
//"	 for (int i = 0; i < number_of_point_lights; i++)"
//"		output_value += calculate_point(point_lights[i], norm, VectorLight, viewDir);"
//
//"	 vec3 color_texture = color;"
//"    color_texture *= intensity_light*directional_light.color;"
//"    fragment_color = vec4(output_value*color_texture, opacity);"
//"}";
//
//}

//Code by Miguel Palencia May 2019
#pragma once
#include"../header/Texture_Cubemap.hpp"
#include"../header/Color_Buffer_Rgba8888.hpp"
#include <vector>


namespace render
{
	Texture_Cubemap::Texture_Cubemap(const char * path)
	{
		// Load all the bitmaps per faces

		std::vector< std::shared_ptr< Texture_Color > > texture_faces;

		for (GLuint texture_index = 0; texture_index < 6 ; ++texture_index)
		{
			
			std::string path_final = path;
			path_final.append(std::to_string(texture_index));
			path_final.append(".tga");
			texture_faces.push_back(load_texture(path_final.c_str()));

			if (!texture_faces[texture_index])
			{
				return;
			}

		}

		
		//Create Texture Object

		glEnable(GL_TEXTURE_CUBE_MAP);

		glGenTextures(1, &id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, id);


		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);



		static const GLenum texture_target[] =
		{
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
		};

		for(GLuint index = 0; index<texture_faces.size();++index)
		{
			Texture_Color & texture = *texture_faces[index];
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_RGBA, texture.get_width(), texture.get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.colors());
		
		}
		
	}

	void Texture_Cubemap::bind(int index)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	}
}
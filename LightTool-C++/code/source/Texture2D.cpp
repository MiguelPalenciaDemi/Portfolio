//Code by Miguel Palencia May 2019
#pragma once
#include "../header/Texture2D.hpp"
#include "../header/Color_Buffer_Rgba8888.hpp"

namespace render
{



	Texture2D::Texture2D(const char * path)
	{
		std::shared_ptr<Texture_Color> texture = load_texture(path);


		if (texture != nullptr)
		{
			//Generate the texture and set up the parameters
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


			//Upload the TexInfo to the Video memory
			glTexImage2D
			(
				GL_TEXTURE_2D,
				0,
				GL_RGBA,
				texture->get_width(),
				texture->get_height(),
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				texture->colors()
			);

		}
	}

	void Texture2D::bind(int index)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, id);
	}

}
//Code by Miguel Palencia May 2019
#pragma once 

#include "../header/Texture.hpp"
#include "../header/Color_Buffer_Rgba8888.hpp"

namespace render
{

	std::map<std::string, std::shared_ptr<Texture_Color>> Texture::textures_loaded;

	

	std::shared_ptr<Texture_Color> Texture::load_texture(const char * path)
	{
		std::shared_ptr< Texture_Color > texture;
		if(!textures_loaded[path])
		{
		
		
			tga_image loaded_image;

			if (tga_read(&loaded_image, path) == TGA_NOERR)
			{

				// If it could be loaded, create a buffer
				texture.reset(new Texture_Color(loaded_image.width, loaded_image.height));

				// Convert to RGBA8888
				tga_convert_depth(&loaded_image, texture->bits_per_color());
				tga_swap_red_blue(&loaded_image);

				// Copy to the texture:
				Texture_Color::Color * loaded_image_pixels = reinterpret_cast< Texture_Color::Color * >(loaded_image.image_data);
				Texture_Color::Color * loaded_image_pixels_end = loaded_image_pixels + loaded_image.width * loaded_image.height;
				Texture_Color::Color * image_buffer_pixels = texture->colors();

				while (loaded_image_pixels <  loaded_image_pixels_end)
				{
					*image_buffer_pixels++ = *loaded_image_pixels++;
				}

				tga_free_buffers(&loaded_image);
			}

			textures_loaded[path] = texture;
				
		}		
			


		return textures_loaded[path];
		
	}

}


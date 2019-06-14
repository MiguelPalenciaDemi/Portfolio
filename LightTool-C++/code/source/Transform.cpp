//Miguel Palencia de Miguel 2/03/2019
#pragma once
#include "../header/Transform.hpp"
#include <iostream>

namespace render
{
	void Transform::set_position(float x, float y, float z)
	{
		local_transform = translate(local_transform, -translation);//Reset the position to the 0,0,0
		local_transform = translate(local_transform, vec3(x, y, z));
		translation = vec3(x, y, z);
		update_position();
	};

	mat4 Transform::update_position()
	{		

		if (updated) return transform; 

		if (parent)
			transform = parent->update_position() * local_transform ;
		else
			transform = local_transform; 


		updated = true;

		return transform;
	}

}

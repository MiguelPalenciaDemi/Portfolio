/**
 * @file Shape.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-31
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once 

#include <btBulletDynamicsCommon.h>
#include <memory>


namespace render
{
	/**
	 * @brief 
	 * 
	 */
	__declspec(align(16)) class Shape
	{
		btScalar mass;
		btVector3 inertia;
		std::shared_ptr<btCollisionShape> shape;

	public:
		Shape(btScalar width, btScalar length, btScalar height,btScalar mass,btVector3 inertia):mass(mass),inertia(inertia)
		{
			shape.reset(new btBoxShape(btVector3{ width,height,length }));

		}

		Shape(btScalar radius, btScalar mass, btVector3 inertia) :mass(mass), inertia(inertia)
		{ shape.reset(new btSphereShape(radius)); }

		btScalar get_mass() { return mass; }
		btVector3 get_inetia() { return inertia; }
		std::shared_ptr<btCollisionShape> get_shape() { return shape; }
		void calculate_inertia() { shape->calculateLocalInertia( mass, inertia); }

		void* operator new(size_t i)
		{
			return _mm_malloc(i, 16);
		}

		void operator delete(void* p)
		{
			_mm_free(p);
		}
	};

}
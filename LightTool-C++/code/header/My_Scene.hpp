/**
 * @file My_Scene.hpp
 * @author Miguel Palencia (miguelpalenciademi@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once
#include "Scene.hpp"
#include "OpenGL.hpp"
#include "Windmill.hpp"
#include "Joints.hpp"
#include "Catapult.hpp"
#include "Platform.hpp"
#include "Door.hpp"


namespace render
{
	/**
	 * @brief Custom Scene
	 * 
	 */
	__declspec(align(16)) class My_Scene:public Scene
	{	
		/**
		 * @brief Catapult character
		 * 
		 */
		std::shared_ptr<Catapult> character;

		/**
		 * @brief Platform
		 * 
		 */
		std::shared_ptr<Platform> platform;

		/**
		 * @brief Gate
		 * 
		 */
		std::shared_ptr<Door> gate;
		
		/**
		 * @brief Light catapult
		 * 
		 */
		Point_Light* catapult_light;

		/**
		 * @brief light key
		 * 
		 */
		Point_Light* key_light;

		/**
		 * @brief 
		 * 
		 */
		bool key_picked = false;
	public:

		/**
		 * @brief Construct a new My_Scene object
		 * 
		 * @param width 
		 * @param height 
		 */
		My_Scene(std::size_t width, std::size_t height);

		/**
		 * @brief update function
		 * 
		 * @param time 
		 */
		void update(float time) override;
		
		/**
		 * @brief Check all the collision
		 * 
		 */
		void check_collision();
		
		/**
		 * @brief Create a platform object
		 * 
		 * @param name 
		 * @param path 
		 * @param position 
		 * @param size 
		 * @param type 
		 * @return RigidBody* 
		 */
		RigidBody* create_platform(std::string name, std::string path, btVector3 position, btVector3 size, RigidBody::RigidBody_Type type);

		/**
		 * @brief Create a rock object
		 * 
		 */
		void create_rock();

		/**
		 * @brief Get the character object
		 * 
		 * @return std::shared_ptr<Catapult> 
		 */
		std::shared_ptr<Catapult> get_character() { return character; }


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
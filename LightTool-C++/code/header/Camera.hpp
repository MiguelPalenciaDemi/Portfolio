/**
 * @file Camera.hpp
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



namespace render
{
	/**
	 * @brief Camera class
	 * 
	 */
	class Camera
	{
		private: 
			
			/**
			 * @brief Field of view
			 * 
			 */
			float fov;
			/**
			 * @brief Aspect ratio
			 * 
			 */
			float aspect_ratio;
			/**
			 * @brief Distance to the near plane
			 * 
			 */
			float near_plane;
			/**
			 * @brief Distance to the far plane
			 * 
			 */
			float far_plane;
			/**
			 * @brief X Rotation
			 * 
			 */
			float yaw;
			/**
			 * @brief Y rotation
			 * 
			 */
			float pitch;
			/**
			 * @brief Camera position
			 * 
			 */
			glm::vec3 camera_position;
			/**
			 * @brief Point that camera is looking at
			 * 
			 */
			glm::vec3 camera_front;
			
			/**
			 * @brief world vector up
			 * 
			 */
			glm::vec3 up;
			
			/**
			 * @brief Right vector 
			 * 
			 */
			glm::vec3 camera_right;
			/**
			 * @brief Up vector
			 * 
			 */
			glm::vec3 camera_up;
		
		public:
		/**
		 * @brief Construct a new Camera object
		 * 
		 * @param _fov 
		 * @param _aspect_ratio 
		 * @param _near 
		 * @param _far 
		 */
			Camera(float _fov, float _aspect_ratio, float _near, float _far):fov(_fov),aspect_ratio(_aspect_ratio),near_plane(_near),far_plane(_far)
			{
				yaw 			 = -90;
				pitch 			 = 0;
				camera_position  = glm::vec3(0.0f, 0.0f, 0.0f);
				camera_front     = glm::vec3(0.0f, 0.0f, -1.0f);
				up 				 = glm::vec3(0.0f, 1.0f, 0.0f);  
			
				update_vectors();
			}

			/**
			 * @brief Construct a new Camera object
			 * 
			 */
			Camera() {};

			/**
			 * @brief Destroy the Camera object
			 * 
			 */
			~Camera() {}

			/**
			 * @brief Set the position object
			 * 
			 * @param x 
			 * @param y 
			 * @param z 
			 */
			void set_position(float x, float y , float z)
			{
				camera_position = glm::vec3(x, y, z);
			}

			/**
			 * @brief Get the position object
			 * 
			 * @return glm::vec3 
			 */
			glm::vec3 get_position() { return camera_position; }
			void set_position(glm::vec3 _position)
			{
				camera_position = _position;
			}

			/**
			 * @brief Get the projection matrix object
			 * 
			 * @return glm::mat4 
			 */
			glm::mat4 get_projection_matrix() { return glm::perspective(glm::radians(fov), aspect_ratio, near_plane, far_plane); }

			/**
			 * @brief Get the view matrix object
			 * 
			 * @return glm::mat4 
			 */
			glm::mat4 get_view_matrix()
			{ 
				return glm::lookAt(camera_position, camera_position + camera_front, camera_up);
			}
			glm::mat4 get_view_matrix_origin()
			{
				return glm::lookAt(glm::vec3(0, 0, 0), camera_front, camera_up);
				
			}

			/**
			 * @brief Move camera down
			 * 
			 * @param speed 
			 */
			void move_down(float speed){ camera_position -= speed * camera_front; }

			/**
			 * @brief Move camera up
			 * 
			 * @param speed 
			 */
			void move_up(float speed){ camera_position += speed * camera_front; }

			/**
			 * @brief  Move camera left
			 * 
			 * @param speed 
			 */
			void move_left(float speed){ camera_position -= glm::normalize(glm::cross(camera_front, camera_up)) * speed; }

			/**
			 * @brief  Move camera right
			 * 
			 * @param speed 
			 */
			void move_rigth(float speed){ camera_position += glm::normalize(glm::cross(camera_front, camera_up)) * speed; }

			/**
			 * @brief Rotate the camera
			 * 
			 * @param y 
			 * @param x 
			 */
			void rotate(float y, float x)
			{
				
				yaw = glm::mod(yaw + x, 360.0f);
				
				pitch += y;

				if (pitch > 89.0f)
					pitch = 89.0f;
				if (pitch < -89.0f)
					pitch = -89.0f;

				update_vectors();
			
			}

			/**
			 * @brief update camera
			 * 
			 */
			void update() 
			{
				update_vectors();
				
			}
			
			/**
			 * @brief Update the vectors
			 * 
			 */
			void update_vectors ()
			{
				 
				glm::vec3 front;
				front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
				front.y = sin(glm::radians(pitch));
				front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
				camera_front = glm::normalize(front);
				
				camera_right = glm::normalize(glm::cross(camera_front, up));  
				camera_up = glm::normalize(glm::cross(camera_right, camera_front));
			}
	};


}



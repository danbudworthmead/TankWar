//\====

#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include "Utilities.h"
#include "LineRenderer.h"
#include "Enumerations.h"

struct GLFWwindow;

namespace UG{
	
	class Application
	{
	public:

		///
		/// @name Singleton Functions
		/// The following functions are the public accessors for creating, retrieving and 
		/// destroying an instance of the Application. Only one instance of the Application 
		/// can be created.  See: Design Patterns (Singleton)
		///
		/**@{**/
		/// Create and Instance of the Application
		///@param a_iWidth the width of the Application Window that is to be created
		///@param a_iHeight the height of the Application Window that is to be created
		///@param a_bFullscreen wheather or not the application is to be fullscreen, defaults to false (windowed)
		///@param a_pWindowTitle the name for the application window that is to be displayed
		///@return Returns an instance of the Application.
		static Application* Create(int a_iWidth, int a_iHeight, bool a_bFullscreen = false, const char* a_pWindowTitle = nullptr, int a_xPosition = 0, int a_yPosition = 0);
		///Gets and Instance of the Application
		///@return Returns an instance of the Applicationk, returns Null if no framework has been created
		static Application* GetInstance();
		///Destroys the current Application. Should be called on Termination of the application
		static void Destroy();
		/**@}**/

		bool	onCreate(int a_iWidth, int a_iHeight, bool a_bFullscreen = false, const char* a_pWindowTitle = nullptr, int a_xPosition = 0, int a_yPosition = 0);
		bool	process();
		void	destroy()	{ m_running = false; }

	public:

		GLFWwindow* GetWindow() { return m_window; }

		bool	IsPVMDirty() { return m_isPVMDirty;	}

		void	GetCameraMatrix(glm::mat4& a_cameraMatrix)const				{ a_cameraMatrix = m_CameraMatrix; }
		void	GetProjectionMatrix(glm::mat4& a_projectionMatrix)const		{ a_projectionMatrix = m_ProjectionMatrix; }
		void	GetViewMatrix(glm::mat4& a_viewMatrix) const				{ a_viewMatrix = m_ViewMatrix;  }

	private:
		//Due to this being a singelton object the constructor and destructor are private
		Application() : m_running(false) { }
		Application(Application& a_app){}
		virtual ~Application();

		static Application* m_Instance;

		GLFWwindow*		m_window;
		bool			m_running;

		char			m_ApplicationTitle[256];

		//Variables for Shaders and camera matrices
		GLuint m_ShaderID = 0;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_CameraMatrix;

		bool		m_isPVMDirty;
		//variable holding the time taken each frame
		float m_fDeltaTime;

	};


}//end namespace UG

#endif // __APPLICATION_H_

//////////////////////////////////////////////////////////////////////////
#define APPLICATION_ENTRY(appClass)									\
	int main(int a_argc, char* a_argv[])							\
	{																\
		UG::Application* app = new appClass();					\
		if (app->create(a_argc,a_argv) == true)						\
		{															\
			app->run();												\
			app->destroy();											\
		}															\
		else														\
		{															\
			/*UG::logError("Failed to setup application!\n");*/	\
		}															\
		delete app;													\
		return 0;													\
	}
//////////////////////////////////////////////////////////////////////////
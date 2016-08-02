//////////////////////////////////////////////////////////////////////////
//	Author:	Jamie Stewart
//	Date:	08/07/2015
//	Brief:	A font manager class for being in charge of various fonts etc
//////////////////////////////////////////////////////////////////////////
#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_
//////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <list>
#include <vector>

namespace UG
{
	//forwad declarations
	class Font;
	struct CharacterBillboard;
	struct FontVertex;

	//////////////////////////////////////////////////////////////////////////
	class FontManager
	{
	public:
		static FontManager* CreateInstance();
		static FontManager* GetInstance();
		static void			DestroyInstance();
	protected:
		FontManager();
		~FontManager();
		static FontManager*     m_pInstance;
	public:
		void                Update(float fTimeStep);
		void				Draw(unsigned int a_uiProgramID);
		void				DrawString(glm::vec4 v4Position, float a_fSize, glm::vec4 v4colour, const char* pBuffer);
		Font*               GetDebugFont();
		Font*               GetCurrentFont();

		void                AddFont(Font* pFont);
		Font*               AddFont(const char* pFontName);

		void                SetFont(Font* pFont);
		Font*               SetFont(const char* pFontName);

		void                RemoveFont(Font* pFont);
		void                RemoveFont(const char* pFontName);

	private:

		//This is a simple struct to allow us to easily have fonts that can be swapped in and out 
		//for rendering as the render for all characters is done in one long stream, with this we can 
		//break that stream up and allocate the appropriate font texture where required
		struct FontBlock
		{
			Font* pFont;
			unsigned int iCharacterIndexStart;
			unsigned int iNumCharsToRender;
		};
		std::vector<FontBlock*>  m_pFontRenderQueue;

		Font*                   m_pDebugFont;
		Font*                   m_pCurrentFont;
		std::list<Font*>        m_pFontList;

		GLuint				m_uiVAO;
		GLuint				m_uiVBO;
		GLuint				m_uiIBO;
		glm::mat4			m_m4ModelView;
		CharacterBillboard* m_pCharacterBillboards;
		unsigned int		m_uiCharactersToDraw;
	};

}//Namespace UG

 //////////////////////////////////////////////////////////////////////////
#endif //_FONT_MANAGER_H_
 //////////////////////////////////////////////////////////////////////////

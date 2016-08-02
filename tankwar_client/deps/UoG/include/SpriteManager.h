//////////////////////////////////////////////////////////////////////////
//	Author:	Jamie Stewart
//	Date:	08/07/2015
//	Brief:	Class to manage sprites
//////////////////////////////////////////////////////////////////////////
#ifndef _SPRITEMANAGER_H_
#define _SPRITEMANAGER_H_
//////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>
#include <queue>
#include <set>
#include "BaseSprite.h"
#include "Utilities.h"

namespace UG
{
	struct SpriteVertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 uv;
	};

	struct SpriteVertexData
	{
		SpriteVertex vertex[4];
	};

	struct SpriteBatch
	{
		unsigned int iNumToRender;
		SpriteVertexData svd[64];
	};
	//////////////////////////////////////////////////////////////////////////
	class SpriteManager
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		//This class is a static instance or a singleton class
		//////////////////////////////////////////////////////////////////////////
		static SpriteManager* CreateInstance();
		static SpriteManager* GetInstance();
		static void DestroyInstance();
		//////////////////////////////////////////////////////////////////////////
		void Draw(unsigned int a_uiShaderID);
		//////////////////////////////////////////////////////////////////////////
		int				AddSprite				(const char* a_pTexture, glm::vec2& a_v2Size, glm::vec2& a_v2Origin, glm::vec4 a_vfUVCoords, glm::vec4 a_v4colour);
		int				DuplicateSprite			(int a_uiSpriteID);
		void			MoveSprite				(int a_uiSpriteID, int a_iXPos, int a_iYPos);
		void			MoveSprite				(int a_uiSpriteID, const float* a_fVec);
		void			GetSpritePosition		(int a_uiSpriteID, glm::vec2& a_v2Pos) const;
		void			SetSpriteMatrix			(int a_uiSpriteID, const float* a_fm4);
		void			GetSpriteMatrix			(int a_uiSpriteID, float* a_fm4);
		void			RotateSprite			(int a_uiSpriteID, float a_iRotation);
		void			RemoveSprite			(int a_uiSpriteID);
		void			SetSpriteUVCoordinates	(int a_uiSpriteID, glm::vec2& a_minUVCoord, glm::vec2& a_maxUVCoord);
		void			GetSpriteUVCoordinates	(int a_uiSpriteID, glm::vec2& a_minUVCoord, glm::vec2& a_maxUVCoord);
		void			MarkSpriteForDraw		(int a_uiSpriteID);
		bool			StopDrawingSprite		(int a_uiSpriteID);
		void			SetSpriteColour			(int a_uiSpriteID, glm::vec4& a_v4Colour);
		void			GetSpriteColour			(int a_uiSpriteID, glm::vec4& a_v4Colour);
		void			SetSpriteScale			(int a_uiSpriteID, glm::vec2& a_v2SpriteScale);
		void			GetSpriteScale			(int a_uiSpriteID, glm::vec2& a_v2SpriteScale);
		void			SetSpriteBlendMode		(int a_uiSpriteID, const unsigned int& a_uiSourceFactor, const unsigned int& a_uiDestinationFactor);
		void			GetSpriteBlendMode		(int a_uiSpriteID, unsigned int& a_uiSourceFactor, unsigned int& a_uiDestinationFactor) const;
		void			SetDiscardSpriteColour	(int a_uiSpriteID, glm::vec4& a_v4Colour);
		void			GetDiscardSpriteColour	(int a_uiSpriteID, glm::vec4& a_v4Colour);
		void			SetSpriteLayer			(int a_uiSpriteID, const unsigned int& a_uiLayer);
		void			GetSpriteLayer			(int a_uiSpriteID, unsigned int& a_uiLayer) const;
		void			SetSpriteTexture		(int a_uiSpriteID, const char* a_pTextureName);
		void			GetSpriteTexture		(int a_uiSpriteID, char* a_pTextureName) const;


	protected:

		SpriteManager();
		~SpriteManager();

		int FindSpriteIndex(BaseSprite* a_pSprite);

		//function for sorting the SET Based on Layer and texture ID
		struct SortSet { 
			bool operator()(const BaseSprite* lhs, const BaseSprite* rhs) const { 
				if (lhs->GetLayer() != rhs->GetLayer()) {
					return lhs->GetLayer() < rhs->GetLayer();
				}
				else if (lhs->GetTextureID() != rhs->GetTextureID()) {
					return lhs->GetTextureID() < rhs->GetTextureID();
				}
				else
					return lhs < rhs;
			} 
		};
		//Struct to be used as a getter for retreiving sprite data from a base sprite
		struct SpriteDataGetter { 
			const UG::SpriteData& operator()(const BaseSprite* sprite) const
			{ 
				return sprite->GetSpriteData(); 
			}
		};
		
	private:
		std::vector<BaseSprite*>				m_Sprites;
		//Render Queue and Set to ensure that only unique items are added to the queue, with custom predicate for sorting
		std::set<BaseSprite*, SortSet >	m_CurrentRenderSet;
		
		std::queue<BaseSprite*>							m_pRenderQueue;
		std::vector<SpriteData> m_vSpriteData;
		GLuint m_uiTextureID = 0;

		static SpriteManager*					m_pInstance;

		GLuint m_ShaderID;

		GLuint m_uiVAO;
		GLuint m_uiVBO;
		GLuint m_uiIBO;

		UG::Vertex aoVertices[4];

		GLuint dtb;
		GLuint dtbo_tex;
		static unsigned int DefaultBufferCapacity;

	};

}//end namespace UG

 //////////////////////////////////////////////////////////////////////////
#endif //_SPRITEMANAGER_H_
 //////////////////////////////////////////////////////////////////////////
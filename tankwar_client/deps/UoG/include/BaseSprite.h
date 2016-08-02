//////////////////////////////////////////////////////////////////////////
//	Author:	Jamie Stewart
//	Date:	08/07/2015
//	Brief:	This is a basic textured screen-space quad
//////////////////////////////////////////////////////////////////////////
#ifndef _AIE_BASE_SPRITE_H_
#define _AIE_BASE_SPRITE_H_

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Utilities.h"

namespace UG
{
	
	struct SpriteData {
		glm::mat4 posRot;
		glm::vec2 origin;
		glm::vec2 scale;
		glm::vec4 UVcoords;
		glm::vec4 color;
	};

	//////////////////////////////////////////////////////////////////////////
	class BaseSprite
	{
	public:
		//Constructors Destructors
		BaseSprite(const char* a_pTexture, const glm::vec2& a_v2Size, const glm::vec2& a_v2Origin, const glm::vec4 a_fv4UVCoordinates = glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4 a_v4colour = glm::vec4(1.f, 1.f, 1.f, 1.f));
		BaseSprite(const BaseSprite& pSprite);
		~BaseSprite();
		///////////////////////////////////////////////////////////////////////////
		// Fucntions to set and Get sprite attributes 
		///////////////////////////////////////////////////////////////////////////
		void	SetRotation(const float a_iRotation);
		void	GetRotation(float a_iRotation)const;

		void	SetSpritecolour(const glm::vec4& a_v4colour);
		void	GetSpritecolour(glm::vec4& a_v4colour) const;

		void	SetPosition(int a_iX, int a_iY);
		void	SetPosition(const float* a_fVec);
		void	GetPosition(float& a_iX, float& a_iY) const;

		void	SetSpriteMatrix(const float* a_fm4);
		void	GetSpriteMatrix(float* a_fm4) const;

		void	SetOrigin(const glm::vec2& a_v2Origin);
		void	GetOrigin(glm::vec2& a_v2Origin) const;

		void	SetSize(float a_iWidth, float a_iHeight);
		void	GetSize(float& a_iWidth, float& a_iHeight) const;

		unsigned int GetTextureID() const { return m_uiTextureID; }
		void	SetTextureID(const unsigned int& a_textureID );

		void	SetUVCoords(const glm::vec2& a_minUVCoords, const glm::vec2& a_maxUVCoords);
		void	GetUVCoords(glm::vec2& a_minUVCoords, glm::vec2& a_maxUVCoords) const;

		void	SetBlendParameters(const unsigned int& a_uiSourceFactor, const unsigned int& a_uiDestinationFactor);
		void	GetBlendParameters(unsigned int& a_uiSourceFactor, unsigned int& a_uiDestinationFactor) const;
		///////////////////////////////////////////////////////////////////////////

		void	SetDiscardColor(const glm::vec4& a_v4colour);
		void	GetDiscardColor(glm::vec4& a_v4colour) const;
		
		void	GetSpriteData(SpriteData& a_spriteData) const { a_spriteData = m_spriteData; }
		const SpriteData& GetSpriteData() const { return m_spriteData; }

		void			SetLayer(unsigned int a_uLayer ) { m_uLayer = a_uLayer; }
		const unsigned int&	GetLayer() const { return m_uLayer; }

	private:
		glm::vec4			m_v4Spritecolour;
		glm::vec4			m_v4BlitColor;
		

		unsigned int	m_uiTextureID;
		unsigned int	m_uSourceBlendMode;
		unsigned int	m_uDestinationBlendMode;
		unsigned int	m_uLayer;
		SpriteData		m_spriteData;

	};
	///////////////////////////////////////////////////////////////////////////
	//inline functions 
	// these are inlined to improve performance as they are called frequently
	///////////////////////////////////////////////////////////////////////////
	inline void BaseSprite::SetPosition(int a_iX, int a_iY)
	{
		m_spriteData.posRot[3] = glm::vec4((float)a_iX, (float)a_iY, 0.f, 1.f);
	}

	inline void BaseSprite::SetPosition(const float* a_fVec)
	{
		m_spriteData.posRot[3] = glm::vec4(a_fVec[0], a_fVec[1], 0.f, 1.f);
	}

	inline void BaseSprite::SetSpriteMatrix(const float* a_fm4)
	{
		memcpy(glm::value_ptr(m_spriteData.posRot), a_fm4, sizeof(float) * 16);
	}

	inline void BaseSprite::GetSpriteMatrix(float* a_fm4) const
	{
		memcpy(a_fm4, glm::value_ptr(m_spriteData.posRot), sizeof(float) * 16);
	}

	inline void BaseSprite::GetPosition(float& a_iX, float& a_iY) const
	{
		a_iX = m_spriteData.posRot[3].x;
		a_iY = m_spriteData.posRot[3].y;
	}

	inline void BaseSprite::SetSize(float a_iWidth, float a_iHeight)
	{
		m_spriteData.scale = glm::vec2(a_iWidth, a_iHeight);
	}

	inline void BaseSprite::GetSize(float& a_iWidth, float& a_iHeight) const
	{
		a_iWidth = m_spriteData.scale.x;
		a_iHeight = m_spriteData.scale.y;
	}


}//namespace UG

 //////////////////////////////////////////////////////////////////////////
#endif //_AIE_BASE_SPRITE_H_
 //////////////////////////////////////////////////////////////////////////

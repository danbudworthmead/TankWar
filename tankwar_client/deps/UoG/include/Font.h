//////////////////////////////////////////////////////////////////////////
//	Author:	Jamie Stewart
//	Date:	07/07/2015
//	Brief:	Basic Font class for drawing screen-space text
//////////////////////////////////////////////////////////////////////////
#ifndef _FONT_H_
#define _FONT_H_
//////////////////////////////////////////////////////////////////////////
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Utilities.h"
#include <map>
#include <set>

namespace UG
{
	struct CharacterBillboard
	{
		Vertex v0;
		Vertex v1;
		Vertex v2;
		Vertex v3;
	};
	//////////////////////////////////////////////////////////////////////////
	class Font
	{
	public:

		//////////////////////////////////////////////////////////////////////////
		// Character struct used to hold information for each character represented
		// in the font being used
		typedef struct Character_s
		{
			int	id;
			int	x;
			int	y;
			int	width;
			int	height;
			int	xoffset;
			int	yoffset;
			int	xadvance;
			int	page;
			int	channel;
		} Character;

		typedef struct Kerning_s
		{
			unsigned int id;
			std::map<unsigned int, int> amount;

			void addSecond(unsigned int a_second, int a_amount)
			{
				amount[a_second] = a_amount;
			}

			bool operator<(const Kerning_s &rhs) const {
				return id < rhs.id;
			}

			bool operator ==(const Kerning_s &rhs)const {
				return (id == rhs.id);
			}

			bool operator !=(const Kerning_s &rhs)const {
				return (id != rhs.id);
			}

		}Kerning;

		//function for sorting the SET Based on Layer and texture ID
		struct KernComp {
			bool operator()(const Kerning* lhs, const Kerning* rhs) const {
				return lhs < rhs;
			}
		};

		///////////////////////////////////////////////////////////////////////////
		//Constructor/Destruction
		Font();
		Font(const char* pszFontName);
		~Font();
		///////////////////////////////////////////////////////////////////////////
		unsigned int LoadTexture(const char* pszTextureName);

		unsigned int DrawString(glm::vec4 v4Position, float a_fSize, glm::vec4 v4colour, const char* pBuffer, CharacterBillboard* pVertexDisplayArray);
		unsigned int GetTextureID() { return m_uiTextureID; }
		const char*		GetFontName() { return m_pFontName; }

	private:

		bool LoadFont(const char* pszFontName);
		char*			m_pFontName;

		unsigned int    m_uiTextureID;
		unsigned int    m_iNumCharacters;
		Character*      m_pCharacters;
		std::map< unsigned int, Character*> m_CharacterMap;
		// Scale values to account for any difference between texture size and stored font kerning
		float			m_TexScale;
		float			m_InvTexScale;
		//Font detalis
		char			m_FaceName[256];
		int				m_Size;
		unsigned int    m_IsBold;
		unsigned int    m_IsItalic;
		unsigned int    m_IsUnicode;
		unsigned int    m_IsSmooth;
		unsigned int    m_IsAa;
		int				m_Outline;
		int				m_StretchH;
		int				m_Padding[4];
		int				m_Spacing[2];
		// Common.
		int			m_LineHeight;
		int			m_Base;
		int			m_ScaleW;
		int			m_ScaleH;
		int			m_Pages;
		int			m_Packed;
		int			m_AlphaChannel;
		int			m_RedChannel;
		int			m_GreenChannel;
		int			m_BlueChannel;
		// Pages
		char		m_PageFilename[256];
		// Character mapping table
		int			m_MappingTable[256];
		// Kerning table.
		Kerning* m_pKernings;
		std::set<Kerning*, KernComp> m_KerningSet;
		bool		m_HasKerningInformation;
		
	};

}//Namespace UG

 //////////////////////////////////////////////////////////////////////////
#endif //_FONT_H_
 //////////////////////////////////////////////////////////////////////////

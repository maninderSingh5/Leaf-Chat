#ifndef DYNAMICTEXT_H
#define DYNAMICTEXT_H 

#include <string>
#include <vector>
#include <unordered_map>

//vendor
#include "SDL2/SDL_ttf.h"

static SDL_Renderer* textRender = nullptr;
static TTF_Font* font = nullptr;


namespace Leaf{
	struct Glyph;
	
	class dynamicText{	
		SDL_Color TextColor;
		std::vector<Leaf::Glyph>* glyphs;
		
		static const int xMargin;
		
	public:
		
		dynamicText(SDL_Color);
		void createGlyphs();
		int renderLine(const std::string&,int,int,int,int xx=0);
		int getVal(char);
		
		static void Init(SDL_Renderer*);
		static void CleanUp();
		static void Quit();
	};
	

	struct Glyph{
		SDL_Texture*gl_image=nullptr;
		int width = 0;
		int height = 0;
		
		Glyph(char,const SDL_Color&);
		~Glyph();
		
	};
	
}

#endif



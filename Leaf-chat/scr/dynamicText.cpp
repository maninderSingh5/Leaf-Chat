#include "dynamicText.h"


static std::unordered_map<std::string, std::vector<Leaf::Glyph>*> Map;


namespace Leaf{

const int dynamicText::xMargin = 10;
	
void dynamicText::Init(SDL_Renderer*render){
			
//	If font not open, then open it
		if(!font){
			TTF_Init();
			font = TTF_OpenFont("Assets/RoundedFont.ttf",30);
			
		if(!textRender)
			textRender = render;
		}
}

dynamicText::dynamicText(SDL_Color color) : TextColor(color)
	{
		std::string key = std::to_string(color.r) +std::to_string(color.g) +std::to_string(color.b) ;
		
		if(auto d=Map.find(key);d!=Map.end()){
			glyphs = d->second;
		}else{
			glyphs = new std::vector<Glyph>;
			createGlyphs();
			Map[key] = glyphs;
		}
		
	}
	
	void dynamicText::createGlyphs(){
		char chars[87] {"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,!@#$%&:;'{}[]<>/+-=*"};
		chars[84]='"',chars[85]=' ',
		chars[86] = '?';
		glyphs->reserve(90);
		
		for(char ch : chars)
			glyphs->emplace_back(ch,TextColor);
		
	}
	
	int dynamicText::renderLine(const std::string &mesg,int yTextPos,int ScreenWidth,int ScreenHeight,int xBy){
		
		int x = xMargin,y=yTextPos,wX=0;
		SDL_Rect textRect;
		int lvalue=0;
		int lastspace=0;
		bool safe = true;
		
		if(xBy){
			x = xBy;
		}
		
		
		
		for(uint cnt=0;cnt<mesg.length();cnt++){
			lvalue=getVal(mesg[cnt]);
			if(lvalue==85){
				lastspace = cnt;
				wX=x+ (*glyphs)[85].width;
				for(uint i=lastspace;i<mesg.length();i++){
					lvalue=getVal(mesg[i]);
					wX=wX+(*glyphs)[lvalue].width;
					if(wX >= ScreenWidth-xMargin){
						safe = false;
						break;
					}
					if(lvalue == 85){
						safe = true;
						break;
					}
				}
			}
			
		if(safe){
			textRect.x = x;
			textRect.y = y;
			textRect.w = (*glyphs)[lvalue].width;
			textRect.h = (*glyphs)[lvalue].height;
			SDL_RenderCopy(textRender,(*glyphs)[lvalue].gl_image,NULL,&textRect);
			x = x+(*glyphs)[lvalue].width;
		}else{
			cnt=lastspace;
			x = xMargin;
			y = y+(*glyphs)[lvalue].height;
			safe = true;
		}
		
		
		}
		
		y = y+(*glyphs)[lvalue].height;
		return y;
	}
		
	void dynamicText::CleanUp(){
		
		for(auto& d : Map)
			delete d.second;
		
		if(font)
		TTF_CloseFont(font);
	}
	void dynamicText::Quit(){
		TTF_Quit();
	}	
	
	int dynamicText::getVal(char letter){

switch(letter){
  case '0'  : return 0;
  case '1'  : return 1;
  case '2'  : return 2;
  case '3'  : return 3;
  case '4'  : return 4;
  case '5'  : return 5;
  case '6'  : return 6;
  case '7'  : return 7;
  case '8'  : return 8;
  case '9'  : return 9;
  case 'a'  : return 10;
  case 'b'  : return 11;
  case 'c'  : return 12;
  case 'd'  : return 13;
  case 'e'  : return 14;
  case 'f'  : return 15;
  case 'g'  : return 16;
  case 'h'  : return 17;
  case 'i'  : return 18;
  case 'j'  : return 19;
  case 'k'  : return 20;
  case 'l'  : return 21;
  case 'm'  : return 22;
  case 'n'  : return 23;
  case 'o'  : return 24;
  case 'p'  : return 25;
  case 'q'  : return 26;
  case 'r'  : return 27;
  case 's'  : return 28;
  case 't'  : return 29;
  case 'u'  : return 30;
  case 'v'  : return 31;
  case 'w'  : return 32;
  case 'x'  : return 33;
  case 'y'  : return 34;
  case 'z'  : return 35;
  case 'A'  : return 36;
  case 'B'  : return 37;
  case 'C'  : return 38;
  case 'D'  : return 39;
  case 'E'  : return 40;
  case 'F'  : return 41;
  case 'G'  : return 42;
  case 'H'  : return 43;
  case 'I'  : return 44;
  case 'J'  : return 45;
  case 'K'  : return 46;
  case 'L'  : return 47;
  case 'M'  : return 48;
  case 'N'  : return 49;
  case 'O'  : return 50;
  case 'P'  : return 51;
  case 'Q'  : return 52;
  case 'R'  : return 53;
  case 'S'  : return 54;
  case 'T'  : return 55;
  case 'U'  : return 56;
  case 'V'  : return 57;
  case 'W'  : return 58;
  case 'X'  : return 59;
  case 'Y'  : return 60;
  case 'Z'  : return 61;
  case '.'  : return 62;
  case ','  : return 63;
  case '!'  : return 64;
  case '@'  : return 65;
  case '#'  : return 66;
  case '$'  : return 67;
  case '%'  : return 68;
  case '&'  : return 69;
  case ':'  : return 70;
  case ';'  : return 71;
//  case '''  : return 72;
  case '{'  : return 73;
  case '}'  : return 74;
  case '['  : return 75;
  case ']'  : return 76;
  case '<'  : return 77;
  case '>'  : return 78;
  case '/'  : return 79;
  case '+'  : return 80;
  case '-'  : return 81;
  case '='  : return 82;
  case '*'  : return 83;
  case '"'  : return 84;
  case ' '  : return 85;
  case '?'  : return 86;
		
	const char spc[2] = "'";
	if(letter==spc[0]) return 72;
		
	}
	return 66;
}



	Glyph::Glyph(char alpha,const SDL_Color &textCol){
		char alphaStr[2]={alpha,'\0'};
		
		SDL_Surface *tempSurf=nullptr;
		if(font)
		tempSurf = TTF_RenderText_Solid(font,alphaStr,textCol);
		
		if(textRender)
		gl_image = SDL_CreateTextureFromSurface(textRender,tempSurf);
		SDL_QueryTexture(gl_image,NULL,NULL,&width,&height);
		
		SDL_FreeSurface(tempSurf);
		
	}
	
	Glyph::~Glyph(){
		SDL_DestroyTexture(gl_image);
	}

} 
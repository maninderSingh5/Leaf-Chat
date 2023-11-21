#ifndef MESSENGER_H
#define MESSENGER_H

#include "dynamicText.h"

#ifdef APPLICATION_H
	#include "Application.h"
#endif
#include <list>

namespace Leaf{
	
	class messenger{
		std::string idName;
		std::string connectTo;
		std::string serverIP;
		std::string color{",255,0,0"};
		bool logged = false;
		std::string InputText;
		
		int ScreenWidth = 0;
		int ScreenHeight = 0;
		SDL_Rect InBoxRect;
		SDL_Rect CurInbox;
		int boxNumber;
		SDL_Rect Box[8];
		std::string values[6];
		int YaxisToRenderMesg = 10;

		static std::list<std::string> ConsoleMesgs;
		static std::list<std::string> SendMesgs;
		
	public:
	
		static std::list<std::string>* getRecvList();
		static std::list<std::string>*getSendList();
	
	
		messenger() = default;
		messenger(std::string Name,int width,int height);
		~messenger();
		
		
		std::string getIdName();
		std::string getServerIp();
		std::string getConnectToId();
		void setIdNameAndWindowPram(std::string name,int w,int h);
		
		bool isLogged();
		void setLogged();
		SDL_Rect* GetInBoxRect();
		
		static void Init(SDL_Renderer*);
		static void CleanUp();
		static void Quit();
		
		void InitInput();
		void QuitInput();
		void PushInputMesg( std::string);
		void PopInputMesg();
		bool HandleTypedMesg(SDL_Event&);
		void HandleMouseClick(SDL_Event&);
		void HandleKeys(SDL_Event&);
		
		
		SDL_Color ExtractColor(std::string&);
		std::string EncapColor(const std::string&,SDL_Color&);
		
		void AddMesg(std::string mesg);
		void RefreshScreen();
		void PrintMesg(std::string&);
		
		
		void InitialInputBox(SDL_Renderer*);
		
	};
}

#endif
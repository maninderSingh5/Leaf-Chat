#pragma once

#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include <iostream>
#include <thread>
#include <chrono>

#include "messenger.h"
#include "Server.h"
#include "Client.h"
//vendor
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"


static SDL_Window* window = nullptr;
static SDL_Renderer* render= nullptr;


namespace Leaf{
	
	struct AppSpecification{
		std::string AppName = "Leaf Chat";
		int width = 700;
		int height = 700;
	};
	
	
	class Application {
		bool isRunning = false;
		double FPS = 10.0;
		AppSpecification AppWindow;
		messenger MSG;
	public:
		
		Application(AppSpecification  App = AppSpecification());
		~Application();
		
		static void Init();
		static void Quit();
		void cleanUp();
		
		void run();
		void renderApp();
		void setRender();
		void HandleNetServer();
		void HandleNetClient();
		void HandleEvents();
		void limitFrames(double,double);
		static double getTicks();
		
	};
	
}

#endif
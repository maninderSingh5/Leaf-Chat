#include "Application.h"

namespace Leaf{
	// initialize SDL System	
	void Application::Init(){
		SDL_Init(SDL_INIT_EVERYTHING);		Network::Init();
	}
	

	
//create App Window && init renderer for the window
Application::Application(AppSpecification  App):
	 isRunning(true),AppWindow(App){
	
		window=SDL_CreateWindow(
		AppWindow.AppName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		AppWindow.width,
		AppWindow.height,
		SDL_WINDOW_MAXIMIZED );
		
		if(!window){
			SDL_Log("CreateWindow Failed\n");
			isRunning = false;
			return;
		}
		
		render = SDL_CreateRenderer(
		window,-1,SDL_RENDERER_PRESENTVSYNC);
		if(!render){
			SDL_Log("CreateRenderer Failed\n");
			isRunning = false;
			return;
		}
		
		MSG.setIdNameAndWindowPram("Server",AppWindow.width,AppWindow.height);
		messenger::Init(render);
		MSG.InitInput();
	}
	
	Application::~Application(){
		
	}
	
	
	//Application Loop
	void Application::run(){
		
		double start=0.0, stop=0.0;
		
		
		while(isRunning){
			start = getTicks();
		
			
			
			if(MSG.isLogged()){
				setRender();
				MSG.RefreshScreen();
			}else
				MSG.InitialInputBox(render);
			
			renderApp();
			
			stop = getTicks();
			limitFrames(start,stop);
		}
	}
	
	
	void Application::HandleNetServer(){
		MSG.setLogged();
		Network* server = new Server();
		
		while(isRunning){
			double start=getTicks();
			
			server->acceptClient();
			server->run();
			
			double stop=getTicks();
			limitFrames(start,stop);
		}
		
		
		delete server;
	}
	
	
	void Application::HandleNetClient(){
		
		while(!MSG.isLogged()){
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
		
		
		Network* client = new Client(MSG.getIdName(),MSG.getConnectToId(),MSG.getServerIp());
		
		while(isRunning){
			double start=getTicks();
			
			client->run();
			
			double stop=getTicks();
			limitFrames(start,stop);
		}
		
		
		delete client;
	}
	
	
	
	
	
	
	void Application::HandleEvents(){
	
		SDL_Event event;

		double start = getTicks();
	while(isRunning){
		while(SDL_PollEvent(&event)){
		switch(event.type){
				case SDL_QUIT :
					isRunning = false;
					break;
					
				case SDL_MOUSEMOTION:
					MSG.HandleMouseClick(event);
				
					break;
					
				case SDL_KEYDOWN :
					MSG.HandleKeys(event);
					break;	
				case SDL_TEXTINPUT :
					isRunning=MSG.HandleTypedMesg(event);
					break;
				
			}
				
		}
		
		limitFrames(start,getTicks());
		}
	
	}
		
	
	
	//display what is rendered	
	void Application::renderApp(){
		SDL_RenderPresent(render);
	}
	
	void Application::setRender(){
		SDL_RenderClear(render);
		
		SDL_SetRenderDrawColor(render,255,255,255,255);
		
		SDL_RenderDrawRect(render,MSG.GetInBoxRect());
		
		SDL_SetRenderDrawColor(render,50,50,100,200);
		
	}
	
	
	// return current time in ms
	double Application::getTicks(){
		return SDL_GetTicks();
	}
	
	void Application::limitFrames(double start,double stop){
		double frameTime = 1000/FPS;
		double consumeTime = stop-start;
		int64_t delay = frameTime-consumeTime;

		if(delay>0){		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
//		std::cout<<"Consume "<<consumeTime<<std::endl;
		
		}
	}
	
// Clean System + SubSystems
	void Application::cleanUp(){
		SDL_Log("cleanUp\n");
		
		MSG.QuitInput();
		messenger::CleanUp();
			
		if(window)
		SDL_DestroyWindow(window);
		
		if(render)
		SDL_DestroyRenderer(render);
		
	}
	

// stop SDL System
	void Application::Quit(){
		SDL_Log("quit\n");
		
		messenger::Quit();
		Network::Quit();
		
		SDL_Quit();
	}
	
}


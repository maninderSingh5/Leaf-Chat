#include "Application.h"


using namespace Leaf;

int main(int argc, char *argv[]){

	Application::Init();
	
	Application* App = new Application();
	
	
//	std::thread NetTh(&Application::HandleNetServer,App);
	
	std::thread NetTh(&Application::HandleNetClient,App);
	
	std::thread EventManager(&Application::HandleEvents,App);
		
	App->run();
	
	EventManager.join();
	NetTh.join();
	
	App->cleanUp();
	
	Application::Quit();
	
	delete App;
	return 0;
}
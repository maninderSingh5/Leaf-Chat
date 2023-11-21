#include "Network.h"


namespace Leaf{
	
	void Network::Init(){
		SDL_Log("Network Init\n");
		SDLNet_Init();
	}
	void Network::Quit(){
		SDL_Log("Network Quit\n");
		SDLNet_Quit();
	}
	
	
	
	Network::Network(){
		Recv = messenger::getRecvList();
		Send = messenger::getSendList();
	}

	std::vector<std::string> Network::decomposeMesgs(std::string &AllMesgs){
		std::vector<std::string> AllPacks;
		std::string sMesg;
		sMesg.reserve(MAXMESGSIZE);
		
		for(int i=0;i<AllMesgs.size();i++){	
			char d = AllMesgs[i];
			if(d==255 ||d ==251 ||d==250 || i==AllMesgs.size()-1){
				
				sMesg.push_back(d);
				AllPacks.emplace_back(sMesg);
				sMesg.clear();
			}else{
				sMesg.push_back(d);
			}
			
		}
		
		
		return AllPacks;
	}
	
	
	
	void Network::send(){
		
	}
	
	void Network::receive(){
			
	}
	
	void Network::run(){
		
	}
	
	void Network::acceptClient(){
		
	}
	
	
	Network::~Network(){
		
	}
}
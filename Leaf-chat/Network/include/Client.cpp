#include "Client.h"


namespace Leaf{
	
	Client::Client(std::string From,std::string To,std::string Ip):Network(),From(From),To(To),serverIp(Ip){
		
		std::string firstPacket = "["+From+"]"+"["+To+"]";
		firstPacket.push_back(255);
		
		SDLNet_ResolveHost(&ip,serverIp.c_str(),Port);
		
		client=SDLNet_TCP_Open(&ip);
		
		Server = SDLNet_AllocSocketSet(1);
		SDLNet_TCP_AddSocket(Server,client);
		
		
		while(1){
			if(client){
			   SDLNet_TCP_Send(client, firstPacket.c_str(),firstPacket.size());
			   break;
		
			}
			SDL_Delay(200);
		}
			
	}
	
	Client::~Client(){
		SDL_Log("ShutDown Client\n");
		
		std::string delPack ="[" + From+"] - went Offline,255,0,0";
		delPack.push_back(250);
		SDLNet_TCP_Send(client,delPack.c_str(),delPack.size());
		
		SDL_Delay(10);
		
		SDLNet_FreeSocketSet(Server);
		SDLNet_TCP_Close(client);
	}
		
	void Client::send(){
		if(Send->empty())
			return;
			
		std::string mesg = Send->front();
		mesg.push_back(251);
		
		Send->pop_front();
		
		SDLNet_TCP_Send(client,mesg.c_str(),mesg.size());
		
	}
	
	void Client::receive(){
		
		std::vector<std::string> Packets;
				
		while(SDLNet_SocketReady( client)){
					
			char mesg[MAXMESGSIZE]{};
			SDLNet_TCP_Recv(client,mesg,MAXMESGSIZE);
			std::cout<<"revc "
			<<mesg<<"\n";
			std::string temp = mesg;
			
			Packets = decomposeMesgs(temp);
			
			for(auto&packet:Packets){
				
				if(packet.size()&&packet.back()==255){
					packet.pop_back();
					Recv->emplace_back( packet);
				}else if(packet.size()&&packet.back()==250){
				packet.pop_back();
				Recv->emplace_back(packet);
				
				}else if(packet.size()){
					packet.pop_back();
					Recv->emplace_back( packet);
				
				}else
					break;
			}
			Packets.clear();
				
		}
		
	}
	
	void Client::run(){
		
		
		int RecvCount = SDLNet_CheckSockets(Server,0);
		
		while(RecvCount--){
			receive();
		}
		
		
		int SendCount = Send->size();
		while(SendCount--){
			send();
		}
		
	}
	
	
	
} 
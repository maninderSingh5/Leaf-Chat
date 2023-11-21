#include "Server.h"

namespace Leaf{
	
	// Server-Net Constructor
	Server::Server() :Network(){
		
		SDLNet_ResolveHost(&ip,NULL,Port);
		server =SDLNet_TCP_Open(&ip);
		
		SocketSet = SDLNet_AllocSocketSet(MAXUSERS);
			
	}
	
	
	Server::~Server(){
		SDL_Log("Server Deleted\n");
		
	SDLNet_FreeSocketSet(SocketSet);
		SDLNet_TCP_Close(server);
		
		
	}
	
	void Server::acceptClient(){
		TCPsocket tempSkt = SDLNet_TCP_Accept(server);
		
		std::string firstPacket = "Connected To Server,255,255,255";
		firstPacket.push_back(255);
//	firstPacket.push_back('\n');
		if(tempSkt){
			SDLNet_TCP_AddSocket( SocketSet,tempSkt );
			clientCount++;
			
			vecSoc.emplace_back(tempSkt);
			
			
			SDLNet_TCP_Send(tempSkt,firstPacket.c_str(),firstPacket.size());
		}
		
	}
	
	
	void Server::send(){
		std::string mesgToSend = Send->front();
		Send->pop_front();
		
		int fs = mesgToSend.find_first_of('[')+1;
	int fc = mesgToSend.find_first_of(']');
	
	std::string From = mesgToSend.substr(fs,fc-fs);
		
		std::string getTo;
		
		if(auto d=FromToMap.find(From);d!=FromToMap.end()){
			getTo = d->second;
		}
		
		if(auto d=SocketMap.find(getTo);d!=SocketMap.end()){
			
			mesgToSend.push_back(251);
			
			SDLNet_TCP_Send(d->second,mesgToSend.c_str(),mesgToSend.size());			std::cout<<"\nsend "<<mesgToSend<<"\n";
		}else{
			Send->emplace_back(mesgToSend);
		}
		
		
	}
	
	void Server::receive(){
		
		std::vector<std::string> Packets;
		int i = 0;
		for(auto&d : vecSoc){
				
		while(SDLNet_SocketReady(d)){
					
			char mesg[MAXMESGSIZE]{};
			SDLNet_TCP_Recv(d,mesg,MAXMESGSIZE);
					
			std::string temp = mesg;
			
			Packets = decomposeMesgs(temp);
			
			for(auto&packet:Packets){
			if(packet.size()&&packet.back()==255){
				packet.pop_back();
				priorityPacket(packet,d);
			}else if(packet.size()&&packet.back()==250){
				
				deleteClient(packet,i);
			}else if(packet.size()&&packet.back()==251){
				packet.pop_back();
				Recv->emplace_back(packet);
				Send->emplace_back(packet);
				
			}else
				break;
			
			}
			Packets.clear();
				
			}
			i++;	
		}
		
	}


	void Server::deleteClient(std::string packet,int SocPos){
		
		vecSoc.erase(vecSoc.begin()+SocPos);
		
		int fs=packet.find_first_of('[')+1;
		int fc=packet.find_first_of(']');
	
		std::string From = packet.substr(fs,fc-fs);
		
		SocketMap.erase(From);
	
	}


	void Server::priorityPacket(std::string packet,TCPsocket socket){
	
	//	[From][To]255
	
	std::string From,To;
		
	int fs=packet.find_first_of('[')+1;
	int fc=packet.find_first_of(']');
	
	From = packet.substr(fs,fc-fs);
	
	int ts=packet.find_last_of('[')+1;
	int tc=packet.find_last_of(']');
	
	To=packet.substr(ts,tc-ts);
		
	FromToMap[From] = To;
	SocketMap[From] = socket;
	
	
	std::cout<<"From -"<<From<<"\n To -"<<To<<"\n";
		
		
	}
	
	void Server::run(){
		// Receive portion
		int RecvCount = SDLNet_CheckSockets(SocketSet,0);
		
		while(RecvCount--){
			receive();
		}
		
		
		int SendCount = Send->size();
		while(SendCount--){
			send();
		}
		
		
			
	}
	
}
#ifndef SERVER_H
	#define SERVER_H

#include "Network.h"

#include <unordered_map>

#define MAXUSERS 8
namespace Leaf{ 
	
	class Server : public Network{
		int clientCount = 0;
		std::vector<TCPsocket> vecSoc;
		TCPsocket server;
		SDLNet_SocketSet SocketSet;
		
		std::unordered_map< std::string,std::string > FromToMap;
		std::unordered_map< std::string,TCPsocket > SocketMap;
		
	public:
	
		void send()override;
		void receive()override;
		void run()override;
		void acceptClient()override;
		
		void priorityPacket(std::string packet,TCPsocket socket);
		void deleteClient(std::string,int socketPosition);
		
		Server();
		~Server()override;
		
	};
}

#endif
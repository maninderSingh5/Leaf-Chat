#ifndef CLIENT_H
#define CLIENT_H

#include "Network.h"

namespace Leaf{
	
	class Client :public Network{
		std::string From;
		std::string To;
		std::string serverIp;
		
		
		TCPsocket client;
		SDLNet_SocketSet Server;
		
		Client() = default;
		
	public:
		Client(std::string From,std::string To,std::string Ip);
		~Client();
		void send()override;
		void receive()override;
		void run()override;
	};

}

#endif 
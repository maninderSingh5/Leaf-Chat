#ifndef NETWORK_H
	#define NETWORK_H

#include "messenger.h"

// vendor
#include "SDL2/SDL_net.h"
#include <list>
#include <vector>
#include <iostream>

#define MAXMESGSIZE 1000


namespace Leaf{ 
	class Network{
		
	protected:
		IPaddress ip;
		int Port = 12345;
				
	public:
		
		std::list<std::string>* Recv;
		std::list<std::string>* Send;
		
		
		static void Init();
		static void Quit();
	
	
		Network();
		virtual ~Network();
		
		std::vector<std::string> decomposeMesgs(std::string&);

		virtual void send();
		virtual void receive();
		virtual void run();
		virtual void acceptClient();
	};
}
#endif


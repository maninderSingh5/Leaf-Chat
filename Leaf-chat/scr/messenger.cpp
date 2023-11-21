#include "messenger.h"
#include <iostream>

namespace Leaf{
	
	std::list<std::string> messenger::ConsoleMesgs;
		std::list<std::string> messenger::SendMesgs;
	
	std::list<std::string>* messenger::getRecvList(){
		return &ConsoleMesgs;
	}
	
	std::list<std::string>*messenger::getSendList(){
		return &SendMesgs;
	}
	
	
	messenger::messenger(std::string name, int width,int height){
		idName = name;
		ScreenWidth =  width;
		ScreenHeight = height;
		
		InBoxRect.x = 10;
		InBoxRect.y=ScreenHeight-100;
		InBoxRect.w =ScreenWidth;
		InBoxRect.h = 80;
		
	}
	messenger::~messenger(){
		
	}

	std::string messenger::getConnectToId(){
		return connectTo;
	}
	std::string messenger::getServerIp(){
		return serverIP;
	}
	
	std::string messenger::getIdName(){
		return idName;
	}
	
	void messenger::setLogged(){
		logged = true;
	}



	void 
messenger::InitialInputBox(SDL_Renderer* render){
		
		Box[0]={ScreenWidth/4,ScreenHeight/4,ScreenWidth/2,ScreenHeight/2};
		
	
		
		Box[1]={ScreenWidth/4+100,ScreenHeight/4+50,ScreenWidth/4+60,ScreenHeight/20};
		Box[2]={ScreenWidth/4+100,ScreenHeight/4+60+ScreenHeight/20,ScreenWidth/4+60,ScreenHeight/20};
		Box[3]={ScreenWidth/4+100,ScreenHeight/4+70+2*ScreenHeight/20,ScreenWidth/4+60,ScreenHeight/20};
	
		Box[4]={ScreenWidth/4+30,ScreenHeight/4+80+3*ScreenHeight/20,ScreenWidth/3 - 150,ScreenHeight/20};
		Box[5]={ScreenWidth/4+60+ScreenWidth/3-150,ScreenHeight/4+80+3*ScreenHeight/20,ScreenWidth/3 - 150,ScreenHeight/20};
		Box[6]={ScreenWidth/4+90+2*(ScreenWidth/3-150),ScreenHeight/4+80+3*ScreenHeight/20,ScreenWidth/3 - 150,ScreenHeight/20};
		
		Box[7]={ScreenWidth/2-100,ScreenHeight/4+100+ 4*ScreenHeight/20,200,ScreenHeight/20+20};
		
			
		std::string labels[]{
			"Login Page",
			"Name:",
			"To  :",
			"IP  :",
			"R:",
			"G:",
			"B:",
			"SUBMIT"
		};
		
		// [1 to 6] -> 7
		
		
		
		SDL_RenderClear(render);
		SDL_SetRenderDrawColor(render,0,0,0,255);


		SDL_Color black={0,0,0};
		
		for(int i=0;i<8;i++){
			dynamicText label(black);
			if(i==0)
			label.renderLine(labels[i],ScreenHeight/4+10,ScreenWidth,ScreenHeight,ScreenWidth/2-100);
			
			else if(i>0 && i<4)
			label.renderLine(labels[i],Box[i].y,ScreenWidth,ScreenHeight,ScreenWidth/4+10);
			
			else if(i>3 && i<7)
			label.renderLine(labels[i],Box[i].y,ScreenWidth,ScreenHeight,Box[i].x-25);
			else if(i==7)
			label.renderLine(labels[i],Box[i].y+10,ScreenWidth,ScreenHeight,Box[i].x+50);
			
			SDL_RenderDrawRect(render,&Box[i]);
		
			if(i>0 && i<7){
				int j = i-1;
				
				//if(Box[i].x==CurInbox.x && Box[i].y==CurInbox.y){
//				values[j] = values[j]+InputText;
//				InputText = "";
//				}
				label.renderLine(values[j],Box[i].y+2,ScreenWidth,ScreenHeight,Box[i].x+2);
							
			}										
			
		}
	
		SDL_SetRenderDrawColor(render,255,255,255,255);		
		
		
	}


	bool messenger::isLogged(){
		return logged;
	}

	void messenger::setIdNameAndWindowPram(std::string name,int w,int h){
		idName = name,
		ScreenWidth = w,
		ScreenHeight = h;
		
		InBoxRect.x = 2;
		InBoxRect.y = h-100;
		InBoxRect.w = w-20;
		InBoxRect.h =  100;
	}

	SDL_Rect* messenger::GetInBoxRect(){
		return &InBoxRect;
	}


	void messenger::Init(SDL_Renderer*render){
		dynamicText::Init(render);
	}
	
	void messenger::AddMesg(std::string mesg){
		ConsoleMesgs.emplace_back(mesg);
	}
	
	void messenger::RefreshScreen(){
		YaxisToRenderMesg = 10;
		for(std::string mesg : ConsoleMesgs){
			PrintMesg(mesg);
		}
		
		
		if(InputText.size()){
					
		dynamicText dt({255,255,255});
		dt.renderLine(InputText,InBoxRect.y,InBoxRect.w,InBoxRect.h);
		}
		
		
	}
	
		
	void messenger::PrintMesg(std::string& mesg){

		SDL_Color CoolColor = ExtractColor(mesg);
		
		dynamicText dt(CoolColor);
		YaxisToRenderMesg = dt.renderLine(mesg,YaxisToRenderMesg,ScreenWidth,ScreenHeight);
		
	}
	
	SDL_Color messenger::ExtractColor(std::string& mesg){
		SDL_Color color {0,0,0};
		int arr[3] = {0,0,0};
		int s = mesg.size() - 1;
		
		for(int i=2;i>-1;i--){
			std::string val(3,'0');
			
			for(int j =2;j>-1;j--){
			if(mesg[s]==',') break;
			val[j] = mesg[s];
			s--;
		//	mesg.pop_back();
			}
			if(mesg[s]==',') 
				s--;
			arr[i] = std::stoi(val);
		}
		
		int comacount{3};
		while(comacount){
			if(mesg.back() == ',')
				comacount--;
			mesg.pop_back();
		}
		
		
		color.r = arr[0];
		color.g = arr[1];
		color.b = arr[2];
		
		return color;
	}
	
	
	std::string EncapColor(const 	std::string& mesg,SDL_Color& color){
		
		std::string txCol=","+std::to_string(color.r)+","+std::to_string(color.g)+","+std::to_string(color.b);
		
		return mesg+txCol;
	}
	
	
/*
void InitInput();
void QuitInput();
void PushInputMesg( std::string);
void PopInputMesg();
void HandleTypedMesg();
*/
	
	void messenger::InitInput(){
		SDL_SetTextInputRect( &CurInbox);
		SDL_StartTextInput();
	}
	
	void messenger::QuitInput(){
		SDL_StopTextInput();
	}
	
	
	
	bool messenger::HandleTypedMesg(SDL_Event& event){
		if(!logged){
			values[boxNumber]+=event.text.text;
			return 1;
		}
		InputText+=event.text.text;
		
		if(InputText == "/q"){
			return 0;
		}
		return 1;
	}
	
	void messenger::HandleMouseClick(SDL_Event& event){
		SDL_Point Mouse;
		Mouse.x = event.motion.x;
		Mouse.y = event.motion.y;
	
		if(SDL_PointInRect(&Mouse,&InBoxRect) && logged){
			boxNumber = 0;
			CurInbox = InBoxRect;
			InitInput();
		}else if(!logged){
			
			for(int i=1;i<7;i++){
				
			if(SDL_PointInRect(&Mouse,&Box[i])){
				InputText = "";
				boxNumber = i-1;
				CurInbox = Box[i];
				InitInput();
				
			}
				
			}
			if( SDL_PointInRect(&Mouse,&Box[7])){
			for(auto& d : values)
				if(!d.size()){

					return;
				}
			logged = true;
			
			idName = values[0];
			connectTo = values[1];
			serverIP = values[2];
			//color 3-5 RGB
			color = ","+values[3]+","+values[4]+","+values[5];
			
			
			}
		}
	}
	
	void messenger::HandleKeys(SDL_Event& event){
		if(event.key.keysym.sym ==SDLK_BACKSPACE  ){
			if(logged &&InputText.size())
			InputText.pop_back();
			else if(values[boxNumber].size()){
				values[boxNumber].pop_back();
			}
		}
		
		if(event.key.keysym.sym ==SDLK_RETURN && InputText.size()){
			
			if(logged){
			
			std::string sendMesg="["+idName+"] - "+InputText+color;
			ConsoleMesgs.emplace_back(sendMesg);
			
			SendMesgs.emplace_back(sendMesg);
			}else{
				
				values[boxNumber-1]+=InputText;
				
			}
			InputText = "";
		}
	}
	
	

	void messenger::CleanUp(){
		dynamicText::CleanUp();
	}
	
	void messenger::Quit(){
		dynamicText::Quit();
	}
	
	
}
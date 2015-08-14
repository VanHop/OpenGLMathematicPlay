#ifndef STARTGAME
#define STARTGAME
#include "texture.h"
#include "Button.h"
#include "Help.h"
class StartGame{
	private:
		texture t;
		bool enable;
	public:
		Button start;
		StartGame();
		StartGame(char*,bool);
		void display();
		void setEnable(bool);
		bool isEnable();
};

#endif

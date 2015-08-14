#ifndef SCREEN
#define SCREEN

#include <vector>
#include "texture.h"
#include "Button.h"
#include "Block.h"
class Screen{
	private:
		texture t;
		bool enable;
	public:
		Screen();
		Screen(char*,bool);
		void display(Block A,Block B, vector<Button> button, Button GO, 
			Button NEXT,Button CONG,Button TRU, Button NHAN, Button CHIA,Button CounterTime, Button _Help,int score);
		void setEnable(bool);
		bool isEnable();
};

#endif

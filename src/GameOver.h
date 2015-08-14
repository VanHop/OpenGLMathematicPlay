#ifndef GAMEOVER
#define GAMEOVER
#include "texture.h"
#include "Button.h"
class GameOver{
	private:
		texture t;
		bool enable;
		int kq[4];
		char phepToan[3];
	public:
		Button tryAgain;
		GameOver();
		GameOver(char*,bool);
		void display(int score);
		void setEnable(bool);
		bool isEnable();
		void setKQ(int mang[], char pt[]);
};

#endif

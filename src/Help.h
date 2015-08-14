#ifndef HELP
#define HELP
#include "Texture.h"

class Help{
	
	public:
		private:
		texture t;
		bool enable;
	public:
		Help();
		Help(char*,bool);
		void display();
		void setEnable(bool);
		bool isEnable();
		
};

#endif

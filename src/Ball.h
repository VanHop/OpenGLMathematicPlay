

class Ball{
	private:
		int Level[10] = {1,4,9,16,25,36,49,64,81,100};
		int Index[10] = {1,2,3,4,5,6,7,8,9,10};
		bool enable;
		int num;
		double r;
		char name;
		void drawFilledSun(int);
	public:
		Ball();
		Ball(char);
		void setBall(int);
		void setEnable(bool);
		int getBall();
		void draw();
};

#include <stdio.h>     // Standard C/C++ IO  
#include <windows.h>   // Standard Header For MSWindows Applications
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>   // The GL Utility Toolkit (GLUT) Header
#include <math.h>
#include <string>
#include <iostream>
#include <vector>
#include "Header.h"
#include "Button.h"
#include "Block.h"
#include "numRandom.h"
#include "StartGame.h"
#include "Screen.h"
#include "GameOver.h"
#include "Ball.h"
#include "Help.h"
using namespace std;
Block A, B;
Button Go, Tru, Cong, Nhan, Chia, Swap, CounterTime, _Help;
vector<Button> button, cloneButton;
numRandom rd;
Operator PhepToan;
StartGame startGame;
Screen screen;
GameOver gameOver;
Help help;
int score;
double time;
Ball ballA, ballB;

bool init(void)
{
	glViewport(0,0,1366,768);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,1366,768,0.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glShadeModel(GL_SMOOTH);		
   	glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0f);	
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);	
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    
    rd.start();
	PhepToan = ADD;
	button.push_back(Button(Point(200,600), 90,90, true, rd.element[0], '1', "../image/button.bmp", "../image/button1.bmp"));
	button.push_back(Button(Point(350,600), 90,90, true, rd.element[1], '2', "../image/button.bmp", "../image/button1.bmp"));
	button.push_back(Button(Point(500,600), 90,90, true, rd.element[2], '3', "../image/button.bmp", "../image/button1.bmp"));
	button.push_back(Button(Point(650,600), 90,90, true, rd.element[3], '4', "../image/button.bmp", "../image/button1.bmp"));
	
	
	CounterTime = Button(Point(480,200), TIME,20, true, -1, '1', "../image/time.bmp", "../image/time.bmp");
	
	
	A = Block(Point(400,300), 120,120,Button(),false,"../image/A.bmp");
	B = Block(Point(700,300), 120,120,Button(),false,"../image/A.bmp");
	
	
	for(int i=0;i<4;i++)
		cloneButton.push_back(button.at(i));
		
		
	ballA = Ball('A');
	ballB = Ball('B');
	
	_Help = Button(Point(0,0), 100, 70, true, -1,'H',"../image/giup.bmp", "../image/giup.bmp");
	
	Go = Button(Point(900,300), 100, 100, false, -1,'G',"../image/go.bmp", "../image/go1.bmp");
	Cong = Button(Point(570,250), 70, 50, true, -1, ADD, "../image/math.bmp", "../image/math1.bmp");
	Tru = Button(Point(570,320), 70, 50, true, -1, SUB, "../image/math.bmp", "../image/math1.bmp");
	Nhan = Button(Point(570,390), 70, 50, true, -1, MUL, "../image/math.bmp", "../image/math1.bmp");
	Chia = Button(Point(570,460), 70, 50, true, -1, DIV, "../image/math.bmp", "../image/math1.bmp");
	Swap = Button(Point(900,600), 100,70, true, -1, 'N', "../image/swap.bmp", "../image/math1.bmp");
	
	
	Cong.setFocus(true);Tru.setFocus(false);Nhan.setFocus(false);Chia.setFocus(false);
	
	
	startGame = StartGame("../image/start.bmp", true);
	screen = Screen("../image/background.bmp", false);
	gameOver = GameOver("../image/gameover.bmp", false);
	gameOver.setKQ(rd._element, rd.phepToan);
	help = Help("../image/start.bmp", false);
	return true;
}

bool isEnable = true;

void render(void)   
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(isEnable){
		if(screen.isEnable()){
			time += DELTIME;
			CounterTime.width = TIME - time;
			if(time > TIME){
				screen.setEnable(false);
				gameOver.setEnable(true);
			}
			if(A.getHaveButton() && B.getHaveButton()){
				bool enable = false;
				switch(PhepToan){
					case ADD:
						if(A.button.getValue() + B.button.getValue() < 100)
							enable = true;
						break;
					case SUB:
						if( 0 <= A.button.getValue() - B.button.getValue())
							enable = true;
						break;
					case MUL:
						if( 0 <= A.button.getValue() * B.button.getValue() && A.button.getValue() * B.button.getValue() < 100)
							enable = true;
						break;
					case DIV:
						if(B.button.getValue() != 0 && A.button.getValue() % B.button.getValue() == 0)
							enable = true;
						break;
				}
				Go.setEnable(enable);
			}
			else	Go.setEnable(false);
			
			
			if(score > 0) Swap.setEnable(true);
			else	Swap.setEnable(false);
			
			
		}
		
		if(startGame.isEnable())
			startGame.display();	
		if(screen.isEnable()){
			screen.display(A,B,button,Go,Swap,Cong,Tru,Nhan,Chia,CounterTime, _Help,score);
			
			if(A.getHaveButton()){
				ballA.setBall(A.button.getValue());
				if(ballA.getBall() > 0)
					ballA.draw();
			}
			else	ballA.setBall(0);
			
			if(B.getHaveButton()){
				ballB.setBall(B.button.getValue());
				if(ballB.getBall() > 0)
					ballB.draw();
			}
			else	ballB.setBall(0);
			
		}
		if(gameOver.isEnable())		gameOver.display(score);
	}
	else if(help.isEnable())	help.display();
	glutSwapBuffers();
}


int xTarget, yTarget;
int k =-1;
void MouseButton(int but,int state,int x, int y){
	if (state == GLUT_DOWN && but == GLUT_LEFT_BUTTON){
		if(startGame.start.isEnable() && startGame.start.isWithinButton(x,y)){
			startGame.start.setClick(true);
			startGame.start.setSize();
		}
		else if(gameOver.tryAgain.isEnable() && gameOver.tryAgain.isWithinButton(x, y)){
			gameOver.tryAgain.setClick(true);
			gameOver.tryAgain.setSize();
			
		}
		else if(Go.isEnable() && Go.isWithinButton(x, y)){
			Go.setClick(true);
			Go.setSize();
			
		}
		else if(Cong.isWithinButton(x, y)){
			Cong.setClick(true);
			Cong.setSize();
			PhepToan = ADD;
			Cong.setFocus(true);Tru.setFocus(false);Nhan.setFocus(false);Chia.setFocus(false);
		}
		else if(Tru.isWithinButton(x, y)){
			Tru.setClick(true);
			Tru.setSize();
			PhepToan = SUB;
			Cong.setFocus(false);Tru.setFocus(true);Nhan.setFocus(false);Chia.setFocus(false);
		}
		else if(Nhan.isWithinButton(x, y)){
			Nhan.setClick(true);
			Nhan.setSize();
			PhepToan = MUL;
			Cong.setFocus(false);Tru.setFocus(false);Nhan.setFocus(true);Chia.setFocus(false);
		}
		else if(Chia.isWithinButton(x, y)){
			Chia.setClick(true);
			Chia.setSize();
			PhepToan = DIV;
			Cong.setFocus(false);Tru.setFocus(false);Nhan.setFocus(false);Chia.setFocus(true);
		}
		else if(Swap.isEnable() && Swap.isWithinButton(x, y)){
			Swap.setClick(true);
			Swap.setSize();
		}
		else if(A.getHaveButton() &&  A.button.isWithinButton(x, y)){
			xTarget = x - A.button.position.x;
			yTarget = y - A.button.position.y;
			A.button.setClick(true);
		}
		else if(B.getHaveButton() && B.button.isWithinButton(x, y)){
			xTarget = x - B.button.position.x;
			yTarget = y - B.button.position.y;
			B.button.setClick(true);
		}
		else{
			for(int i=0;i<button.size();i++){
				if(button.at(i).isWithinButton(x,y)){
					k = i;
					xTarget = x - button.at(k).position.x;
					yTarget = y - button.at(k).position.y;
					button.at(k).setClick(true);
					break;
				}
			}
		}
	}
	if (state == GLUT_UP && but == GLUT_LEFT_BUTTON){
		if(startGame.start.isClick()){
			startGame.start.setClick(false);
			startGame.start.setSize();
			startGame.setEnable(false);
			screen.setEnable(true);
		}
		else if(gameOver.tryAgain.isClick()){
			score = 0;
			time = 0;
			CounterTime.width = 300;
			
			button.clear();
			rd.start();
			gameOver.setKQ(rd._element, rd.phepToan);
			for(int i=0;i<4;i++){
				button.push_back(cloneButton.at(i));
				button.at(i).setValue(rd.element[i]);
			}

			A.setHaveButton(false);
			B.setHaveButton(false);
			
			gameOver.setEnable(false);
			screen.setEnable(true);
			gameOver.tryAgain.setClick(false);
			gameOver.tryAgain.setSize();
		}
		else if(Go.isClick()){
			Go.setClick(false);
			Go.setSize();
			if(Go.isWithinButton(x,y)){	
				if(button.size() == 0){
					bool isCorrect = false;
					switch(PhepToan){
						case ADD:
							if(A.button.getValue() + B.button.getValue() == 10)	isCorrect = true;
							break;
						case SUB:
							if(A.button.getValue() - B.button.getValue() == 10) isCorrect = true;
							break;
						case MUL:
							if(A.button.getValue() * B.button.getValue() == 10) isCorrect = true;
							break;
						case DIV:
							if(A.button.getValue() / B.button.getValue() == 10) isCorrect = true;
							break;
					}
					if(isCorrect){
						score++;
						time = 0;
					}
					A.setHaveButton(false);
					B.setHaveButton(false);
					
					rd.start();
					gameOver.setKQ(rd._element, rd.phepToan);
					for(int i=0;i<4;i++){
						button.push_back(cloneButton.at(i));
						button.at(i).setValue(rd.element[i]);
					}				
				}
				else{
					switch(PhepToan){
						case ADD:
							button.push_back(Button(p[button.size()], 90, 90, true, A.button.getValue() + B.button.getValue(), ' ' , "../image/button.bmp", "../image/button1.bmp"));
							A.setHaveButton(false);B.setHaveButton(false);
							break;
						case SUB:
							button.push_back(Button(p[button.size()], 90, 90, true, A.button.getValue() - B.button.getValue(), ' ', "../image/button.bmp", "../image/button1.bmp"));
							A.setHaveButton(false);B.setHaveButton(false);
							break;
						case MUL:
							button.push_back(Button(p[button.size()], 90, 90, true, A.button.getValue() * B.button.getValue(), ' ', "../image/button.bmp", "../image/button1.bmp"));
							A.setHaveButton(false);B.setHaveButton(false);
							break;
						case DIV:
							button.push_back(Button(p[button.size()], 90, 90, true, A.button.getValue() / B.button.getValue(), ' ', "../image/button.bmp", "../image/button1.bmp"));
							A.setHaveButton(false);B.setHaveButton(false);
							break;
					}
				}
			}
		}
		else if(Cong.isClick()){
			Cong.setClick(false);
			Cong.setSize();
		}
		else if(Tru.isClick()){
			Tru.setClick(false);
			Tru.setSize();
		}
		else if(Nhan.isClick()){
			Nhan.setClick(false);
			Nhan.setSize();
		}
		else if(Chia.isClick()){
			Chia.setClick(false);
			Chia.setSize();
		}
		else if(Swap.isClick()){
			Swap.setClick(false);
			Swap.setSize();
			
			if(Swap.isWithinButton(x,y)){
				button.clear();
				rd.start();
				gameOver.setKQ(rd._element, rd.phepToan);
				for(int i=0;i<4;i++){
					button.push_back(cloneButton.at(i));
					button.at(i).setValue(rd.element[i]);
				}
				//---------------------------//
				time = 0;
				CounterTime.width = 300;
				score--;
				//---------------------------//
			
				A.setHaveButton(false);
				B.setHaveButton(false);
			}

		}
		else if(A.getHaveButton() && A.button.isClick() ){
			
			if(B.isWithinBlock(A.button)){
				if(B.getHaveButton()){
					B.button.position = p[button.size()];
					button.push_back(B.button);
				}
				B.button = A.button;
				B.button.position = Point((B.position.x + B.width/2) - B.button.width/2, (B.position.y + B.height/2) - B.button.height/2);
				B.setHaveButton(true);
				B.button.setClick(false);
			}
			
			else{
				A.button.position = p[button.size()];
				A.button.root = A.button.position;
				A.button.setClick(false);
				button.push_back(A.button);
			}
			
			A.setHaveButton(false);
			A.button.setClick(false);
		}
		else if(B.getHaveButton() && B.button.isClick()){
			if(A.isWithinBlock(B.button)){
				if(A.getHaveButton()){
					A.button.position = p[button.size()];
					button.push_back(A.button);
				}
				A.button = B.button;
				A.button.position = Point((A.position.x + A.width/2) - A.button.width/2, (A.position.y + A.height/2) - A.button.height/2);
				A.setHaveButton(true);
				A.button.setClick(false);
			}
			
			else{
				B.button.position = p[button.size()];
				B.button.root = A.button.position;
				B.button.setClick(false);
				button.push_back(B.button);
			}
			
			B.setHaveButton(false);
			B.button.setClick(false);
		}
		else if(k != -1){
			if(A.isWithinBlock(button.at(k))){
				if(A.getHaveButton()){
					A.button.position = p[button.size()-1];
					button.push_back(A.button);
				}
				A.button = button.at(k);
				A.button.position = Point((A.position.x + A.width/2) - A.button.width/2, (A.position.y + A.height/2) - A.button.height/2);
				A.setHaveButton(true);
				A.button.setClick(false);
				for(int i = button.size() -1 ; i>k;i--){
					button.at(i).position = p[i-1];
					button.at(i).root = button.at(i).position;
				}
				button.erase(button.begin()  + k);
			}
			else if(B.isWithinBlock(button.at(k))){
				if(B.getHaveButton()){
					B.button.position = p[button.size()-1];
					button.push_back(B.button);
				}
				B.button = button.at(k);
				B.button.position = Point((B.position.x + B.width/2) - B.button.width/2, (B.position.y + B.height/2) - B.button.height/2);
				B.setHaveButton(true);
				B.button.setClick(false);
				for(int i = button.size() -1 ; i>k;i--){
					button.at(i).position = p[i-1];
					button.at(i).root = button.at(i).position;
				}
				button.erase(button.begin()  + k);
			}
			else{
				button.at(k).position = button.at(k).root;
				button.at(k).setClick(false);
			}
		}
		k = -1;
	}
	glutPostRedisplay();
}

void MousePassiveMotion(int x, int y)
{

	if(Go.isWithinButton(x,y))
		Go.setFocus(true);
	else
		Go.setFocus(false);
	
	if(gameOver.tryAgain.isWithinButton(x,y))
		gameOver.tryAgain.setFocus(true);
	else gameOver.tryAgain.setFocus(false);
	
	if(_Help.isWithinButton(x,y)){
		help.setEnable(true);
		isEnable = false;
	}
	else{
		isEnable = true;
		help.setEnable(false);
	}

}
void MouseMotion(int x, int y)
{
	if(A.getHaveButton() && A.button.isClick()){
		A.button.position.x = x - xTarget;
		A.button.position.y = y - yTarget;
	}
	if(B.getHaveButton() && B.button.isClick()){
		B.button.position.x = x - xTarget;
		B.button.position.y = y - yTarget;
	}
	if(k != -1 && button.at(k).isClick()){
		button.at(k).position.x = x - xTarget;
		button.at(k).position.y = y - yTarget;
	}
	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
			break;
		case 'a':
	        ballA.setEnable(true);
	        ballB.setEnable(true);
	        break;
		case 's':
			ballA.setEnable(false);
	        ballB.setEnable(false);
	        break;
		default:  
			break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WCX, WCY);
	glutCreateWindow("WELCOME TO MY GAME");
	init(); 
	glutFullScreen();
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutIdleFunc(render);
	glutMainLoop(); 
	return 0;
}

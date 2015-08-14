#include <math.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include "numRandom.h"
using namespace std;
numRandom::numRandom(){
}

char math[8] = {'+', '-', '*', '/','+','-','*','/'};

char tinhToan(int ketqua, int &x, int &y){
	bool loop = true;
	int pheptinh;
	while(loop){
		
		pheptinh = rand() % 8 + 1;
		
		switch(pheptinh){
			case 1: case 5://+
				x = rand() % 5 + 5;
				y = ketqua - x;
				if(y > 1 && y < 10)
					loop = false;
				break;
			case 2: case 6://-
				x = rand() % 5 + 5;
				y = ketqua + x;
				if(y > 1  && y < 10)
					loop = false;
				break;
			case 3: case 7://*
				for(int i=2;i<10;i++){
					if(ketqua % i){
						x = i;
						y = ketqua / x;
						break;
					}
				}
				break;
			case 4: case 8:// chia
				if(ketqua != 10){
					x = rand() % 4 + 1;
					y =  ketqua * x;
					if(1 < y && y < 100)
						loop = false;
				}
				break;		
		}
	}
	return math[pheptinh-1];
	
}
void numRandom::start(){
	srand (time(NULL));
	int kq = 10;
	int x,y;
	phepToan[0] = tinhToan(10,x,y);
	_element[0] = x; _element[1] = y;
	
	
	int r = rand() % 2;
	x = 0; y =0;
	if(r == 0){
		phepToan[1] = phepToan[0];
		_element[2] = _element[1];
		phepToan[r] = tinhToan(_element[r],x,y);
		_element[0] = y;
		_element[1] = x;
	} 
	else{
		phepToan[r] = tinhToan(_element[r],x,y);
		_element[1] = y;
		_element[2] = x;
		
	}	
	
	r = rand() % 3;
	x = 0; y =0;
	
	if(r == 0){
		phepToan[2] = phepToan[1];phepToan[1] = phepToan[0];
		_element[3] = _element[2];_element[2] = _element[1];
		phepToan[r] = tinhToan(_element[r],x,y);
		_element[0] = y;
		_element[1] = x;
	} 
	else if(r == 1){
		phepToan[2] = phepToan[1];
		_element[3] = _element[2];
		phepToan[r] = tinhToan(_element[r],x,y);
		_element[1] = y;
		_element[2] = x;
		
	}
	else{
		phepToan[r] = tinhToan(_element[r],x,y);
		_element[2] = y;
		_element[3] = x;
		
	}
	
	int temp[4] = {-1,-1,-1,-1};
	int i = 0;
	while(i<4){
		r = rand() % 4;
		if(temp[r] == r)	continue;
		temp[r] = r;
		element[i] = _element[r];
		i++;
	}
	
	
}

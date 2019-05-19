#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

class Hod{
public:
int y1,y2;
char a,b;
};

class Pole{
class Kletka{
public:
int figura;
int color;
};


public:
	int last_move_maker;
	Kletka kl[8][8];
	Pole * next;
	Pole * prev;
 	Pole();     
	void print(int);//если 1, то печатаем доску повернутую к первому игроку, если 2, то печатаем доску повернутую ко второму игроку, если 3, то печатаем доску так, чтобы ее лучше видел тот, чей ход сейчас.
	Hod hod;
	int type;
	Pole operator=(Pole);
	int check(Pole);
	
	int maketurn(int,int,int,int);
	int maketurnplus(int,int,int,int);
	int poiskkorx(int,int,int,int);
	int poiskkory(int,int,int,int);
	int tupocheck(int,int,int,int);
};



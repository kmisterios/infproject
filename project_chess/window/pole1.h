#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;
class Pole{
class Kletka{
public:
int figura;
int color;
};
Kletka kl[8][8];
int last_move_maker;
public:
 	Pole();     
	int maketurn(int,int,int,int);
	int maketurnplus(int,int,int,int);
	int poiskkorx(int,int,int,int);
	int poiskkory(int,int,int,int);
	int tupocheck(int,int,int,int);
	void print();
};
